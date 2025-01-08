/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream> // Per std::cout e std::endl
#include <windows.h>


//==============================================================================
EqualizerAudioProcessor::EqualizerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), treeState(*this, nullptr, "PARAMETERS", createParameterLayout())

#endif
{
    initFilters();
}

EqualizerAudioProcessor::~EqualizerAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout EqualizerAudioProcessor::createParameterLayout() 
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

    //Update number of reservation if adding params
    params.reserve(1);
    
    // Params definition
    auto pGainIn = std::make_unique<juce::AudioParameterFloat>("input_gain", "Input Gain", -24.0, 12.0, 0.0);
    auto pGainOut = std::make_unique<juce::AudioParameterFloat>("output_gain","Output Gain",-24.0, 12.0, 0.0);

    auto pLoPassFreq = std::make_unique<juce::AudioParameterFloat>("lopass_freq", "LowPass Frequency", juce::NormalisableRange<float>(20, 20000, 0.f, 0.25f), 20000);
    auto pHiPassFreq = std::make_unique<juce::AudioParameterFloat>("hipass_freq", "HiPass Frequency", juce::NormalisableRange<float>(20, 20000, 0.f, 0.25f), 20);

    auto pSubFreq = std::make_unique<juce::AudioParameterFloat>("sub_freq", "Sub Frequency", 30, 100, 30);
    auto pSubGain = std::make_unique<juce::AudioParameterFloat>("sub_gain", "Sub Gain", -12, 12, 0.0);

    auto pBassFreq = std::make_unique<juce::AudioParameterFloat>("bass_freq", "Bass Frequency", 150, 500, 150);
    auto pBassGain = std::make_unique<juce::AudioParameterFloat>("bass_gain", "Bass Gain", -12, 12, 0);

    auto pMidFreq = std::make_unique<juce::AudioParameterFloat>("mid_freq", "Mid Frequency", 1000, 5000, 1000);
    auto pMidGain = std::make_unique<juce::AudioParameterFloat>("mid_gain", "Mid Gain", -12, 12, 0);

    auto pHighFreq = std::make_unique<juce::AudioParameterFloat>("high_freq", "High Frequency", 8000, 16000, 8000);
    auto pHighGain = std::make_unique<juce::AudioParameterFloat>("high_gain", "High Gain", -12, 12, 0);

    params.push_back(std::move(pGainIn));
    params.push_back(std::move(pGainOut));

    params.push_back(std::move(pLoPassFreq));
    params.push_back(std::move(pHiPassFreq));

    params.push_back(std::move(pSubFreq));
    params.push_back(std::move(pSubGain));

    params.push_back(std::move(pBassFreq));
    params.push_back(std::move(pBassGain));

    params.push_back(std::move(pMidFreq));
    params.push_back(std::move(pMidGain));

    params.push_back(std::move(pHighFreq));
    params.push_back(std::move(pHighGain));

    return { params.begin(), params.end() };
}

//==============================================================================
const juce::String EqualizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EqualizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EqualizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EqualizerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EqualizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EqualizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EqualizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EqualizerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EqualizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void EqualizerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EqualizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;

    //Structure to define the context for the dsp module
    juce::dsp::ProcessSpec specs;
    specs.sampleRate = sampleRate;
    specs.maximumBlockSize = samplesPerBlock;
    specs.numChannels = getTotalNumOutputChannels();

    //Setting the filters and cleaning the pending values
    lopassFilter.prepare(specs);
    hipassFilter.prepare(specs);
    subFilter.prepare(specs);

    lopassFilter.reset();
    hipassFilter.reset();
    subFilter.reset();
    
    //Clearing the spectrum visualizer component
}

void EqualizerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EqualizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EqualizerAudioProcessor::initFilters() {
    *lopassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000, 0.1f);
    *hipassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(44100, 20, 0.1f);
    *subFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 30, 0.1f, 1.0f);
}

void EqualizerAudioProcessor::updateFilter() {
    *lopassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(lastSampleRate,
        *treeState.getRawParameterValue("lopass_freq"),
        0.1f);
    *hipassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(lastSampleRate,
        *treeState.getRawParameterValue("hipass_freq"),
        0.1f);

    if (*treeState.getRawParameterValue("sub_gain") > 0.0f)
    {
        *subFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate,
            *treeState.getRawParameterValue("sub_freq"),
            0.1f,
            juce::Decibels::decibelsToGain(float(*treeState.getRawParameterValue("sub_gain"))));
    }
    else if (*treeState.getRawParameterValue("sub_gain") == 0.0f)
    {
    }
    else
    {
     /*
        *subFilter.state = *juce::dsp::IIR::Coefficients<float>::makeNotch(lastSampleRate,
            *treeState.getRawParameterValue("sub_freq"),
            0.1f,
            juce::Decibels::decibelsToGain(float(*treeState.getRawParameterValue("sub_freq"))));
    */
    }

    /*
    float subRawGain = *treeState.getRawParameterValue("sub_gain");
    float subGainFactor = juce::Decibels::decibelsToGain(subRawGain);
    *subFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(lastSampleRate, *treeState.getRawParameterValue("sub_freq"), 1.f, subGainFactor);*/
}

void EqualizerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    //Cleaning empty or non used channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Retrieving VOLUME INPUT value from slider
    float inputGain = *treeState.getRawParameterValue("input_gain");
    float rawInputGain = juce::Decibels::decibelsToGain(inputGain);

    // Retrieving VOLUME INPUT value from slider
    float outputGain = *treeState.getRawParameterValue("output_gain");
    float rawOutputGain = juce::Decibels::decibelsToGain(outputGain);

    // Retrieving SUB FREQUENCY and GAIN value from slider
    int subFrequency = *treeState.getRawParameterValue("sub_freq");
    int subGain = *treeState.getRawParameterValue("sub_gain");
    int rawSubGain = juce::Decibels::decibelsToGain(subGain);

    // Retrieving BASS FREQUENCY and GAIN value from slider
    int bassFrequency = *treeState.getRawParameterValue("bass_freq");
    int bassGain = *treeState.getRawParameterValue("bass_gain");
    int rawBassGain = juce::Decibels::decibelsToGain(bassGain);

    // Retrieving MID FREQUENCY and GAIN value from slider
    int midFrequency = *treeState.getRawParameterValue("mid_freq");
    int midGain = *treeState.getRawParameterValue("mid_gain");
    int rawMidGain = juce::Decibels::decibelsToGain(midGain);

    // Retrieving HIGH FREQUENCY and GAIN value from slider
    int highFrequency = *treeState.getRawParameterValue("high_freq");
    int highGain = *treeState.getRawParameterValue("high_gain");
    int rawHighGain = juce::Decibels::decibelsToGain(highGain);

    //Creating the audio block to work with
    juce::dsp::AudioBlock<float> audioBlock(buffer);

    audioBlock *= rawInputGain;
    updateFilter();
    hipassFilter.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    lopassFilter.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    subFilter.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    audioBlock *= rawOutputGain;


    //Creating the sub band pass filter
    /*
    if (subGain >= 0) {
        subCoefficients = juce::dsp::IIR::Coefficients<float>::makeBandPass(44100, subFrequency);
    }
    else {
        subCoefficients = juce::dsp::IIR::Coefficients<float>::makeNotch(44100, subFrequency);
    }*/

    //subFilter = juce::dsp::IIR::Filter<float>::Filter(subCoefficients);
    //subFilter.process(context);
    
    /*
    // Retrieving BASS FREQUENCY and GAIN value from slider
    int bassFrequency = *treeState.getRawParameterValue("bass_freq");
    int bassGain = *treeState.getRawParameterValue("bass_gain");
    int rawBassGain = juce::Decibels::decibelsToGain(bassGain);

    // Retrieving MID FREQUENCY and GAIN value from slider
    int midFrequency = *treeState.getRawParameterValue("mid_freq");
    int midGain = *treeState.getRawParameterValue("mid_gain");
    int rawMidGain = juce::Decibels::decibelsToGain(midGain);

    // Retrieving HIGH FREQUENCY and GAIN value from slider
    int highFrequency = *treeState.getRawParameterValue("high_freq");
    int highGain = *treeState.getRawParameterValue("high_gain");
    int rawHighGain = juce::Decibels::decibelsToGain(highGain);
    */

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) 
        {
            //channelData[sample] *= rawInputGain;

            //channelData[sample] *= rawOutputGain;

        }
    }
}

//==============================================================================
bool EqualizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EqualizerAudioProcessor::createEditor()
{
    return new EqualizerAudioProcessorEditor (*this);
}

//==============================================================================
void EqualizerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EqualizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EqualizerAudioProcessor();
}

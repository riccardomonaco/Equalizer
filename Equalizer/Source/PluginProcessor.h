/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <string.h>
#include <JuceHeader.h>
#include "AnalyzerComponent.h"

//==============================================================================
/**
*/
class EqualizerAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    EqualizerAudioProcessor();
    ~EqualizerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void initFilters();
    void updateFilter();
    bool getStateLoPass();
    bool getStateHiPass();
    float valueToSteps(float value, int type);
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // Value Trees ================================================================
    juce::AudioProcessorValueTreeState treeState;

    // Spectrum analyzer ==========================================================
    std::unique_ptr<AnalyzerComponent> analyzerComponent;
    void setAnalyzerComponent(std::unique_ptr<AnalyzerComponent> analyzer);

    // dB Meter ===================================================================
    float EqualizerAudioProcessor::getMeterLevel();


private:

    float lastSampleRate;
    int BWPeakFilterSub;
    int BWPeakFilterBass;
    int BWPeakFilterMid;
    int BWPeakFilterHigh;
    bool hipassActive;
    bool lopassActive;

    enum
    {
        sub = 0,
        bass = 1,
        mid = 2,
        high = 3
    };

    float rmsLevel{ -30.0f };  // Valore iniziale in dB

    // Filters ==================================================================
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, 
                                   juce::dsp::IIR::Coefficients<float>> lopassFilter;

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
                                   juce::dsp::IIR::Coefficients<float>> hipassFilter;

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
                                   juce::dsp::IIR::Coefficients<float>> subFilter;
    
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
                                   juce::dsp::IIR::Coefficients<float>> bassFilter;

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
                                   juce::dsp::IIR::Coefficients<float>> midFilter;

    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
                                   juce::dsp::IIR::Coefficients<float>> highFilter;

    // Parameters =================================================================
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerAudioProcessor)
};
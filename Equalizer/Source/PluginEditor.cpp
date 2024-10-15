/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EqualizerAudioProcessorEditor::EqualizerAudioProcessorEditor (EqualizerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    //Adding custom lookandfeel class
    CustomLookAndFeel customLookAndFeel;

    /*
     *   Adding and setting the INPUT input slider
     */
    addAndMakeVisible(inputGainFader);
    inputGainFader.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    inputGainFader.setRange(-24.0, 12.0, 0.1);
    inputGainFader.setDoubleClickReturnValue(true, 0.0);
    inputGainAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "input_gain", inputGainFader);
    //Setting custom lookandfeel
    inputGainFader.setLookAndFeel(&customLookAndFeel);

    /*
     *   Adding and setting the OUTPUT input slider
     */
    addAndMakeVisible(outputGainFader);
    outputGainFader.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    outputGainFader.setRange(-24.0, 12.0, 0.1);
    outputGainFader.setDoubleClickReturnValue(true, 0.0);
    outputGainAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "output_gain", outputGainFader);
    //Setting custom lookandfeel
    outputGainFader.setLookAndFeel(&customLookAndFeel);

    /*
     *   Adding and setting the SUB FREQUENCIES input sliders
     */
    addAndMakeVisible(subFrequency);
    subFrequency.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    subFrequency.setRange(30, 100, 10);
    subFrequency.setDoubleClickReturnValue(true, 30);
    subFrequencyAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "sub_freq", subFrequency);

    addAndMakeVisible(subGain);
    subGain.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    subGain.setRange(-12, 12, 1);
    subGain.setDoubleClickReturnValue(true, 0);
    subGainAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "sub_gain", subGain);

    /*
     *   Adding and setting the BASS FREQUENCIES input slider
     */
    addAndMakeVisible(bassFrequency);
    bassFrequency.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    bassFrequency.setRange(150, 500, 50);
    bassFrequency.setDoubleClickReturnValue(true, 150);
    bassFrequencyAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "bass_freq", bassFrequency);

    /*
     *   Adding and setting the MID FREQUENCIES input slider
     */
    addAndMakeVisible(midFrequency);
    midFrequency.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    midFrequency.setRange(1000, 5000, 500);
    midFrequency.setDoubleClickReturnValue(true, 1000);
    midFrequencyAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "mid_freq", midFrequency);

    /*
     *   Adding and setting the HIGH FREQUENCIES input slider
     */
    addAndMakeVisible(highFrequency);
    highFrequency.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    highFrequency.setRange(8000, 16000, 2000);
    highFrequency.setDoubleClickReturnValue(true, 8000);
    highFrequencyAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "high_freq", highFrequency);

    //Setting the window size
    setSize (750 * 2, 450 * 2);
}

EqualizerAudioProcessorEditor::~EqualizerAudioProcessorEditor()
{
}

//==============================================================================
void EqualizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    //Instantiating background image
    bgImage = juce::ImageCache::getFromMemory(BinaryData::EQ_BG_SPC_png, BinaryData::EQ_BG_SPC_pngSize);
    
    //Rendering the image
    g.drawImageWithin(bgImage, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);

    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //Text section
     /*
        g.setColour(juce::Colours::white);
        g.setFont (juce::FontOptions (15.0f));
        g.drawFittedText ("EQUALIZER IN PROGRESS...", getLocalBounds(), juce::Justification::centred, 1);
     */
}

void EqualizerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    /* Input and output faders */
    inputGainFader.setBounds (610 * 2, 245 * 2, 10 * 2, 181 * 2);
    outputGainFader.setBounds (680 * 2, 245 * 2, 10 * 2, 181 * 2);

    /* Sub, bass, mid and high frequency knobs */
    subFrequency.setBounds(50, 650, 200, 200);
    subGain.setBounds(50, 500, 200, 200);

    bassFrequency.setBounds(subFrequency.getBounds().getX() + 250, 650, 200, 200);
    midFrequency.setBounds(bassFrequency.getBounds().getX() + 250, 650, 200, 200);
    highFrequency.setBounds(midFrequency.getBounds().getX() + 250, 650, 200, 200);
}

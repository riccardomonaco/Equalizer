/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
EqualizerAudioProcessorEditor::EqualizerAudioProcessorEditor (EqualizerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    //Adding custom lookandfeel class
    CustomLookAndFeel customLookAndFeel;

    /********************************************************
     *
     *   Adding and setting the INPUT VOLUME slider
     *
     *********************************************************/
    addAndMakeVisible(inputGainFader);
    inputGainFader.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    inputGainFader.setRange(-24.0, 12.0, 0.1);
    inputGainFader.setDoubleClickReturnValue(true, 0.0);
    inputGainAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "input_gain", inputGainFader);
    //Setting custom lookandfeel
    inputGainFader.setLookAndFeel(&customLookAndFeel);

    /********************************************************
     *
     *   Adding and setting the OUTPUT VOLUME slider
     *
     *********************************************************/
    addAndMakeVisible(outputGainFader);
    outputGainFader.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    outputGainFader.setRange(-24.0, 12.0, 0.1);
    outputGainFader.setDoubleClickReturnValue(true, 0.0);
    outputGainAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "output_gain", outputGainFader);
    //Setting custom lookandfeel
    outputGainFader.setLookAndFeel(&customLookAndFeel);

    /********************************************************
     *
     *   Adding and setting the SUB FREQUENCIES input slider
     *
     *********************************************************/
    addAndMakeVisible(subFrequency);
    subFrequency.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    subFrequency.setRange(30, 100, 20);
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

    /* Dimensions variables */
    int knobWidth = 150;
    int knobHeight = 150;
    int filterKnobY = 600;
    int gainKnobY = 450;
    int spacingBKnobs = 250;

    /* Sub frequency and gain knobs positions and dimensions */
    subFrequency.setBounds(50, filterKnobY, knobWidth, knobHeight);
    subGain.setBounds(50, gainKnobY, knobWidth, knobHeight);

    /*Setting the others relative to the sub one */
    bassFrequency.setBounds(subFrequency.getBounds().getX() + spacingBKnobs, 
                            subFrequency.getBounds().getY(), 
                            knobWidth, 
                            knobHeight);

    bassGain.setBounds(subGain.getBounds().getX() + spacingBKnobs, 
                       subGain.getBounds().getY(), 
                       knobWidth, 
                       knobHeight);

    midFrequency.setBounds(bassFrequency.getBounds().getX() + spacingBKnobs, 
                           bassFrequency.getBounds().getY(), 
                           knobWidth, 
                           knobHeight);
    
    midGain.setBounds(bassGain.getBounds().getX() + spacingBKnobs, 
                      bassGain.getBounds().getY(), 
                      knobWidth, 
                      knobHeight);

    highFrequency.setBounds(midFrequency.getBounds().getX() + spacingBKnobs, 
                            midFrequency.getBounds().getY(), 
                            knobWidth, 
                            knobHeight);

    highGain.setBounds(midFrequency.getBounds().getX() + spacingBKnobs, 
                       midGain.getBounds().getY(), 
                       knobWidth, 
                       knobHeight);
}

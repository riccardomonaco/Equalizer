/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "CustomLookAndFeel.h"
#include "testLAF.h"

//==============================================================================
EqualizerAudioProcessorEditor::EqualizerAudioProcessorEditor (EqualizerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

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
     *   Adding and setting the LOPASS FREQ input slider
     *
     *********************************************************/
    addAndMakeVisible(hipassFrequency);
    hipassFrequency.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    hipassFrequency.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    hipassFrequency.setRange(20, 20000, 1);
    hipassFrequency.setDoubleClickReturnValue(true, 20);
    hipassFrequency.setLookAndFeel(&customLookAndFeel);
    hipassFrequencyAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "hipass_freq", hipassFrequency);

    /********************************************************
     *
     *   Adding and setting the HIPASS FREQ input slider
     *
     *********************************************************/
    addAndMakeVisible(lopassFrequency);
    lopassFrequency.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    lopassFrequency.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    lopassFrequency.setRange(20, 20000, 1);
    lopassFrequency.setDoubleClickReturnValue(true, 20000.0);
    lopassFrequencyAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "lopass_freq", lopassFrequency);
    lopassFrequency.setLookAndFeel(&customLookAndFeel);


    /********************************************************
     *
     *   Adding and setting the SUB FREQUENCIES input slider
     *
     ********************************************************
    addAndMakeVisible(subFrequency);
    subFrequency.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    subFrequency.setRange(double(500), double(1000), double(10));
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
    */

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

    /*
    POSIZIONI KNOBS
    LOPASS 
    
    */;

    /* Dimensions variables */
    int knobWidth = 150;
    int knobHeight = 150;
    int filterKnobY = 600;
    int gainKnobY = 450;
    int spacingBKnobs = 250;
    int lopasshipassY = 695;
    int lopasshipassWidth = 135;
    int lopassX = 900;
    int hipassX = 80;
    int fadersWidth = 80;
    int fadersHeight = 362;
    int fadersImageOffset = 4;
    float fadersScaleFactor = 1.5;
    int inputGainFaderX = 1230;
    int outputGainFaderX = 1370;
    int inoutGainFaderY = 490;

    /* Input and output faders */
    inputGainFader.setBounds(inputGainFaderX - fadersWidth * fadersScaleFactor + fadersImageOffset, inoutGainFaderY, fadersWidth * 2, fadersHeight);
    outputGainFader.setBounds(outputGainFaderX - fadersWidth * fadersScaleFactor + fadersImageOffset, inoutGainFaderY, fadersWidth * 2, fadersHeight);

    lopassFrequency.setBounds(lopassX, lopasshipassY, lopasshipassWidth, lopasshipassWidth);
    hipassFrequency.setBounds(hipassX, lopasshipassY, lopasshipassWidth, lopasshipassWidth);

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

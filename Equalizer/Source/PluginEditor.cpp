/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "CustomLookAndFeel.h"
#include "AnalyzerComponent.h"

//==============================================================================
EqualizerAudioProcessorEditor::EqualizerAudioProcessorEditor (EqualizerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
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
    hipassFrequencyAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "hipass_freq", hipassFrequency);
    hipassFrequency.setLookAndFeel(&customLookAndFeel);

    /********************************************************
     *
     *   Adding and setting the HIPASS FREQ input slider
     *
     *********************************************************/
    addAndMakeVisible(lopassFrequency);
    lopassFrequency.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    lopassFrequency.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    lopassFrequency.setRange(20, 20000, 1);
    lopassFrequency.setDoubleClickReturnValue(true, 20000);
    lopassFrequencyAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "lopass_freq", lopassFrequency);
    lopassFrequency.setLookAndFeel(&customLookAndFeel);

    /********************************************************
     *
     *   Adding and setting the SUB FREQUENCIES input slider
     *
     ********************************************************/
    addAndMakeVisible(subFrequency);
    subFrequency.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    subFrequency.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    subFrequency.setRange(30, 100, 30);
    subFrequency.setDoubleClickReturnValue(true, 30);
    subFrequencyAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "sub_freq", subFrequency);
    subFrequency.setLookAndFeel(&selectorLookAndFeel);

    addAndMakeVisible(subGain);
    subGain.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    subGain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    subGain.setRange(-24, 24, 1);
    subGain.setDoubleClickReturnValue(true, 0);
    subGainAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "sub_gain", subGain);
    subGain.setLookAndFeel(&customLookAndFeel);

    /********************************************************
    *
    *   Adding and setting the BASS FREQUENCIES input slider
    *
    ********************************************************/
    addAndMakeVisible(bassFrequency);
    bassFrequency.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    bassFrequency.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    bassFrequency.setRange(150, 500, 50);
    bassFrequency.setDoubleClickReturnValue(true, 150);
    bassFrequencyAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "bass_freq", bassFrequency);
    bassFrequency.setLookAndFeel(&selectorLookAndFeel);

    addAndMakeVisible(bassGain);
    bassGain.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    bassGain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    bassGain.setRange(-24, 24, 1);
    bassGain.setDoubleClickReturnValue(true, 0);
    bassGainAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "bass_gain", bassGain);
    bassGain.setLookAndFeel(&customLookAndFeel);

    /********************************************************
    *
    *   Adding and setting the MID FREQUENCIES input slider
    *
    ********************************************************/
    addAndMakeVisible(midFrequency);
    midFrequency.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    midFrequency.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    midFrequency.setRange(1000, 5000, 1000);
    midFrequency.setDoubleClickReturnValue(true, 1000);
    midFrequencyAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "mid_freq", midFrequency);
    midFrequency.setLookAndFeel(&selectorLookAndFeel);

    addAndMakeVisible(midGain);
    midGain.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    midGain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    midGain.setRange(-24, 24, 1);
    midGain.setDoubleClickReturnValue(true, 0);
    midGainAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "mid_gain", midGain);
    midGain.setLookAndFeel(&customLookAndFeel);

    /********************************************************
    *
    *   Adding and setting the HIGH FREQUENCIES input slider 
    *
    ********************************************************/
    addAndMakeVisible(highFrequency);
    highFrequency.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    highFrequency.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    highFrequency.setRange(8000, 16000, 2000);
    highFrequency.setDoubleClickReturnValue(true, 8000);
    highFrequencyAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "high_freq", highFrequency);
    highFrequency.setLookAndFeel(&selectorLookAndFeel);

    addAndMakeVisible(highGain);
    highGain.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    highGain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    highGain.setRange(-24, 24, 1);
    highGain.setDoubleClickReturnValue(true, 0);
    highGainAtch =
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "high_gain", highGain);
    highGain.setLookAndFeel(&customLookAndFeel);

    //Setting and adding spectrum analyzer
    p.setAnalyzerComponent(&analyzer);
    addAndMakeVisible(analyzer);

    //Setting the window size
    setSize(750 * 2, 450 * 2);
}

EqualizerAudioProcessorEditor::~EqualizerAudioProcessorEditor()
{
}

//==============================================================================
void EqualizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    //Instantiating background image
    bgImage = juce::ImageCache::getFromMemory(BinaryData::EQ_BG_SPC_png, BinaryData::EQ_BG_SPC_pngSize);
    ledOnImage = juce::ImageCache::getFromMemory(BinaryData::LED_RED_ON_png, BinaryData::LED_RED_ON_pngSize);
    
    //Rendering the image
    g.drawImageWithin(bgImage, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    
    //Rendering active leds
    if (audioProcessor.getStateHiPass()) {
        g.drawImage(ledOnImage, 193, 819, 50, 50, 0, 0, ledOnImage.getWidth(), ledOnImage.getHeight());
    }
    else repaint();

    if (audioProcessor.getStateLoPass()) {
        g.drawImage(ledOnImage, 870, 819, 50, 50, 0, 0, ledOnImage.getWidth(), ledOnImage.getHeight());
    }
    else repaint();
}

void EqualizerAudioProcessorEditor::resized()
{
    /* Dimensions variables */
    int knobWidth = 150;
    int knobHeight = 150;
    int filterKnobY = 600;
    int gainKnobY = 450;
    int spacingBKnobs = 250;
    //lopass hipass
    int lopasshipassY = 704;
    int lopasshipassWidth = 109;
    int lopassX = 910;
    int hipassX = 90;
    //volume faders
    int fadersWidth = 80;
    int fadersHeight = 362;
    int fadersImageOffset = 4;
    float fadersScaleFactor = 1.5;
    int inputGainFaderX = 1230;
    int outputGainFaderX = 1370;
    int inoutGainFaderY = 490;
    //sub range
    int subGainX = 244;
    int subGainY = 495.5;
    int subGainWidth = 68;
    int subFrequencyX = 244;
    int subFrequencyY = 623;
    int subFrequencyWidth = 68;
    //knobs 
    int lilKnobsDistance = 117;
    int lilKnobWidth = 68;

    /* Input and output faders */
    inputGainFader.setBounds(inputGainFaderX - fadersWidth * fadersScaleFactor + fadersImageOffset, inoutGainFaderY, fadersWidth * 2, fadersHeight);
    outputGainFader.setBounds(outputGainFaderX - fadersWidth * fadersScaleFactor + fadersImageOffset, inoutGainFaderY, fadersWidth * 2, fadersHeight);

    /* HiPass and LoPass filters */
    lopassFrequency.setBounds(lopassX, lopasshipassY, lopasshipassWidth, lopasshipassWidth);
    hipassFrequency.setBounds(hipassX, lopasshipassY, lopasshipassWidth, lopasshipassWidth);

    /* Sub frequency and gain knobs positions and dimensions */
    subGain.setBounds(subGainX, subGainY, subGainWidth, subGainWidth);
    subFrequency.setBounds(subFrequencyX, subFrequencyY, subFrequencyWidth, subFrequencyWidth);


    /* Setting bass pos and dim relative to the sub one */
    bassGain.setBounds(subGainX + subGainWidth + lilKnobsDistance, subGainY, subGainWidth, subGainWidth);
    bassFrequency.setBounds(subFrequencyX + subFrequencyWidth + lilKnobsDistance, subFrequencyY, subGainWidth, subGainWidth);

    /* Setting mid pos and dim relative to the sub one */
    midFrequency.setBounds(bassFrequency.getBounds().getX() + lilKnobsDistance + lilKnobWidth,
                           bassFrequency.getBounds().getY(), 
                           lilKnobWidth,
                           lilKnobWidth);
    
    midGain.setBounds(bassGain.getBounds().getX() + lilKnobsDistance + lilKnobWidth,
                      bassGain.getBounds().getY(), 
                      lilKnobWidth,
                      lilKnobWidth);

    /* Setting high pos and dim relative to the mid one */
    highFrequency.setBounds(midFrequency.getBounds().getX() + lilKnobsDistance + lilKnobWidth,
                            midFrequency.getBounds().getY(), 
                            lilKnobWidth,
                            lilKnobWidth);

    highGain.setBounds(midFrequency.getBounds().getX() + lilKnobsDistance + lilKnobWidth,
                       midGain.getBounds().getY(), 
                       lilKnobWidth,
                       lilKnobWidth);

    analyzer.setBounds(60, 60, 990, 330);
}

void EqualizerAudioProcessorEditor::timerCallback()
{
    /*
    if (++framesElapsed > 100)
    {
        framesElapsed = 0;
        maxRmsLeft = -100.f;
        maxRmsRight = -100.f;
    }

    const auto leftGain = audioProcessor.getRmsLevel(0);
    const auto rightGain = audioProcessor.getRmsLevel(1);
    if (leftGain > maxRmsLeft)
        maxRmsLeft = leftGain;
    if (rightGain > maxRmsRight)
        maxRmsRight = rightGain;
    currentRmsValue.setText(String{ leftGain, 2 } + "   " + String{ rightGain, 2 }, sendNotification);
    maxRmsValue.setText(String{ maxRmsLeft, 2 } + "   " + String{ maxRmsRight, 2 }, sendNotification);

    DbMeterL.setLevel(leftGain);
    DbMeterL.repaint();

    DbMeterR.setLevel(rightGain);
    DbMeterR.repaint();
    */
}
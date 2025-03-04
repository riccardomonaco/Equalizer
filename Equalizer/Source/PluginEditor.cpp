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
    : AudioProcessorEditor (&p), audioProcessor (p),
    meterComponentL([this] { return audioProcessor.getMeterLevel(); }),
    meterComponentR([this] { return audioProcessor.getMeterLevel(); })
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

    addAndMakeVisible(meterComponentL);
    addAndMakeVisible(meterComponentR);

    //Setting the window size
    setSize(1500 * resizeFactor, 900 * resizeFactor);
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
        g.drawImage(ledOnImage, 193 * resizeFactor, 819 * resizeFactor, 50 * resizeFactor, 50 * resizeFactor, 0, 0, ledOnImage.getWidth(), ledOnImage.getHeight());
    }
    else repaint();

    if (audioProcessor.getStateLoPass()) {
        g.drawImage(ledOnImage, 870 * resizeFactor, 819 * resizeFactor, 50 * resizeFactor, 50 * resizeFactor, 0, 0, ledOnImage.getWidth(), ledOnImage.getHeight());
    }
    else repaint();
}

void EqualizerAudioProcessorEditor::resized()
{
    /* Dimensions variables */
    int knobWidth = 150 * resizeFactor;
    int knobHeight = 150 * resizeFactor;
    int filterKnobY = 600 * resizeFactor;
    int gainKnobY = 450 * resizeFactor;
    int spacingBKnobs = 250 * resizeFactor;
    
    //lopass hipass
    int lopasshipassY = 704 * resizeFactor;
    int lopasshipassWidth = 109 * resizeFactor;
    int lopassX = 910 * resizeFactor;
    int hipassX = 90 * resizeFactor;
    
    //volume faders
    int fadersWidth = 80 * resizeFactor;
    int fadersHeight = 362 * resizeFactor;
    int fadersImageOffset = 4 * resizeFactor;
    float fadersScaleFactor = 1.5 * resizeFactor;
    int inputGainFaderX = 1230 * resizeFactor;
    int outputGainFaderX = 1370 * resizeFactor;
    int inoutGainFaderY = 490 * resizeFactor;
   
    //sub range
    int subGainX = 244 * resizeFactor;
    int subGainY = 495.5 * resizeFactor;
    int subGainWidth = 68 * resizeFactor;
    int subFrequencyX = 244 * resizeFactor;
    int subFrequencyY = 623 * resizeFactor;
    int subFrequencyWidth = 68 * resizeFactor;
    
    //knobs 
    int lilKnobsDistance = 117 * resizeFactor;
    int lilKnobWidth = 68 * resizeFactor;

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

    analyzer.setBounds(60 * resizeFactor, 60 * resizeFactor, 990 * resizeFactor, 330 * resizeFactor);
    meterComponentL.setBounds(1245 * resizeFactor, 138 * resizeFactor, 40 * resizeFactor, 300 * resizeFactor);
    meterComponentR.setBounds(1321 * resizeFactor, 138 * resizeFactor, 40 * resizeFactor, 300 * resizeFactor);
}

void EqualizerAudioProcessorEditor::timerCallback()
{}

void EqualizerAudioProcessorEditor::plotGrid()
{
    std::vector<float> gridFrequencies = { 30.0f, 60.0f, 90.0f, 100.0f, 150.f, 200.0f, 350.f, 500.0f, 1000.0f, 2000.0f, 3500.f, 5000.0f, 8000.f, 12000.f, 20000.0f };

    for (float freq : gridFrequencies)
    {
        auto logMinFreq = std::log10(20.0f);
        auto logMaxFreq = std::log10(20000.0f);
        auto logFreq = std::log10(freq); 
        auto normalizedPos = (logFreq - logMinFreq) / (logMaxFreq - logMinFreq); 

        int xPos = (int)(60 + normalizedPos * (1050 - 60));

        g.setColour(juce::Colours::lightgrey);
        g.drawVerticalLine(xPos, 50, 200); 
        g.drawText(juce::String(freq) + " Hz", xPos + 2, 5, 50, 20, juce::Justification::centredLeft);
    }
}

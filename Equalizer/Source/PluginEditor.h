/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"
#include "SelectorLookAndFeel.h"
#include "AnalyzerComponent.h"
#include "MeterComponent.h"

//==============================================================================
/**
*/
class EqualizerAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    EqualizerAudioProcessorEditor (EqualizerAudioProcessor&);
    ~EqualizerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void plotGrid(juce::Graphics& g);

    AnalyzerComponent analyzer;
    //DbMeter variables
    MeterComponent meterComponentL;
    MeterComponent meterComponentR;


private:
    //Customizable style class
    CustomLookAndFeel customLookAndFeel;
    SelectorLookAndFeel selectorLookAndFeel;

    // Background image variable
    juce::Image bgImage;
    juce::Image ledOnImage;
    juce::Image glassDotsImage;

    float resizeFactor = 1;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EqualizerAudioProcessor& audioProcessor;

    juce::Slider inputGainFader;
    juce::Slider outputGainFader;

    juce::Slider subFrequency;
    juce::Slider subGain;

    juce::Slider bassFrequency;
    juce::Slider bassGain;

    juce::Slider midFrequency;
    juce::Slider midGain;

    juce::Slider highFrequency;
    juce::Slider highGain;

    juce::Slider lopassFrequency;
    juce::Label lopassFrequencyLabel;
    
    juce::Slider hipassFrequency;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputGainAtch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputGainAtch;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> subFrequencyAtch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> subGainAtch;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bassFrequencyAtch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bassGainAtch;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> midFrequencyAtch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> midGainAtch;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highFrequencyAtch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highGainAtch;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lopassFrequencyAtch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> hipassFrequencyAtch;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerAudioProcessorEditor)
};

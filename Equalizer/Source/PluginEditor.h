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
#include "AudioSpectrum.h"

//==============================================================================
/**
*/
class EqualizerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    EqualizerAudioProcessorEditor (EqualizerAudioProcessor&);
    ~EqualizerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //Customizable style class
    CustomLookAndFeel customLookAndFeel;
    SelectorLookAndFeel selectorLookAndFeel;

    //Spectrum Analyzer class
    AudioSpectrum audioSpectrum;

    // Background image variable
    juce::Image bgImage;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EqualizerAudioProcessor& audioProcessor;

    // Graphics components
        //int windowWidth;
        //int windowHeight;

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
    //juce::Button lopassActive;
    
    juce::Slider hipassFrequency;
    //juce::Button hipassActive;

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

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"


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
    
    //int inputGainFaderPosX = 1224;
    //inputGainFaderPosY = 

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputGainAtch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputGainAtch;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerAudioProcessorEditor)
};

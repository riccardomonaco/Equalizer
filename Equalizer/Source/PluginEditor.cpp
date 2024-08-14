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
    addAndMakeVisible(inputGainFader);
    addAndMakeVisible(outputGainFader);

    inputGainFader.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    outputGainFader.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);

    inputGainFader.setRange(-24.0, 12.0, 0.1);
    outputGainFader.setRange(-24.0, 12.0, 0.1);

    inputGainFader.setDoubleClickReturnValue(true, 0.0);
    outputGainFader.setDoubleClickReturnValue(true, 0.0);

    inputGainAtch = 
        std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.treeState, "input_gain", inputGainFader);

    setSize (750 * 2, 450 * 2);
}

EqualizerAudioProcessorEditor::~EqualizerAudioProcessorEditor()
{
}

//==============================================================================
void EqualizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    //Instantiating background image
    bgImage = juce::ImageCache::getFromMemory(BinaryData::EQ_UI_VOL_jpg, BinaryData::EQ_UI_VOL_jpgSize);
    
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
    inputGainFader.setBounds (610 * 2, 245 * 2, 10 * 2, 181 * 2);
    outputGainFader.setBounds (680 * 2, 245 * 2, 10 * 2, 181 * 2);
}

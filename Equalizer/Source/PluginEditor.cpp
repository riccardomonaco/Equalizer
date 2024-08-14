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
    setSize (750, 450);
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
}

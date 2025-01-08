/*
  ==============================================================================

    AudioSpectrum.h
    Created: 18 Nov 2024 5:24:57pm
    Author:  Dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AudioSpectrum : public juce::AudioVisualiserComponent
{
public:
    AudioSpectrum() : juce::AudioVisualiserComponent(2)
    {
        setBufferSize(512);
        setSamplesPerBlock(256);
        setColours(juce::Colours::darkgrey, juce::Colours::white);
        
    }
private:
};
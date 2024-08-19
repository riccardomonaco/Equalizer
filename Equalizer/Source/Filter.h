/*
  ==============================================================================

    Filter.h
    Created: 19 Aug 2024 5:21:18pm
    Author:  Dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Filter  : public juce::Component
{
public:
    Filter();
    ~Filter();

    int bufferSize;
    int sampleRate;

    void prepareToPlay(double sampleRate, int samplesPerBlock);

    float butterHiPass(float currentSample, float sliderValue);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};

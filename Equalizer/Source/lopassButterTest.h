/*
  ==============================================================================

    lopassButterTest.h
    Created: 25 Sep 2024 8:21:38am
    Author:  Dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/

class lopassButterTest : public juce::Component
{
public:
    lopassButterTest(double cutoffFreq);
    ~lopassButterTest() override;

    int sampleRate;
    double cutoffFreq;

    double processSample(double currSample);
    void updateCoefficients();
 
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(lopassButterTest);

    //Creating the filter object
    juce::dsp::IIR::Filter<double> bFilter;
    //Creating the coefficients reference object
    juce::dsp::IIR::Filter<double>::CoefficientsPtr bCoefficients;

};
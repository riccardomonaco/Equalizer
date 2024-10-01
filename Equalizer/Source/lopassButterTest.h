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
    lopassButterTest(double cutoffFreq, int order);
    ~lopassButterTest() override;

    int sampleRate;
    int order;
    double cutoffFreq;

    //double processSample(double currSample);
    //juce::Array<juce::dsp::IIR::Coefficients<double>> updateCoefficients(double cutoffFreq, juce::Array<juce::dsp::IIR::Filter<double>> butterFilters);
 
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(lopassButterTest);

    //Creating the filter object
    juce::Array<juce::dsp::IIR::Filter<double>> butterFilters;
    //Creating the coefficients reference object
    juce::dsp::IIR::Filter<double>::CoefficientsPtr bCoefficients;

};

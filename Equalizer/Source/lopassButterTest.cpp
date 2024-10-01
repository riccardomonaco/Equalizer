/*
  ==============================================================================

    lopassButterTest.cpp
    Created: 25 Sep 2024 8:21:38am
    Author:  Dev

  ==============================================================================
*/
#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846

#include <JuceHeader.h>
#include <cmath>
#include "lopassButterTest.h"

//==============================================================================

lopassButterTest::lopassButterTest(double cutoffFreq, int order)
{
    sampleRate = 44100;
    cutoffFreq = cutoffFreq;
    order = order;
    //updateCoefficients(cutoffFreq, this->butterFilters);
}

lopassButterTest::~lopassButterTest()
{
    this->sampleRate = 44100;
    this->cutoffFreq = 1000;
    //bCoefficients = juce::dsp::IIR::Coefficients<double>::makeLowPass(sampleRate, cutoffFreq);
    //bFilter = juce::dsp::IIR::Filter<double>::Filter(bCoefficients);
}

/*
juce::Array<juce::dsp::IIR::Coefficients<double>> lopassButterTest::updateCoefficients(double cutoffFreq,
                                                                                       juce::Array<juce::dsp::IIR::Filter<double>> butterFilters)
{    
    int order = 2;
    juce::Array<juce::dsp::IIR::Coefficients<double>> arrayFilters;

    if (order % 2 == 1)
    {
        arrayFilters.add(*juce::dsp::IIR::Coefficients<double>::makeFirstOrderLowPass(sampleRate, cutoffFreq));

        for (int i = 0; i < order / 2; ++i)
        {
            auto Q = 1.0 / (2.0 * std::cos((i + 1.0) * M_PI / order));
            arrayFilters.add(*juce::dsp::IIR::Coefficients<double>::makeLowPass(sampleRate, cutoffFreq,
                static_cast<double> (Q)));

            juce::dsp::IIR::Filter<double> tF;
            tF.coefficients = arrayFilters[i];
            butterFilters.add(tF);
        }
    }
    else
    {
        for (int i = 0; i < order / 2; ++i)
        {
            auto Q = 1.0 / (2.0 * std::cos((2.0 * i + 1.0) * M_PI / (order * 2.0)));
            arrayFilters.add(*juce::dsp::IIR::Coefficients<double>::makeLowPass(sampleRate, cutoffFreq,
                static_cast<double> (Q)));

            juce::dsp::IIR::Filter<double> tF;
            tF.coefficients = arrayFilters[i];
            butterFilters.add(tF);
        }
    }

    return arrayFilters;
 }
 */
/*double lopassButterTest::processSample(double currSample)
{
    double output = 0;

    for (int i = 0; i < order / 2; ++i) 
    {
        butterFilters[i].processSample(currSample);
    }

    return output;
}*/
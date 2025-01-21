/*
  ==============================================================================

    AudioSpectrum.h
    Created: 21 Jan 2025 5:36:30pm
    Author:  Dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AudioSpectrum  : public juce::Component
{
public:
    enum
    {
        fftOrder = 11,             // [1]
        fftSize = 1 << fftOrder,  // [2]
        scopeSize = 512             // [3]
    };

    AudioSpectrum();
    ~AudioSpectrum() override;

    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void pushNextSampleIntoFifo(float sample);
    void drawNextFrameOfSpectrum();
    void timerCallback();
    void drawFrame(juce::Graphics& g);

private:
    juce::dsp::FFT forwardFFT;                      // [4]
    juce::dsp::WindowingFunction<float> window;     // [5]

    float fifo[fftSize];                           // [6]
    float fftData[2 * fftSize];                    // [7]
    int fifoIndex = 0;                              // [8]
    bool nextFFTBlockReady = false;                 // [9]
    float scopeData[scopeSize];                    // [10]

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSpectrum)
};

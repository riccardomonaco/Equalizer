/*
  ==============================================================================

    AnalyzerComponent.h
    Created: 22 Jan 2025 4:23:58pm
    Author:  Dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AnalyzerComponent : public juce::Component,
                          public juce::Timer
{
public:
    AnalyzerComponent()
        : forwardFFT(fftOrder),
        window(fftSize, juce::dsp::WindowingFunction<float>::hann)
    {
        startTimerHz(30);
    }


    //==============================================================================
    void pushNextBlockIntoFifo(const juce::dsp::AudioBlock<float>& audioBlock) noexcept
    {
        auto numSamples = static_cast<int>(audioBlock.getNumSamples());
        auto numChannels = static_cast<int>(audioBlock.getNumChannels());

        for (int sample = 0; sample < numSamples; ++sample)
        {
            float mixedSample = 0.0f;

            // Somma i canali per ottenere un segnale mono
            for (int channel = 0; channel < numChannels; ++channel)
            {
                mixedSample += audioBlock.getSample(channel, sample);
            }

            mixedSample /= static_cast<float>(numChannels); // Media tra i canali (se più di uno)

            fifo[fifoIndex++] = mixedSample;

            // Se il FIFO è pieno, copiamo i dati per l'FFT
            if (fifoIndex == fftSize)
            {
                if (!nextFFTBlockReady)
                {
                    juce::zeromem(fftData, sizeof(fftData));
                    memcpy(fftData, fifo, sizeof(fifo));
                    nextFFTBlockReady = true;
                }

                fifoIndex = 0;
            }
        }
    }

    void drawNextFrameOfSpectrum()
    {
        // first apply a windowing function to our data
        window.multiplyWithWindowingTable(fftData, fftSize);       // [1]

        // then render our FFT data..
        forwardFFT.performFrequencyOnlyForwardTransform(fftData);  // [2]

        auto mindB = -100.0f;
        auto maxdB = 0.0f;

        for (int i = 0; i < scopeSize; ++i)                         // [3]
        {
            auto skewedProportionX = 1.0f - std::exp(std::log(1.0f - (float)i / (float)scopeSize) * 0.2f);
            auto fftDataIndex = juce::jlimit(0, fftSize / 2, (int)(skewedProportionX * (float)fftSize * 0.5f));
            auto level = juce::jmap(juce::jlimit(mindB, maxdB, juce::Decibels::gainToDecibels(fftData[fftDataIndex])
                - juce::Decibels::gainToDecibels((float)fftSize)),
                mindB, maxdB, 0.0f, 1.0f);

            scopeData[i] = level;                                   // [4]
        }
    }

    void timerCallback() override
    {
        if (nextFFTBlockReady)
        {
            drawNextFrameOfSpectrum();
            nextFFTBlockReady = false;
            repaint();
        }
    }

    void drawFrame(juce::Graphics& g)
    {

        for (int i = 1; i < scopeSize; ++i)
        {
            auto width = getLocalBounds().getWidth();
            auto height = getLocalBounds().getHeight();

            g.drawLine({ (float)juce::jmap(i - 1, 0, scopeSize - 1, 0, width),
                                  juce::jmap(scopeData[i - 1], 0.0f, 1.0f, (float)height, 0.0f),
                          (float)juce::jmap(i,     0, scopeSize - 1, 0, width),
                                  juce::jmap(scopeData[i],     0.0f, 1.0f, (float)height, 0.0f) });
        }
    }

    void paint(juce::Graphics& g) override
    {
        g.setColour(juce::Colours::whitesmoke.withAlpha(0.5f));
        drawFrame(g);
    }

    enum
    {
        fftOrder = 11,             
        fftSize = 1 << fftOrder,  
        scopeSize = 512             
    };

private:
    juce::dsp::FFT forwardFFT;                      
    juce::dsp::WindowingFunction<float> window;     

    float fifo[fftSize];                           
    float fftData[2 * fftSize];                    
    int fifoIndex = 0;                              
    bool nextFFTBlockReady = false;                 
    float scopeData[scopeSize];                    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnalyzerComponent)
};

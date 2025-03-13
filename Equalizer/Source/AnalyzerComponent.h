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
        sampleRate = 44100.0;
        startTimerHz(30);
    }

    ~AnalyzerComponent() {
        stopTimer();
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
        window.multiplyWithWindowingTable(fftData, fftSize);

        // then render our FFT data..
        forwardFFT.performFrequencyOnlyForwardTransform(fftData);

        auto mindB = -21.0f;
        auto maxdB = 9.0f;

        for (int i = 0; i < scopeSize; ++i)
        {
            // Mapping logaritmico della frequenza
            auto logMinFreq = std::log10(20.0f);  // Frequenza minima udibile (20 Hz)
            auto logMaxFreq = std::log10(20000.0f); // Frequenza massima udibile (20 kHz)
            auto logFreq = logMinFreq + (logMaxFreq - logMinFreq) * ((float)i / (float)scopeSize);
            auto freq = std::pow(10.0f, logFreq);

            // Trova l'indice corrispondente nell'array FFT
            auto fftDataIndex = juce::jlimit(0, fftSize / 2, (int)((freq / (sampleRate / 2)) * (fftSize / 2)));

            // Converte in dB e normalizza
            auto level = juce::jmap(juce::jlimit(mindB, maxdB,
                juce::Decibels::gainToDecibels(fftData[fftDataIndex]) - juce::Decibels::gainToDecibels((float)fftSize) / 2),
                mindB, maxdB, 0.0f, 1.0f);
            scopeData[i] = level;
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
            auto width = getBounds().getWidth();
            auto height = getBounds().getHeight();

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

    void setSampleRate(double sRate) {
        sampleRate = sRate;
    }

    enum
    {
        fftOrder = 12,             
        fftSize = 1 << fftOrder,  //2^fftOrder
        scopeSize = 1024 //Finestra di dati
    };

private:
    juce::dsp::FFT forwardFFT;                      
    juce::dsp::WindowingFunction<float> window;     
   
    double sampleRate;
    float fifo[fftSize];                           
    float fftData[2 * fftSize];                    
    int fifoIndex = 0;                              
    bool nextFFTBlockReady = false;                 
    float scopeData[scopeSize];                    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnalyzerComponent)
};

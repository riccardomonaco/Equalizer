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
                          private juce::Timer
{
public:
    AnalyzerComponent()
        : forwardFFT(fftOrder),
        window(fftSize, juce::dsp::WindowingFunction<float>::blackman),
        fifo(fftSize)
    {
        setOpaque(true);
        startTimerHz(30);
    }

    ~AnalyzerComponent() override
    {
    }

    //==============================================================================

    void pushAudioSamples(juce::dsp::AudioBlock<float> audioBlock)
    {
        const float* channelData = audioBlock.getChannelPointer(0); // Ottieni i dati del primo canale

        int start1, size1, start2, size2;

        // Prepara il FIFO per la scrittura (in base al numero di campioni nel blocco)
        fifo.prepareToWrite(audioBlock.getNumSamples(), start1, size1, start2, size2);

        // Copia i dati nel FIFO (prima parte)
        if (size1 > 0)
            std::copy(channelData, channelData + size1, fifoBuffer + start1);

        // Copia i dati nel FIFO (seconda parte, se il buffer è "circular")
        if (size2 > 0)
            std::copy(channelData + size1, channelData + size1 + size2, fifoBuffer + start2);

        // Segnala che la scrittura è stata completata
        fifo.finishedWrite(size1 + size2);
    }

    //==============================================================================
    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::black);
        g.setOpacity(0.7);
        g.setColour(juce::Colours::blue);
        drawFrame(g);
    }

    void timerCallback() override
    {
        int start1, size1, start2, size2;

        // Prepara il FIFO per la lettura
        fifo.prepareToRead(fftSize, start1, size1, start2, size2);

        if (size1 + size2 >= fftSize)
        {
            // Copia i dati dal FIFO nel buffer FFT (prima parte)
            if (size1 > 0)
                std::copy(fifoBuffer + start1, fifoBuffer + start1 + size1, fftData);

            // Copia i dati dal FIFO nel buffer FFT (seconda parte, se necessario)
            if (size2 > 0)
                std::copy(fifoBuffer + start2, fifoBuffer + start2 + size2, fftData + size1);

            // Prepara lo spettro per il disegno
            drawNextFrameOfSpectrum();

            // Segnala che la lettura è completata
            fifo.finishedRead(size1 + size2);

            // Aggiorna l'interfaccia grafica
            repaint();
        }
    }

    void drawNextFrameOfSpectrum()
    {
        window.multiplyWithWindowingTable(fftData, fftSize);
        forwardFFT.performFrequencyOnlyForwardTransform(fftData);

        auto mindB = -100.0f;
        auto maxdB = 0.0f;

        for (int i = 0; i < scopeSize; ++i)
        {
            // Calcola l'indice corrispondente nella FFT per ogni punto dello spettro
            auto proportionX = (float)i / (float)(scopeSize - 1);
            auto fftDataIndex = juce::jlimit(0, fftSize / 2, (int)(proportionX * (fftSize * 0.5f)));

            // Converti il valore FFT in decibel
            auto level = juce::jmap(
                juce::jlimit(mindB, maxdB,
                    juce::Decibels::gainToDecibels(fftData[fftDataIndex])
                    - juce::Decibels::gainToDecibels((float)fftSize)),
                mindB, maxdB, 0.0f, 1.0f);

            scopeData[i] = level; // Salva il livello normalizzato

            if (i < 10) // Logga i primi 10 valori
                juce::Logger::writeToLog("scopeData[" + juce::String(i) + "] = " + juce::String(scopeData[i]));
        }

    }

    void drawFrame(juce::Graphics& g)
    {
        for (int i = 1; i < scopeSize; ++i)
        {
            auto width = getLocalBounds().getWidth();
            auto height = getLocalBounds().getHeight();

            // Mappa i valori di scopeData su coordinate pixel
            g.drawLine(
                (float)juce::jmap(i - 1, 0, scopeSize - 1, 0, width),
                juce::jmap(scopeData[i - 1], 0.0f, 1.0f, (float)height, 0.0f),
                (float)juce::jmap(i, 0, scopeSize - 1, 0, width),
                juce::jmap(scopeData[i], 0.0f, 1.0f, (float)height, 0.0f));
        }
    }

    enum
    {
        fftOrder = 11,             // [1]
        fftSize = 1 << fftOrder,  // [2]
        scopeSize = 512             // [3]
    };

private:
    juce::dsp::FFT forwardFFT;                      // [4]
    juce::dsp::WindowingFunction<float> window;     // [5]

    juce::AbstractFifo fifo;                           // [6]
    float fifoBuffer[fftSize] = { 0 };
    float fftData[2 * fftSize] = { 0 };
    float scopeData[scopeSize] = { 0 };                   // [10]

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnalyzerComponent)
};

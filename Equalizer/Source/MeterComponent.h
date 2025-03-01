#pragma once

#include <JuceHeader.h>

class MeterComponent : public juce::Component, public juce::Timer
{
public:
    MeterComponent(std::function<float()>&& valueFunction)
        : valueSupplier(std::move(valueFunction))
    {
        startTimerHz(30);
    }

    void paint(juce::Graphics& g) override
    {
        const auto bounds = getLocalBounds().toFloat();
        const int numDots = 12;  // Numero di pallini nel meter
        const float dotSize = bounds.getHeight() / (numDots + 2);  // Dimensione dei pallini
        const float spacing = dotSize * 1.5f;  // Distanza tra i pallini

        // Mappa il livello dB (-60 dB a +6 dB) in un range normalizzato [0, 1]
        const float level = juce::jlimit(0.f, 1.f, juce::jmap(valueSupplier(), -30.f, 6.f, 0.f, 1.f));

        for (int i = 0; i < numDots; ++i)
        {
            float normalizedIndex = static_cast<float>(i) / (numDots - 1); // Valore tra 0 e 1
            float activationThreshold = normalizedIndex; // Più in alto, più attivato con livello basso

            // Decide il colore del pallino in base al volume
            juce::Colour dotColor = juce::Colours::black.withAlpha(0.3f); // Pallini vuoti semi-trasparenti

            if (level >= activationThreshold)
            {
                // Mappa il livello nel gradiente (verde -> giallo -> rosso)
                dotColor = juce::Colour::fromHSV(
                    juce::jmap(normalizedIndex, 0.0f, 1.0f, 0.3f, 0.0f), // Da verde a rosso
                    1.0f,  // Saturazione massima
                    1.0f,  // Luminosità massima
                    1.0f   // Opacità piena
                );
            }

            // Disegna il cerchio
            float x = bounds.getCentreX();
            float y = bounds.getBottom() - (i + 1) * spacing;
            //g.fillAll(juce::Colours::black);

            g.setColour(dotColor);
            g.fillEllipse(x - dotSize / 2, y - dotSize / 2, dotSize, dotSize);

        }
        g.drawImageAt(glassDotsImage, 0, 0);
    }

    void timerCallback() override
    {
        repaint();
    }

private:
    std::function<float()> valueSupplier;
    juce::Image glassDotsImage = juce::ImageCache::getFromMemory(BinaryData::GLASS_OVERLAY_png, BinaryData::GLASS_OVERLAY_pngSize);
};

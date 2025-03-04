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
        const int numDots = 10;  // Numero di pallini nel meter
        const float dotSize = bounds.getHeight() / (numDots + 2);  // Dimensione dei pallini
        const float spacing = dotSize * 1.2f;  // Distanza tra i pallini

        // Mappa il livello dB (-60 dB a +6 dB) in un range normalizzato [0, 1]
        const float level = juce::jlimit(0.f, 1.f, juce::jmap(valueSupplier(), -21.f, 9.f, 0.f, 1.f));

        for (int i = 0; i < numDots; ++i)
        {
            float normalizedIndex = static_cast<float>(i) / (numDots - 1); // Valore tra 0 e 1
            float activationThreshold = normalizedIndex; // Più in alto, più attivato con livello basso

            // Decide il colore del pallino in base al volume
            juce::Colour dotColor = juce::Colours::black.withAlpha(0.f); // Pallini vuoti semi-trasparenti

            if (level >= activationThreshold)
            {
                // Mappa il livello nel gradiente (verde -> giallo -> rosso)
                dotColor = juce::Colour::fromHSV(
                    0.6f,  // Tonalità fissa nel range del blu
                    juce::jmap(normalizedIndex, 0.0f, 1.0f, 0.4f, 0.2f), // Da saturazione minore a maggiore
                    juce::jmap(normalizedIndex, 0.0f, 1.0f, 0.6f, 0.9f), // Da scuro a chiaro
                    1.0f   // Opacità piena
                );
            }

            // Disegna il cerchio
            float x = bounds.getCentreX();
            float y = bounds.getBottom() - (i + 1) * spacing + dotSize / 2 + 2;

            g.drawImage(bgDotImage, x - bgDotImage.getWidth() / 2, y - bgDotImage.getHeight() / 2 + 2, bgDotImage.getWidth(), bgDotImage.getHeight(), 0, 0, bgDotImage.getWidth(), bgDotImage.getHeight());
            g.setColour(dotColor);
            g.fillEllipse(x - dotSize / 2, y - dotSize / 2, dotSize, dotSize);
            g.setOpacity(1.0f);
            g.drawImage(glassDotImage, x - dotSize / 2 - 2, y - dotSize / 2 - 2, glassDotImage.getWidth(), glassDotImage.getHeight(), 0, 0, glassDotImage.getWidth(), glassDotImage.getHeight());
        }
    }

    void timerCallback() override
    {
        repaint();
    }

private:
    std::function<float()> valueSupplier;
    juce::Image glassDotImage = juce::ImageCache::getFromMemory(BinaryData::GLASS_DOT_png, BinaryData::GLASS_DOT_pngSize);
    juce::Image bgDotImage = juce::ImageCache::getFromMemory(BinaryData::BG_DOT_png, BinaryData::BG_DOT_pngSize);
    juce::Image glassOverlayImage = juce::ImageCache::getFromMemory(BinaryData::GLASS_OVERLAY_png, BinaryData::GLASS_OVERLAY_pngSize);
};

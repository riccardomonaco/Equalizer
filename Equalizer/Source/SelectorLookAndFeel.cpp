/*
  ==============================================================================

    SelectorLookAndFeel.cpp
    Created: 12 Nov 2024 10:53:11pm
    Author:  Dev

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SelectorLookAndFeel.h"

//==============================================================================
SelectorLookAndFeel::SelectorLookAndFeel()
{
    selectorImage = juce::ImageCache::getFromMemory(BinaryData::KNOB_SELECTOR_png, BinaryData::KNOB_SELECTOR_pngSize);
}

SelectorLookAndFeel::~SelectorLookAndFeel()
{
}

void SelectorLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
    juce::Slider& slider)
{
    const int imageWidth = selectorImage.getWidth();
    const int imageHeight = selectorImage.getHeight();

    auto radius = width * 0.5f;
    auto centerX = x + width * 0.5f;
    auto centerY = y + height * 0.5f;

    float scaleX = static_cast<float>(width) / selectorImage.getWidth();
    float scaleY = static_cast<float>(width) / selectorImage.getHeight();

    // Definizione dei 4 step fissi
    constexpr int numSteps = 4;
    constexpr float stepValues[numSteps] = { 0.26f, 0.42f, 0.58f, 0.73f };

    // Trova il valore più vicino tra gli step
    float closestStep = stepValues[0];
    for (int i = 1; i < numSteps; ++i)
    {
        if (std::abs(sliderPos - stepValues[i]) < std::abs(sliderPos - closestStep))
        {
            closestStep = stepValues[i];
        }
    }

    // Calcola l'angolo corretto per il valore più vicino
    auto angle = rotaryStartAngle + closestStep * (rotaryEndAngle - rotaryStartAngle);

    juce::AffineTransform transform =
        juce::AffineTransform::scale(scaleX, scaleY)
        .rotated(angle, centerX, centerY);

    g.drawImageTransformed(selectorImage, transform);
}
/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 14 Aug 2024 10:58:52pm
    Author:  Dev

  ==============================================================================
*/

#pragma once

#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel()
{
    faderImage = juce::ImageCache::getFromMemory(BinaryData::FADER_png, BinaryData::FADER_pngSize);
    lhKnobImage = juce::ImageCache::getFromMemory(BinaryData::KNOB_ROTARY_png, BinaryData::KNOB_ROTARY_pngSize);
}

CustomLookAndFeel::~CustomLookAndFeel()
{
}

void CustomLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
     float sliderPos, float minSliderPos, float maxSliderPos,
     const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    /**************
    * DEBUG COLORS
    ***************/
    //g.setColour(juce::Colours::blue);
    //g.fillRect(x, y, width, height);

    // Dimensioni e posizione dell'immagine/*
    const int imageWidth = faderImage.getWidth();
    const int imageHeight = faderImage.getHeight();

    const int imageX = x + (width - imageWidth) / 2;
    const int imageY = sliderPos - (imageHeight / 2);

    // Disegna l'immagine
    g.drawImage(faderImage, imageX, imageY, imageWidth, imageHeight, 0, 0, imageWidth, imageHeight);
}

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
    juce::Slider& slider)
{
    /**************
    * DEBUG COLORS
    ***************/
    //g.setColour(juce::Colours::blue);
    //g.fillRect(x, y, width, height);

    const int imageWidth = lhKnobImage.getWidth();
    const int imageHeight = lhKnobImage.getHeight();

    auto radius = width * 0.5f;
    auto centerX = x + width * 0.5f;
    auto centerY = y + height * 0.5f;

    float scaleX = static_cast<float>(width) / lhKnobImage.getWidth();
    float scaleY = static_cast<float>(width) / lhKnobImage.getHeight();

    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    juce::AffineTransform transform = juce::AffineTransform::scale(scaleX, scaleY).rotated(angle, centerX, centerY);

    g.drawImageTransformed(lhKnobImage, transform);
}   

void CustomLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label)
{

}


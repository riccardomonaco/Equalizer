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

void CustomLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
     float sliderPos, float minSliderPos, float maxSliderPos,
     const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    // Dimensioni e posizione dell'immagine/*
    const int imageWidth = faderImage.getWidth();
    const int imageHeight = faderImage.getHeight();

    const int imageX = x + (width - imageWidth) / 2;
    const int imageY = sliderPos - (imageHeight / 2);

    // Evita il clipping per permettere al thumb di essere disegnato fuori dai confini dello slider
    //g.setColour(juce::Colours::transparentBlack); // Non disegna nulla nel clipping
    //g.reduceClipRegion(slider.getX() - imageWidth, slider.getY() - imageWidth, imageWidth * 2, imageHeight * 2);

    // Disegna l'immagine
    g.drawImage(faderImage, imageX, imageY, imageWidth, imageHeight, 0, 0, imageWidth, imageHeight);
}

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
    juce::Slider& slider)
{
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    // Dimensioni e posizione dell'immagine/*
    const int imageWidth = lhKnobImage.getWidth();
    const int imageHeight = lhKnobImage.getHeight();

    const int imageX = x + (width - imageWidth) / 2;
    const int imageY = sliderPos - (imageHeight / 2);

    // Evita il clipping per permettere al thumb di essere disegnato fuori dai confini dello slider
    g.setColour(juce::Colours::red); // Non disegna nulla nel clipping
    //g.reduceClipRegion(slider.getX() - imageWidth, slider.getY() - imageWidth, imageWidth * 2, imageHeight * 2);

    // Disegna l'immagine
    g.drawImage(lhKnobImage, imageX, imageY, imageWidth, imageHeight, 0, 0, imageWidth, imageHeight);

}
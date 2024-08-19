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
    thumbImage = juce::ImageCache::getFromMemory(BinaryData::FADER_png, BinaryData::FADER_pngSize);
}

void CustomLookAndFeel::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const juce::Slider::SliderStyle style, juce::Slider& slider)
{
    // Dimensioni e posizione dell'immagine/*
    const int imageWidth = thumbImage.getWidth();
    const int imageHeight = thumbImage.getHeight();

    const int imageX = x + (width - imageWidth) / 2;
    const int imageY = sliderPos - (imageHeight / 2);

    // Evita il clipping per permettere al thumb di essere disegnato fuori dai confini dello slider
    g.setColour(juce::Colours::transparentBlack); // Non disegna nulla nel clipping
    //g.reduceClipRegion(slider.getX() - imageWidth, slider.getY() - imageWidth, imageWidth * 2, imageHeight * 2);

    // Disegna l'immagine
    g.drawImage(thumbImage, imageX, imageY, imageWidth, imageHeight, 0, 0, imageWidth, imageHeight);
}
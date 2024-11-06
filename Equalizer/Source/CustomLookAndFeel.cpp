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

    g.drawImage(lhKnobImage, x, y, imageWidth, imageHeight, 0, 0, imageWidth, imageHeight);
}   

void CustomLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label)
{
    /*
    g.setColour(juce::Colour(juce::uint8(255), 255, 255, 1.0f));
    g.fillRoundedRectangle(label.getLocalBounds().toFloat(), 3.0f);


    if (!label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const juce::Font font(getLabelFont(label));

        g.setColour(juce::Colour(juce::uint8(0), 0, 0, 1.0f));
        g.setFont(font);

        auto textArea = getLabelBorderSize(label).subtractedFrom(label.getLocalBounds());

        g.drawFittedText(label.getText(), textArea, label.getJustificationType(),
            juce::jmax(1, (int)(textArea.getHeight() / font.getHeight())),
            label.getMinimumHorizontalScale());

        g.setColour(juce::Colour(juce::uint8(255), 255, 255, 0.1f));
    }
    else if (label.isEnabled())
    {
        g.setColour(label.findColour(juce::Label::outlineColourId));
    }
    */

    //g.fillRoundedRectangle(label.getLocalBounds().toFloat(), 3.0f);
}

/*
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
 */
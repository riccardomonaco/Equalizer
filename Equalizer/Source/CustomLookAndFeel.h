/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 14 Aug 2024 10:58:52pm
    Author:  Dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel();

    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
         float sliderPos, float minSliderPos, float maxSliderPos,
         const juce::Slider::SliderStyle, juce::Slider& slider) override;

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
         float sliderPos, float rotaryStartAngle, float rotaryEndAngle, 
         juce::Slider& slider) override;

private:
    juce::Image faderImage;
    juce::Image lhKnobImage;
};

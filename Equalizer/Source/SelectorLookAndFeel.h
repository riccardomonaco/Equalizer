/*
  ==============================================================================

    SelectorLookAndFeel.h
    Created: 12 Nov 2024 10:53:11pm
    Author:  Dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SelectorLookAndFeel  : public juce::LookAndFeel_V4
{
public:
    SelectorLookAndFeel();
    ~SelectorLookAndFeel() override;

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
        juce::Slider& slider) override;

private:
    juce::Image selectorImage;
};

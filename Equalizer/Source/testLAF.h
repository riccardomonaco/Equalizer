/*
  ==============================================================================

    testLAF.h
    Created: 6 Nov 2024 1:48:52am
    Author:  Dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class testLAF : public juce::LookAndFeel_V4
{
public:
    testLAF();
    ~testLAF() override;

    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const juce::Slider::SliderStyle, juce::Slider& slider) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (testLAF)
};

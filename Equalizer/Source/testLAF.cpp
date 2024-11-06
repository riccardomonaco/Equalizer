/*
  ==============================================================================

    testLAF.cpp
    Created: 6 Nov 2024 1:48:52am
    Author:  Dev

  ==============================================================================
*/

#include <JuceHeader.h>
#include "testLAF.h"

//==============================================================================
testLAF::testLAF()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

testLAF::~testLAF()
{
}

void testLAF::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const juce::Slider::SliderStyle, juce::Slider& slider)
{
    g.setColour(juce::Colours::red);
}

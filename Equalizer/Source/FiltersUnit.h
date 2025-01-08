/*
  ==============================================================================

    FiltersUnit.h
    Created: 8 Jan 2025 11:15:28am
    Author:  Dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FiltersUnit  : public juce::Component
{
public:
    FiltersUnit();
    ~FiltersUnit() override;
    void initFilters();
    void process(juce::dsp::ProcessContextReplacing<float>(AudioBlock));
    void prepare(juce::dsp::ProcessSpec specs);

private:
    juce::Array<juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
                juce::dsp::IIR::Coefficients<float>>> Filters;
    juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
                                   juce::dsp::IIR::Coefficients<float>> subFilter;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FiltersUnit)
};

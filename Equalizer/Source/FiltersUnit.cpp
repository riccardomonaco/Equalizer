/*
  ==============================================================================

    FiltersUnit.cpp
    Created: 8 Jan 2025 11:15:28am
    Author:  Dev

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FiltersUnit.h"

//==============================================================================
FiltersUnit::FiltersUnit()
{
}

FiltersUnit::~FiltersUnit()
{
}

void FiltersUnit::initFilters() {
/*
    *subFilter.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 30, 0.0001f, 1.0f);
    Filters.add(subFilter);*/
}

void FiltersUnit::process(juce::dsp::ProcessContextReplacing<float>(AudioBlock)) {
/*
    for (auto& f : Filters) {
        f.process(juce::dsp::ProcessContextReplacing<float>(AudioBlock));
    }*/
}

void FiltersUnit::prepare(juce::dsp::ProcessSpec specs) {
/*
    for (auto& f : Filters) {
        f.prepare(specs);
    }*/
}

# Equalizer
 
```c++
juce::AudioProcessorEditor* EqualizerAudioProcessor::createEditor()
{
    /****
        GENERIC EDITOR RETURNED FOR TEST PURPOSES
    ****/

    //return new EqualizerAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

```
___

Viene returnato un editor generico che viene programmaticamente popolato in base ai parametri audio dichiarati. Non è tweakabile esteticamente serve solo a scopo di test.

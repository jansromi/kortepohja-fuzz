/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class KortepohjaFuzzAudioProcessorEditor : public juce::AudioProcessorEditor,
    public Slider::Listener
{
public:
    KortepohjaFuzzAudioProcessorEditor (KortepohjaFuzzAudioProcessor&);
    ~KortepohjaFuzzAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    KortepohjaFuzzAudioProcessor& audioProcessor;

    Slider gainSlider;
    Slider porinaSlider;
    Slider toneSlider;

    Label gainLabel;
    Label porinaLabel;
    Label toneLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KortepohjaFuzzAudioProcessorEditor)
};

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KortepohjaFuzzAudioProcessorEditor::KortepohjaFuzzAudioProcessorEditor (KortepohjaFuzzAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 330);

    // Setup gain
    gainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(0.0, 48.0);
    gainSlider.setValue(0.0);
    gainSlider.addListener(this);

    addAndMakeVisible(gainSlider);

    // Setup pörinä
    porinaSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    porinaSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    porinaSlider.setRange(0.0, 100.0);
    porinaSlider.setValue(0.0);
    porinaSlider.addListener(this);


    addAndMakeVisible(porinaSlider);

    // Setup tone
    toneSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    toneSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    toneSlider.setRange(0.0, 100.0);
    toneSlider.setValue(50.0);
    toneSlider.addListener(this);


    addAndMakeVisible(toneSlider);
    //addAndMakeVisible(toneLabel);
}

KortepohjaFuzzAudioProcessorEditor::~KortepohjaFuzzAudioProcessorEditor()
{

}

//==============================================================================
void KortepohjaFuzzAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void KortepohjaFuzzAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    Rectangle<int> dialArea = area.removeFromTop(area.getHeight() / 2);
    Rectangle<int> labelArea = area.removeFromBottom(area.getHeight() / 3);

    gainSlider.setBounds(dialArea.removeFromLeft(area.getWidth() / 3)); //3
    porinaSlider.setBounds(dialArea.removeFromRight(area.getWidth() / 3)); //3
    toneSlider.setBounds(dialArea.removeFromRight(area.getWidth() / 3)); // 3

    gainLabel.setBounds(labelArea.removeFromLeft(area.getWidth() / 3));
    gainLabel.setText("Gain", dontSendNotification);
    gainLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(gainLabel);

    porinaLabel.setBounds(labelArea.removeFromLeft(area.getWidth() / 3));
    porinaLabel.setText("PÖRINÄ!", dontSendNotification);
    porinaLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(porinaLabel);

    toneLabel.setBounds(labelArea.removeFromLeft(area.getWidth() / 3));
    toneLabel.setText("Laatu", dontSendNotification);
    toneLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(toneLabel);

}

void KortepohjaFuzzAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &gainSlider)
    {
        audioProcessor.rawVolume = pow(10, gainSlider.getValue() / 20);
        DBG("moro :D");
    }

    if (slider == &porinaSlider)
    {
        // do something with pörinä value
        DBG("moro :D");
    }

    if (slider == &toneSlider) 
    {
        // do something with tone value
        DBG("moro :D");
    }



}
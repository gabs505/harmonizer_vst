/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class HarmonizerAudioProcessorEditor  : public AudioProcessorEditor,private ComboBox::Listener//, private Timer//private MidiKeyboardStateListener
{
public:
    HarmonizerAudioProcessorEditor (HarmonizerAudioProcessor&);
    ~HarmonizerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HarmonizerAudioProcessor& processor;
	
	Label pluginLabel;
	ComboBox chordList;
	void chordListChanged();
	MidiKeyboardState keyboardState;
	
	
	void comboBoxChanged(ComboBox* box) override;

	//void timerCallback() override
	//{
	//	if (processor.chordIdx != processor.lastIdx) {
	//		chordList.setSelectedItemIndex(processor.chordIdx);
	//		processor.lastIdx = processor.chordIdx;
	//		stopTimer();
	//	}
	//	
	//	
	//}

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HarmonizerAudioProcessorEditor)
};

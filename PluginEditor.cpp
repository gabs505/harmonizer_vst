/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HarmonizerAudioProcessorEditor::HarmonizerAudioProcessorEditor (HarmonizerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 100);
	
	chordList.addItem("major", 1);
	chordList.addItem("minor", 2);
	chordList.addItem("maj7", 3);
	chordList.addItem("7", 4);
	chordList.addItem("m7", 5);
	chordList.addItem("m7b5", 6);
	chordList.addItem("dim", 7);
	
	chordList.setSelectedItemIndex(0);
	chordList.onChange = [this] { chordListChanged(); };

	addAndMakeVisible(pluginLabel);
	pluginLabel.setText("Choose chord type: ", dontSendNotification);
	pluginLabel.attachToComponent(&chordList, false);
	
	


	addAndMakeVisible(&chordList);
}

HarmonizerAudioProcessorEditor::~HarmonizerAudioProcessorEditor()
{
}

//==============================================================================
void HarmonizerAudioProcessorEditor::paint (Graphics& g)
{
   
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (30.0f);
    
}

void HarmonizerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	
	int width = 100;
	int height = 20;
	chordList.setBounds(40, 40,width,height);
}


void HarmonizerAudioProcessorEditor::comboBoxChanged(ComboBox* box) {

	processor.chordIdx= chordList.getSelectedId();
}

void  HarmonizerAudioProcessorEditor::chordListChanged() {
	processor.chordIdx = chordList.getSelectedId();
}


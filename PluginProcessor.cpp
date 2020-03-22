/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HarmonizerAudioProcessor::HarmonizerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                      .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                      )
#endif
{
	
}

HarmonizerAudioProcessor::~HarmonizerAudioProcessor()
{
}

//==============================================================================
//void HarmonizerAudioProcessor::MidiKeyboardStateListener
//::handleNoteOff(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) {
//	
//}
const String HarmonizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HarmonizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HarmonizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HarmonizerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HarmonizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HarmonizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HarmonizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HarmonizerAudioProcessor::setCurrentProgram (int index)
{
}

const String HarmonizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void HarmonizerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void HarmonizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void HarmonizerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HarmonizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HarmonizerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

	

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }

	MidiBuffer newMidiBuffer;
	/*MidiMessage third;
	MidiMessage fifth;
	MidiMessage prime;*/
	/*int prime_num;
	int channel;
	int velocity;*/
	int time;
	MidiMessage m;
	/*MidiMessage next;*/
	
	/*if (!midiMessages.isEmpty()) {*/

	
	
	//t = chordGenerator.chordMap[chordName][0];
	//t = 3;
	//f = chordGenerator.chordMap[chordName][0]; //!!!!!!!!!!!!!!!1tu jest problem!!!!!!!!!!!!!!!!!!!!!!!!1

		

		for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
		{
			 

			if (m.isNoteOn())
			{
				counter++;
				
				if (counter%2!=0) {
					m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), m.getVelocity());
					newMidiBuffer.addEvent(m, time);
					for (auto const& value : chordGenerator.chordMap[chordIdx]) {
						MidiMessage el = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber() + value, m.getVelocity());
						newMidiBuffer.addEvent(el, time);
					}
					lastPrime = m;

				}
				else {
		
					
					MidiMessage el_off = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber(), m.getVelocity());
					newMidiBuffer.addEvent(el_off, time);
					for (auto const& value : chordGenerator.chordMap[chordIdx]) {
						el_off = MidiMessage::noteOff(lastPrime.getChannel(), lastPrime.getNoteNumber() + value, lastPrime.getVelocity());
						newMidiBuffer.addEvent(el_off, time);
					}
						
					//Wczeœniejsza dobra wersja z podmian¹ tercji----------------------------------------------------------------------------
					/*for (auto const& value : chordGenerator.chordMap[chordIdx]) {
					
						if (value == 3) {

							MidiMessage el_off = MidiMessage::noteOff(lastPrime.getChannel(), lastPrime.getNoteNumber() + value, lastPrime.getVelocity());
							MidiMessage el_on = MidiMessage::noteOn(lastPrime.getChannel(), lastPrime.getNoteNumber() + 4, lastPrime.getVelocity());
							newMidiBuffer.addEvent(el_off, time);
							newMidiBuffer.addEvent(el_on, time);
							third = el_on;

						}
						else if (value == 4) {

							MidiMessage el_off = MidiMessage::noteOff(lastPrime.getChannel(), lastPrime.getNoteNumber() + value, lastPrime.getVelocity());
							MidiMessage el_on = MidiMessage::noteOn(lastPrime.getChannel(), lastPrime.getNoteNumber() + 3, lastPrime.getVelocity());
							newMidiBuffer.addEvent(el_off, time);
							newMidiBuffer.addEvent(el_on, time);
							third = el_on;

						}
						
	
					}*/
					//---------------------------------------------------------------------------------------------------
					
					lastIdx = chordIdx;
					
					if (m.isMidiNoteBlack(m.getNoteNumber())) {//klawisz czarny - zmiana na akord dominantowy
						chordIdx = 4;
					}
					else { //klawisz bia³y - zmiana trybu na mollowy
						if (chordIdx == 1 || chordIdx == 3 || chordIdx == 4) { //if major then minor
							chordIdx = 2;
						}
						else if (chordIdx == 2 || chordIdx == 5 || chordIdx == 6 || chordIdx == 7) {
							chordIdx = 1;
						}
					}
					

					for (auto const& value : chordGenerator.chordMap[chordIdx]) {
						MidiMessage el_on = MidiMessage::noteOn(lastPrime.getChannel(), lastPrime.getNoteNumber() + value, lastPrime.getVelocity());
						newMidiBuffer.addEvent(el_on, time);
					}
					chordIdx = lastIdx;
				}
				
			

			}
			else if (m.isNoteOff())
			{	
				counter++;
				
				//removing 7th
				MidiMessage key_off = MidiMessage::noteOff(lastPrime.getChannel(), lastPrime.getNoteNumber() + seventh, lastPrime.getVelocity());
				newMidiBuffer.addEvent(key_off, time);
				//removing 3rds
				key_off = MidiMessage::noteOff(lastPrime.getChannel(), lastPrime.getNoteNumber() + 3, lastPrime.getVelocity());
				newMidiBuffer.addEvent(key_off, time);
				key_off = MidiMessage::noteOff(lastPrime.getChannel(), lastPrime.getNoteNumber() + 4, lastPrime.getVelocity());
				newMidiBuffer.addEvent(key_off, time);
				
				for (int& value : chordGenerator.chordMap[chordIdx]) {
					MidiMessage el_off = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber() + value, m.getVelocity());
					newMidiBuffer.addEvent(el_off, time);
				}

				for (int& value : chordGenerator.chordMap[chordIdx]) {
					MidiMessage el_off = MidiMessage::noteOff(lastPrime.getChannel(), lastPrime.getNoteNumber() + value, lastPrime.getVelocity());
					newMidiBuffer.addEvent(el_off, time);
				}

			
				
			}
			else if (m.isAftertouch())
			{
			}
			else if (m.isPitchWheel())
			{
			}
			
			

		}
		midiMessages.swapWith(newMidiBuffer);
		

	

}

//==============================================================================
bool HarmonizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HarmonizerAudioProcessor::createEditor()
{
    return new HarmonizerAudioProcessorEditor (*this);
}

//==============================================================================
void HarmonizerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HarmonizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HarmonizerAudioProcessor();
}

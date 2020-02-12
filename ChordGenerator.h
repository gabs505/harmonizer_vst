#pragma once
#include "../JuceLibraryCode/JuceHeader.h"



class ChordGenerator
{
public:
	ChordGenerator() {
		

		chordMap[1] = std::vector<int>{ 4,7 }; //major
		chordMap[2] = std::vector<int>{ 3,7 };//minor
		chordMap[3] = std::vector<int>{ 4,7,11 };//maj7
		chordMap[4] = std::vector<int>{ 4,7,10 };//7
		chordMap[5] = std::vector<int>{ 3,7,10 };//m7
		chordMap[6] = std::vector<int>{ 3,6,10 };//m7b5
		chordMap[7] = std::vector<int>{ 3,6,9 };//dim
	}
	
	std::map<int, std::vector < int >> chordMap;

	
private:
	
};
#include "Date.h"
#include "ClassInfo.h"

#include <iostream>
#include <fstream>
#include <vector>

#include <cstring>

#include <sstream>

using std::fstream;
using std::string;
using std::endl;
using std::cin;
using std::cout;
using std::vector;
using std::to_string;

unsigned int findStringReturnIndex(vector<char> giantCharVector, string myString) {
	unsigned int stringLength = myString.length();
	unsigned int vectorLength = giantCharVector.size();

	unsigned int countNumMatchingChars = 0;

	for (unsigned int i = 0; i < vectorLength; i++) {

		for (unsigned int j = 0; j < stringLength; j++) {
			// if two chars are equal
			if (giantCharVector.at(i) == myString.at(j)) {
				// then check the next two chars.
				i++;
				countNumMatchingChars++;

				if (countNumMatchingChars == stringLength - 1) {
					// go back to the beginning
					return i - stringLength;
				}


			} else {
				// start over with the first of myString
				// and start with next of vector
				i++;
				j = 0;
				countNumMatchingChars = 0;
			}
		}	
	}

	return 0;
}


// if on either side of ':', there are integers, then 
// mark that spot as potientially a time. save the index somewhere.
vector<unsigned int> potentialTimeAtThisIndex(vector<char> giantCharVector) {
	vector<unsigned int> listOfIndexesPotentialTimes;
	for (unsigned int i = 0; i < giantCharVector.size(); i++){
		if ( (giantCharVector.at(i) >= 48 && giantCharVector.at(i) <= 57) &&
		     (giantCharVector.at(i + 1) == ':') &&
		     (giantCharVector.at(i + 2) >= 48 && giantCharVector.at(i + 2) <= 57)) {
		
			listOfIndexesPotentialTimes.push_back(i + 1);
		}
	}

	return listOfIndexesPotentialTimes;

}


// now this time have index be the first letter of what you think is a day of the week
vector<unsigned int> potentialDayAtThisIndex(vector<char> giantCharVector, vector<string> weekdays) {

	vector<unsigned int> listOfIndexesPotentialDays;

	string myString;

	for (unsigned int i = 0; i < giantCharVector.size(); i++) {

		for (unsigned int j = 0; j < weekdays.size(); j++) {

			string weekString = weekdays.at(j);

			if (findStringReturnIndex(giantCharVector, weekString) > 0) {
				listOfIndexesPotentialDays.push_back(findStringReturnIndex(giantCharVector, weekString));
	
			}

		}
	}

	return listOfIndexesPotentialDays;

}




// TODO: This ACTUALLY now returns the index of the first dot
unsigned int numOfZoomLinks(vector<char> giantCharVector) {

	unsigned int z = 0;

	for (unsigned int i = 0; i < giantCharVector.size() - 5; ++i) {

		if (giantCharVector.at(i) == '.' &&
		    giantCharVector.at(i + 1) == 'z' &&
		    giantCharVector.at(i + 2) == 'o' && 
		    giantCharVector.at(i + 3) == 'o' &&
		    giantCharVector.at(i + 4) == 'm' &&
		    giantCharVector.at(i + 5) == '.' ) {

		    z = i;
		}
	
	}

	return z;
}


string returnZoomLink(vector<char> giantCharVector, unsigned int i) {
	//https://brandeis.zoom.us/j/91324843664
	// to the left, look for a space, a '\', a ''', a '?', basically anything
	// that isn't letters, the colon, dots, or forwardslashes.
	// to the right, look for a space
	string zoomLink; 
	char cursor;
	int index;
	string tempString;
	index = i;
	cursor = giantCharVector.at(index);

	while(cursor != ' ' && cursor != '=' && cursor != '(' && cursor != ')' 
			&& index > 0) {
		index--;
		cursor = giantCharVector.at(index);
		string tempString(1, cursor);		
		tempString = tempString + zoomLink;
		zoomLink = tempString;
	}

	index = i;
	cursor = giantCharVector.at(index);
	//theoretically, i is:
	//
	// .  z  o  o  m  .
	// ^ here
	
	while (cursor != ' ' && cursor != '(' && cursor != ')' && 
			index < giantCharVector.size() - 2) {
		index++;
		cursor = giantCharVector.at(index);
		string tempString(1, cursor);
		tempString = zoomLink + tempString;
		zoomLink = tempString;
	}

	if (i != 0) {
		return zoomLink;
	} else {
		return "probably not a zoom link in this syllabus.";
	}
}


int main() {

	// import all static files (months, things that arent names, etc):
	vector<string> allMonthStrings;
	fstream fs;
	fs.open("monthKeywords.txt");
	string temp;
	while(!fs.eof()) {
		fs >> temp;
		allMonthStrings.push_back(temp);
	}
	fs.close();

	// notNames.txt
	fs.open("notNames.txt");
	vector<string> notNamesStrings;
	while(!fs.eof()) {
		fs >> temp;
		notNamesStrings.push_back(temp);
	}
	fs.close();

	// titlesOfProf.txt
	fs.open("titlesOfProf.txt");
	vector<string> titlesOfProf;
	while(!fs.eof()) {
		fs >> temp;
		titlesOfProf.push_back(temp);
	}
	fs.close();

	// mon.txt
	fs.open("mon.txt");
	vector<string> mon;
	while(!fs.eof()) {
		fs >> temp;
		mon.push_back(temp);
	}
	fs.close();

	// tues.txt
	fs.open("tues.txt");
	vector<string> tues;
	while(!fs.eof()) {
		fs >> temp;
		tues.push_back(temp);
	}
	fs.close();

	// wed.txt
	fs.open("wed.txt");
	vector<string> wed;
	while(!fs.eof()) {
		fs >> temp;
		wed.push_back(temp);
	}
	fs.close();

	// thurs.txt
	fs.open("thurs.txt");
	vector<string> thurs;
	while(!fs.eof()) {
		fs >> temp;
		thurs.push_back(temp);
	}
	fs.close();

	// fri.txt
	fs.open("fri.txt");
	vector<string> fri;
	while(!fs.eof()) {
		fs >> temp;
		fri.push_back(temp);
	}
	fs.close();

	// weekdays.txt
	fs.open("weekdays.txt");
	vector<string> weekdays;
	while(!fs.eof()) {
		fs >> temp;
		weekdays.push_back(temp);
	}
	fs.close();

	// here we gooooo
	fstream FS;

	string filename;

	cout << "enter filename: ";
	cin >> filename;
	FS.open(filename);

	char tempChar;
	string tempString;
	vector<char> giantCharVector;

	while(!FS.eof()) {

		getline(FS, tempString);
		for (unsigned int i = 0; i < tempString.length(); ++i) {
			tempChar = tempString.at(i);

			giantCharVector.push_back(tempChar);
		}

	}

	unsigned int numWhitespace = 0;
	unsigned int numNumbers = 0;
	unsigned int numPeriods = 0;
	unsigned int numColons = 0 ;
	unsigned int numCommas = 0;
	unsigned int numMonths = 0;

	for (unsigned int i = 0; i < giantCharVector.size(); ++i) {
		if (giantCharVector[i] == ' ') {
			numWhitespace++;

		} else if (giantCharVector[i] == '.') {
			numPeriods++;

		} else if (giantCharVector[i] == ':') {
			numColons++;

		} else if (giantCharVector[i] == ',') {
			numCommas++;

		} else if (giantCharVector[i] >= 48 && giantCharVector[i] <= 57) {
			numNumbers++;

		}

	}


	cout << endl;


	// some stats I was going to use but now seem waaay less useful
	cout << "numWhitespace: " << numWhitespace << endl;

	cout << "numPeriods: " << numPeriods << endl;
	cout << "numColons: " << numColons << endl;
	cout << "numCommas: " << numCommas << endl;
	cout << "numNumbers: " << numNumbers << endl;
	cout << "index of a zoom link: " << numOfZoomLinks(giantCharVector) << endl;
	cout << "zoom link: " << returnZoomLink(giantCharVector, 
					numOfZoomLinks(giantCharVector));
	cout << endl;
	cout << endl;

	vector<unsigned int> timeIndexes;
	timeIndexes = potentialTimeAtThisIndex(giantCharVector);

	for (unsigned int i = 0; i < timeIndexes.size(); ++i) {

		if (giantCharVector.at(timeIndexes.at(i) - 3) != '-') {
			for (int j = -2; j < 3; ++j) {
				cout << giantCharVector.at(  timeIndexes.at(i) + j  );
				
			} 
			cout << "    ";
		}
	}


	return 0;
}



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


// TODO: clean up hour:minute


// if on either side of ':', there are integers, then 
// mark that spot as potientially a time. save the index somewhere.
vector<unsigned int> potentialTimeAtThisIndex(vector<char> giantCharVector) {


	vector<unsigned int> listOfIndexesPotentialTimes;

	for (unsigned int i = 0; i < giantCharVector.size(); i++){
		if ( (giantCharVector[i] >= 48 && giantCharVector[i] <= 57) &&
		     (giantCharVector[i + 1] == ':') &&
		     (giantCharVector[i + 2] >= 48 && giantCharVector[i + 2] <= 57)) {
			
			listOfIndexesPotentialTimes.push_back(i + 1);

		}
	}

	return listOfIndexesPotentialTimes;



}


// now this time have index be the first letter of what you think is a day of the week
vector<unsigned int> potentialDayAtThisIndex(vector<char> giantCharVector) {


	vector<unsigned int> listOfIndexesPotentialDays;

	// FIXME(this MWF stuff)
	for (unsigned int i = 0; i < giantCharVector.size(); i++){
		if ( (giantCharVector[i] == 'M') &&
		     (giantCharVector[i + 1] == 'W') &&
		     (giantCharVector[i + 2] == 'F')) {
			
			listOfIndexesPotentialDays.push_back(i);

		} else if ( (giantCharVector[i] == 'M') &&
		     (giantCharVector[i + 1] == 'W')){
			listOfIndexesPotentialDays.push_back(i);

		} else if ( (giantCharVector[i] == 'T') &&
				(( (giantCharVector[i + 1] == '-') &&
				  (giantCharVector[i + 2] == 'T') &&
				  (giantCharVector[i + 3] == 'h') )   ||
				
				 ( (giantCharVector[i + 1] == 'T') &&
				  (giantCharVector[i + 2] == 'h') ))) {
			listOfIndexesPotentialDays.push_back(i);
		}
	}

	return listOfIndexesPotentialDays;



}






// TODO: have this return a vector or string with zoom link
unsigned int numOfZoomLinks(vector<char> giantCharVector) {

	unsigned int z = 0;

	for (unsigned int i = 0; i < giantCharVector.size() - 5; ++i) {

		if (giantCharVector.at(i) == '.' &&
		    giantCharVector.at(i + 1) == 'z' &&
		    giantCharVector.at(i + 2) == 'o' && 
		    giantCharVector.at(i + 3) == 'o' &&
		    giantCharVector.at(i + 4) == 'm' &&
		    giantCharVector.at(i + 5) == '.' ) {
		       z++;	
		}
	
	}

	return z;
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

	for (unsigned int i = 0; i < allMonthStrings.size(); ++i) {
		cout << allMonthStrings.at(i) << endl;
	}
	fs.close();



// notNames.txt
	fs.open("notNames.txt");
	vector<string> notNamesStrings;
	while(!fs.eof()) {
		fs >> temp;
		notNamesStrings.push_back(temp);
	}

	for (unsigned int i = 0; i < notNamesStrings.size(); ++i) {
		cout << notNamesStrings.at(i) << endl;
	}
	fs.close();



// titlesOfProf.txt
	fs.open("titlesOfProf.txt");
	vector<string> titlesOfProf;
	while(!fs.eof()) {
		fs >> temp;
		titlesOfProf.push_back(temp);
	}

	for (unsigned int i = 0; i < titlesOfProf.size(); ++i) {
		cout << titlesOfProf.at(i) << endl;
	}
	fs.close();



// testKeywords.txt
// not doing this one, doesn't seem that needed.




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
			cout << tempChar;
			giantCharVector.push_back(tempChar);
		}

	}

	unsigned int numWhitespace = 0;
	unsigned int numNumbers = 0;
	unsigned int numPeriods = 0;
	unsigned int numColons = 0 ;
	unsigned int numCommas = 0;
	unsigned int numMonths = 0;

	//			size - 1, because the last one
	//			is repeated because of .eof()
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

//	cout << "numOfMonths: " << numOfMonths(allMonthStrings, giantCharVector);

	cout << "numZoomLinks: " << numOfZoomLinks(giantCharVector) << endl;


	cout << endl;
	cout << "The most important thing I can do is get MWF xx:yy to aa::bb times";


	vector<unsigned int> timeIndexes;
	timeIndexes = potentialTimeAtThisIndex(giantCharVector);

	cout << "special colons at: ";
	for (unsigned int i = 0; i < timeIndexes.size(); i++) {
		cout << timeIndexes.at(i) << "   ";
	}
	cout << endl;

	for (unsigned int j = 0; j < timeIndexes.size(); j++) {

		for (unsigned int i = timeIndexes.at(j) - 2; i < timeIndexes.at(j) + 3; i++) {
			cout << giantCharVector.at(i);
		}
		cout << "    ";

	}

	vector<unsigned int> dayIndexes;
	dayIndexes = potentialDayAtThisIndex(giantCharVector);

	for (unsigned int i = 0; i < dayIndexes.size(); i++) {
		cout << dayIndexes.at(i) << "   ";
	}
	cout << endl;

	for (unsigned int j = 0; j < dayIndexes.size(); j++) {

		for (unsigned int i = dayIndexes.at(j) - 2; i < dayIndexes.at(j) + 3; i++) {
			cout << giantCharVector.at(i);
		}
		cout << "    ";

	}

	cout << endl;
	
	return 0;
}



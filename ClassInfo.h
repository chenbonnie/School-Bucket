#ifndef CLASSINFO_H
#define CLASSINFO_H

#include <iostream>

#include <string>

#include "Date.h"

using std::string;

class ClassInfo {

	public:
//	string dateString = "default_date";

//	string infoString = "default_info";

	string profName = "default_prof_name";

	string classCode = "default_class_code";

	unsigned int numberOfExams = 0;

	unsigned int numberOfQuizzes = 0;

	unsigned int numberOfHomeworks = 0;

	unsigned int numberOfDatesMentioned = 0;



};

	// these will become capitol
	// letters when that day has
	// the class on it
	char daysOfWeekMeeting[] = 
{'s', 'm', 't', 'w', 't', 'f', 's'};
	unsigned int hourMeeting[] = {25, 25, 25, 25, 25, 25, 25};
	unsigned int minuteMeeting[] =
{61, 61, 61, 61, 61, 61, 61};


	// max amount of zoom links:
	// 365
	// max amount of passwords:
	// 365

	string zoomLinks[365];
	string zoomPasswords[365];

	unsigned int numDaysClass = 0;

	Date startDate;

	Date endDate;

#endif




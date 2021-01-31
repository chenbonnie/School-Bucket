

def findStringReturnIndex(giantCharVector, myString):
    '''Find string in a larger string (syllabus), returns first letter index in larger string.'''

    stringLength = myString.length()
    countNumMatchingChars = 0

    for i in range(len(giantCharVector)):
        for j in stringLength:
            if giantCharVector[i] == myString[j]:
                i = i + 1
                countNumMatchingChars = countNumMatchingChars + 1
                if countNumMatchingChars == stringLength:
                    return i - stringLength
            else:
                i += 1
                j = 0
                countNumMatchingChars = 0
    return 0		

def potentialTimeAtThisIndex(giantCharVector):
    '''Determine a list of potential times in a file/string, return an array.'''

    listOfIndexesPotentialTimes = []

    for i in range(len(giantCharVector)):
        if (ord(giantCharVector[i]) >= 48 and ord(giantCharVector[i]) <= 57 and giantCharVector[i + 1] == ':' and ord(giantCharVector[i + 2]) >= 48 and ord(giantCharVector[i + 2]) <= 57):
            listOfIndexesPotentialTimes.append(i + 1)       # add index of colon to list

    return listOfIndexesPotentialTimes

##// now this time have index be the first letter of what you think is a day of the week

def potentialDayAtThisIndex(giantCharVector, weekdays):
    '''Determine a list of potential days of the week in a file/string, return an array.'''
    
    #TODO: define week array in place
    listOfIndexesPotentialDays = []

    for i in range(len(giantCharVector)):
        for j in weekdays:
            weekdayIndex = findStringReturnIndex(giantCharVector, j)
            if weekdayIndex > 0:    
                listOfIndexesPotentialDays.append(weekdayIndex)

    return listOfIndexesPotentialDays


# TODO: This ACTUALLY now returns the index of the first dot in the zoom link
def returnIndexOfFirstDot(giantCharVector):

    z = 0
    for i in range(len(giantCharVector)- 5):
        if (giantCharVector[i:i+6] == '.zoom.'):        #FIXME: check for out of range errors
            z = i

    return z
           
           
def returnZoomLink(giantCharVector, origIndex):
	##// to the left, look for a space, a '\', a ''', a '?', basically anything
	##// that isn't letters, the colon, dots, or forwardslashes.
	##// to the right, look for a space
    

    tempString = ""
    index = origIndex
    cursor = giantCharVector[index]

    # walk backwards to beginning of link and store characters
    while((cursor != ' ') and (cursor != '=') and (cursor != '(') and (cursor != ')') and (index > 0)):
        index -= 1
        cursor = giantCharVector[index]
        
    tempString = giantCharVector[index:origIndex]
        
    
    index = origIndex
    cursor = giantCharVector[index]
	#//theoretically, i is:
	#//
	#// .  z  o  o  m  .
	#// ^ here
	
    while (cursor != ' ' and cursor != '(' and cursor != ')' and index < len(giantCharVector) - 2):
	    index += 1
	    cursor = giantCharVector[index]
        
    tempString += giantCharVector[origIndex:index]
	

    if index != 0:
        return tempString
    else:
        return "probably not a zoom link in this syllabus."
    


#int main() {
def main():

	##// import all static files (months, things that arent names, etc):

	
        ##// notNames.txt
#	fs.open(""notNames.txt"");
#	vector<string> notNamesStrings;
#	while(!fs.eof()) {
#		fs >> temp;
#		notNamesStrings.push_back(temp);
#	}
#	fs.close();
#

##	// titlesOfProf.txt
#	fs.open(""titlesOfProf.txt"");
#	vector<string> titlesOfProf;
#	while(!fs.eof()) {
#		fs >> temp;
#		titlesOfProf.push_back(temp);
#	}
#	fs.close();


##       // weekdays.txt
#	fs.open(""weekdays.txt"");
#	vector<string> weekdays;
#	while(!fs.eof()) {
#		fs >> temp;
#		weekdays.push_back(temp);
#	}
#	fs.close();

#	// here we gooooo
#	fstream FS;

#	string filename;
        
    
    filename = input("enter filename: ")

    giantCharVector = [ ]
    
    file = open(filename, 'r')
    for line in file:
        giantCharVector.append(line)
    
    giantCharVector = "".join(giantCharVector)
	    

#    numWhitespace = 0
#    numNumbers = 0
#    numPeriods = 0
#    numColons = 0
#    numCommas = 0
#    numMonths = 0

#FIXME: this is still in C++
    
#	for i in range(len(giantCharVector):
#		
#        if (giantCharVector[i] == ' ') {
#			numWhitespace++;
#
#        for i in i < giantCharVector.size():
#            if giantCharVector[i] == ' ':
#                numWhitespace = numWhitespace + 1
#            else if giantCharVector[i] == '.':
#		numPeriods = numPeriods + 1
#            else if giantCharVector[i] == ':':
#		numColons = numColons + 1
#	    else if giantCharVector[i] == ',':
#		numCommas = numCommas + 1
#            else if giantCharVector[i] >= 48 and giantCharVector[i] <= 57:
#		numNumbers = numNumbers + 1


#    print("\n")
#
#	##// some stats I was going to use but now seem waaay less useful
#    print("numWhitespace: " numWhitespace)
#    
#    print("numPeriods: " numPeriods)
#    print("\n")
#    print("numColons: " numColons)
#    print("\n")
#    
#    print("numCommas: " numCommas)
#    print("\n")
#    
#    print("numNumbers: " numNumbers)
#    print("\n")
#    
#    print("index of a zoom link: " numOfZoomLinks(giantCharVector))
#    print("\n")
    
    print("zoom link: ", returnZoomLink(giantCharVector, returnIndexOfFirstDot(giantCharVector)))
    print("\n")
    print("\n")


    timeIndexes = potentialTimeAtThisIndex(giantCharVector)


    for i in range(len(timeIndexes)):
        if giantCharVector[timeIndexes[i] - 3] != '-':
            print(giantCharVector[i-2:i+3])
#            j = -2 in j < 3 :                       # FIXME: make this readable, lol
#            giantCharVector.at(timeIndexes.at(i) + j)
#            print("\n")

    return 0

main()
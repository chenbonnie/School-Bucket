     # By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Names:        Macy Drew  
# Section:      TAMUHack
# File:         Zoom Link Organization
# Date:         1-30-2021

import datetime


class zoomLink:
    
    # members:
    # classLink ------ string/dict (if plural=True); link to zoom room
    # classID -------- string; name of class, e.g. MATH 304
    # section -------- int; section number, e.g. 512
    # plural --------- bool; if true, multiple class links (by date)
    # N.B. members ("attributes") are declared implicitly in methods
    
    # methods:
    def __init__(self, classLink, classID, section, plural): # N.B. __init__ has two underscores on each side :P
        self.classID = classID
        self.section = section
        self.plural = plural            # if plural=True...
        self.classLink = classLink      # ...classLink is a dict.
    
    def printClassLink(self):
        '''Prints class name/section and zoom link, returns (string) zoom link.'''
        if not self.plural:     # same room all semester
            print(f"{self.classID}-{self.section} class link:")
            print(self.classLink)
            return self.classLink
        else:                   # custom rooms each class; keys = datetimes, values = links
            today = datetime.datetime.today()
            print(today)
            for key in self.classLink.keys():
                print(key)
                if key >= today:                # will print and return the next session's link
                    print(self.classLink[key])
                    return self.classLink[key]
                else:
                    continue
            print(f"There are no more {self.classID}-{self.section} class links this semester.")
            return



class zoomSchedule:
    
    # members:
    # listOfLinks ----- array of zoomLink objects
    
    # methods:
    def __init__(self, listOfLinks):
        self.listOfLinks = listOfLinks
    
    # pop-up for next class of the day ***Could be added to Navigate app***
    def findClassLink(self, classToFind):   # N.B. section not required; included above for user's info
        '''Finds specified class and prints its zoom link, returns (string) specified zoom link or error string.'''
        for i in self.listOfLinks:
            if i.classID == classToFind:
                i.printClassLink()
                return i.classLink
        return "Class not found"        # returns error message if class does not exist
    
    # add a button for this
    # TODO: manual inputs? link to a form?
    def addClass(self, newClass):
        '''Add new zoomLink object to end of listOfLinks, return void.'''
        self.listOfLinks.append(newClass)
        
    def printSchedule(self, filename):
        '''Prints whole schedule of zoom links to given files name, returns void.'''
        with open(filename, 'w') as file:
            file.write("hello")
        
    
# ---------------------------------- TESTING ----------------------------------
        
a = zoomLink("www.zoom.com", "MATH 304", 512, plural=False)

b = zoomLink("www.macydrew2023.weebly.com", "STAT 211", 506, plural=False)

c = zoomLink({datetime.datetime(2021, 1, 4, 3, 55):"www.coolmathgames.com",
              datetime.datetime(2021, 1, 6, 3, 55):"www.weebly.com",
              datetime.datetime(2021, 2, 17, 3, 55):"www.coolmathgames2.com"}, "CSCE 312", 510, plural=True)

a.printClassLink()
b.printClassLink()
c.printClassLink()



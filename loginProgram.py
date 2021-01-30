# By submitting this assignment, I agree to the following:
#   "Aggies do not lie, cheat, or steal, or tolerate those who do."
#   "I have not given or received any unauthorized aid on this assignment."
#
# Names:        Macy Drew  
# Section:      TAMUHack
# Assignment:   
# Date:         1-30-21

#-------------------------LOG IN PROCEDURE-------------------------------------

# usernames stored in a list to make sure they match
# the summative hash will then be used to access user data in a dict

'''Bells and Whistles:
  - add function for changing/recovering password
  - add function for deleting account/data
'''

from os import system, name
from time import sleep



def screen_clear():
   if name == 'nt':
      _ = system('cls')
   else:
      _ = system('clear')

# methods
def addUser(userDict):
    '''Adds a user's username and password to the given dict, returns hash of new login.'''
    
    username = input("Please enter a username:")
    while len(username) > 16:
        print("Username must be 16 characters or less;")
        username = input("Please enter a username:")
        
    password = input("Please enter a strong password:")
    while len(password) < 8:
        print("Password must be 8 characters or more;")
        username = input("Please enter a password:")

    userDict.update({hash(username+password):[]})
    userDict[0].append(username)         # design is such that dict[0] is a username list
    
    return hash(username + password)


def backupUsers(filename, userDict):
    '''Writes given list of users to a given file, returns void.''' 
    
    # create file for users
    with open(filename, 'w') as file:
        for key in userDict[0]:
            file.write(key)
    return


def backupUserData(filename, userDict):
    '''Writes given list of users' data to a given file, returns void.''' 
    
     # create file for users' protected data
    with open(filename, 'w') as file:
        for key in userDict.keys():
            if key == 0:        # do not include login data
                continue
            file.write(str(key) + ',' + ','.join(userDict[key]))
    return


def loadData(filename_users, filename_hashData):
    '''Fills given user dict from given .csv file, returns user dict.'''
    
    userDict = {0:[]}
    with open(filename_users, 'r') as file:
        for line in file:
            userDict[0].append(line)
            
    with open(filename_hashData, 'r') as file:
        for line in file:
            tempArray = line.strip().split(',')
            userDict.update({int(tempArray[0]):tempArray[1:]})
            
    return userDict


def addData(currentHash, userDict):
    
    print("Do you want to add to your account data? y/n")
    addData = input()
    
    while addData == 'y' or addData == 'Y':
        tempVar = input("Enter data: ")
        userDict[currentHash].append(tempVar)
        print("Current account data: \n", userDict[currentHash])
        addData = input("Do you want to add more to your account data? y/n\n")
        
    print("Logging out...goodbye!")
#    in terminal:
#    screen_clear()
    sleep(2.5)
    print('\n' * 30)
    return
            


def login(userDict):
    '''Asks for login info and either verifies login and grants access to user's
    "protected" info, or asks to make a new account; returns void.'''
    
    username = input("Please enter your username:")
    if username == "quit":      # will stop loop later in main function
        return 0
    
    password = input("Please enter your password:")
    
    currentHash = hash(username + password)
    
    if currentHash not in userDict.keys():
        print("Username or password is incorrect.  Create new account? y/n")
        newAccount = input()
        if newAccount == 'y' or newAccount == 'Y':
            currentHash = addUser(userDict)
        else:
            return -1
    
    print("\nCurrent stored data for " + username + ':')
    print(userDict[currentHash])
    
    return currentHash
        

# "users data" class
#  userDict = {0:{}}       # key 0 refers to a list containing the usernames
    
# skeleton crew: userDict = {0:["admin"], -5329453070961561034:["Hello World!"]}


def main():
    
    userDict = loadData("users.csv", "data.csv")
    
    print("1. Login\n2. Create new account")
    newAccount = int(input())
    
    if newAccount == 1:         # loop login until correct
        var = login(userDict)
        while var == -1:
            var == login(userDict)
    else:                       # add new user then login
        addUser(userDict)
        var = login(userDict)
        while var == -1:
            var == login(userDict)
        
    # allow user to add data
    addData(var, userDict)
    
    # backup current login data
    backupUsers("users.csv", userDict)
    backupUserData("data.csv", userDict)

    return var

main()
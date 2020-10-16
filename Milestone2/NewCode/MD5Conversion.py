# Schuyler Enneman
# CS-499
# Python Authentication System (Converted from Java)

# Note: Requires veterinarian.txt, zookeeper.txt, and admin.txt

# MD5 Conversion Code

# Imports
import sys
import hashlib


# Function for converting user password into MD5 Hash
# This function uses the hashlib library to convert the user password (string) into hash

def MD5ConversionFunc(userPassword, Type):
    original = userPassword
    userType = Type

    hashed = hashlib.md5(original.encode())  # uses hashlib to encode hashed password

    hashed2 = hashed.hexdigest()  # returns the digest for the hashed pass; returns as string containing only -
    # hexadecimals

    passCheck(hashed2, userType)

    return hashed2  # Returns hashed password for unit testing


# Function for checking the inputted password against the passwords stored in the lists
# The passwords are pre-determined in the lists

def passCheck(password, zooType):
    userPassword = password
    userType = zooType

    # Lists to store pre-determined passwords

    keeperPass = ["85ee6ee9541c8f294772e182147a5f42", "09a2ccf1476407f61867d4de719b0b97"]
    adminPass = ["92446c031dbe789c917c6da0d7ab44b9", "1a6f3e7c72ef9fe22e0e9c21843e91d1"]
    vetPass = ["cb8df1b3cb170724ad07ad5f64c099fe", "23245ffe3d90c2c9a7a702ab34df44bd"]

    # Check if user password is within one of the lists; also checks user type to ensure correct file is viewed
    # Once verification is performed, FileOpen is called to open the correct file

    if userPassword in keeperPass and userType == "zookeeper":
        FileOpen(userType)

    elif userPassword in adminPass and userType == "admin":
        FileOpen(userType)

    elif userPassword in vetPass and userType == "veterinarian":
        FileOpen(userType)

    else:
        print("\nInvalid Password!\n")  # If password is invalid ; returns to login loop


# File for opening and reading .txt files. Each file is related to one of the three user types

def FileOpen(userFileSelect):
    if userFileSelect == "zookeeper":  # Reads the zookeeper file and prints
        file1 = open("zooKeeper.txt", "r")
        print(file1.read())
        print("\n")
        LogOut()

    if userFileSelect == "admin":  # Reads the admin file and prints
        file2 = open("admin.txt", "r")
        print(file2.read())
        print("\n")
        LogOut()

    if userFileSelect == "veterinarian"  # Reads the veterinarian file and prints
        file3 = open("veterinarian.txt", "r")
        print(file3.read())
        print("\n")
        LogOut()


# Logout function - Simple menu interface to see if user wants to log out of the system or not

def LogOut():

    logoutLoop = True

    print("Logout/return to menu or exit?")
    print("1 - Logout and return to menu")
    print("2 - Exit")

    logoutSelection = input()

    while logoutLoop:  # Logout loop is used to ensure user is kept in logout menu until they select 1 or 2

        if logoutSelection == '1':
            main()  # Returns user to main function

        if logoutSelection == '2':
            print("Goodbye!")
            sys.exit()  # Exits / terminates the program
        else:
            print("Error, please type 1 or 2\n")
            continue


# Main function; contains most the primary menu login system and asks for user password and username

def main():
    menu = True
    attempts = 3

    while menu:  # Menu loop for login attempts

        print("Welcome to the authentication system.")
        print("Please enter a number to continue: \n1-Login \n2-Exit")
        menuSelection = input()

        if menuSelection == '1':  # Menu selection 1
            while attempts != 0:  # Attempts counter; user only has 3 attempts
                print("Enter Username: ")
                userName = input()  # Collect username

                print("Enter Password: ")
                userPassword = input()  # Collect user password

                if userName in ["griffin.keys", "donald.monkey"]:
                    userType = "zookeeper"  # Assigns user type zookeeper
                    MD5ConversionFunc(userPassword, userType)  # Calls md5 password conversion
                    attempts -= 1  # Subtracts 1 attempt from counter

                elif userName in ["rosario.dawson", "bruce.grizzlybear"]:
                    userType = "admin"
                    MD5ConversionFunc(userPassword, userType)
                    attempts -= 1

                elif userName in ["bernie.gorilla", "jerome.grizzlybear"]:
                    userType = "veterinarian"
                    MD5ConversionFunc(userPassword, userType)
                    attempts -= 1

                else:
                    print("Invalid user name!\n")
                    attempts -= 1  # Subtracts 1 attempt from counter

                    if attempts == 0:
                        print("\nOut of login attempts. Goodbye!")
                        sys.exit()  # Exits if logout attempts are reached

                    continue  # Loop

            break  # Loop

        if menuSelection == '2':  # Menu selection 2

            yesNoLoop = True  # Variable for loop
            while yesNoLoop:  # Loop for yes or no choice

                print("Are you sure you want to exit? (y/n)")
                yesNo = input()

                if yesNo in ['y', 'Y']:
                    print("Goodbye!")
                    sys.exit()  # Exits if user input is Y or y
                    break
                elif yesNo in ['n', 'N']:
                    yesNoLoop = False  # Ends loop and returns to main if user input is n or N
                    main()
                else:
                    print("Error, please type y or n!")  # Error message ( not y/Y or n/N)
                    continue # Loop
        else:
            print("\nError, please enter 1 or 2\n\n")  # Menu options, if user does not input 1 or  2
            continue # Loop


if __name__ == "__main__":
    main()

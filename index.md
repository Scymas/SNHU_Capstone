# Schuyler Enneman - SNHU Capstone ePortfolio
## CS-499

## Milestone 2 - Software Design and Engineering
### Transfer a project into a different language 

For this project I took a Java project from my IT-145 class and converted it into Python. 
Below I will show both my original Java source code along with the updated and new Python code. 

### Java Code: 

```java

import java.util.Scanner;
import java.io.*;
import java.security.MessageDigest;

/*
Schuyler Enneman
Final Project
IT-145-T1462 Found in App Development
*/


class MD5Conversion { // MD5 conversion class
    public static String MD(String newPass)throws Exception{ // MD5 Conversion
            
        String original = newPass; 
        MessageDigest md = MessageDigest.getInstance("MD5");
        md.update(original.getBytes());
        byte[] digest = md.digest();
        StringBuffer sb = new StringBuffer();
        for (byte b : digest) {
                    sb.append(String.format("%02x", b & 0xff));
        }
        String hashedPass = sb.toString(); // hashedPass stores MD5
                
        return hashedPass;
    }
}

class FileOpen { // file read class
    public static void ZooFile (String userFileSelect) throws IOException {
        
        if (userFileSelect.equals("zookeeper")){ // zookeeper file
            File zooKeeperFile = new File("zookeeper.txt"); 
            Scanner file1 = new Scanner (zooKeeperFile);
            
            // prints content from zookeeper.txt
            System.out.println();
            System.out.println(file1.nextLine());
            System.out.println(file1.nextLine());
            System.out.println(file1.nextLine());
            System.out.println();
        }
        
        if (userFileSelect.equals("admin")){ // admin file
            File adminFile = new File("admin.txt"); 
            Scanner file2 = new Scanner (adminFile);
            
            // prints content from admin.txt
            System.out.println();
            System.out.println(file2.nextLine());
            System.out.println(file2.nextLine());
            System.out.println(file2.nextLine());
            System.out.println();
        }
        
        if (userFileSelect.equals("veterinarian")){ // vetrinarian file
            File veterinarianFile = new File("veterinarian.txt");
            Scanner file3 = new Scanner (veterinarianFile);
            
            // prints content from veterinarian.txt
            System.out.println();
            System.out.println(file3.nextLine());
            System.out.println(file3.nextLine());
            System.out.println(file3.nextLine());
            System.out.println();
            
        } 
    } 
}

class LogOut { // logout class
    public static void Log() throws Exception {
        Scanner scnrLog = new Scanner(System.in);
        char logoutSelection;
        boolean logoutLoop = true;
         
        while (logoutLoop) {
        
        System.out.println("Logout/return to menu or exit?");
        System.out.println("1 - Logout and return to menu");
        System.out.println("2 - Exit");
        logoutSelection = scnrLog.next().charAt(0);
     
            if (logoutSelection == '1') {
                
                System.out.println();
                AuthenticationSystem.main(new String[0]); // returns to main
            }
        
            if (logoutSelection == '2') {
                System.out.println();
                System.out.println("Goodbye!");
                System.exit(0); // terminates program
            }
        
            else {
                System.out.println();
                System.out.println("Error");
                System.out.println();
                continue;
            }
           
        }
    }
}

public class AuthenticationSystem { 
    public static void main(String[] args) throws Exception {
        Scanner scnr = new Scanner(System.in);
        
        // variables
        String userName;
        String userPassword;
        String userType = ""; // initialized 
        boolean menu = true; // used to loop menu
        char menuSelection;
        String yesNo;
        int attempts = 3; // number of login attempts allowed
        String hashedPass = ""; // initialized 
        
        while (menu) { // menu loop
            
            // menu system
            
            System.out.println("Welcome to the authentication system.");
            System.out.println("Please enter a number to contunue: ");
            System.out.println("1 - Login");
            System.out.println("2 - Exit");
            menuSelection = scnr.next().charAt(0); // char for selection
            scnr.nextLine(); // blank to fix nextLine for userName
            
            
            if (menuSelection == '1') { // if user opts to login: 
                
                while (attempts != 0){ // login attempt loop
                
                    System.out.println();
                    System.out.println("Enter username: ");
                    userName = scnr.nextLine(); // collect username
                
                    System.out.println("Enter password: ");
                    userPassword = scnr.nextLine(); // collect user password
                
                    MD5Conversion.MD(userPassword); // call to convert

                
                    if (userName.equals("griffin.keyes") || 
                        userName.equals("donald.monkey")){
                        userType = "zookeeper"; // assign zookeper to user
                    
                    }
                    else if (userName.equals("rosario.dawson")|| 
                        userName.equals("bruce.grizzlybear")){
                        userType = "admin"; // assign admin to user
                    
                    }
                    else if (userName.equals("bernie.gorilla") ||
                        userName.equals("jerome.grizzlybear")){
                        userType = "veterinarian"; /// assign veterinarian user
                    
                    }
                    else {
                        
                        System.out.println("Invalid username! ");
                        System.out.println();
                        attempts--; // -1 from attempt limit
                        continue;
                    }
                    
                    /*
                    The following if / else if statements check the userType
                    and compare it to the appropriate 'hashed' password. If the 
                    user has entered the correct username and correct password 
                    their file will be opened. If the username is correct but
                    the password is not, the program informs the user their 
                    password is invalid. 
                    */
                    
                    if ((userType.equals("zookeeper")) && (MD5Conversion.MD
                    (userPassword).equals("108de81c31bf9c622f76876b74e9285f"))
                    || (MD5Conversion.MD(userPassword).equals("17b1b7d8a70669"
                    + "6ed220bc414f729ad3"))){
                        
                        FileOpen.ZooFile(userType); // file open class
                        LogOut.Log(); // logout 
                    }
                    
                    // if usertype is admin and userpass matches hashed pass
                    else if ((userType.equals("admin")) && (MD5Conversion.MD
                    (userPassword).equals("3e34baa4ee2ff767af8c120a496742b5"))
                    || (MD5Conversion.MD(userPassword).equals("0d107d09f5bbe40"
                    + "cade3de5c71e9e9b7"))){
                        
                        FileOpen.ZooFile(userType);
                        LogOut.Log();
                    }
                    
                    // if usertype is "vet" and userpass matches hashed pass
                    else if ((userType.equals("veterinarian")) && (MD5Conversion
                    .MD(userPassword).equals("a584efafa8f9ea7fe5cf18442f32b07b")
                    )|| (MD5Conversion.MD(userPassword).equals("3adea92111e6307"
                    + "f8f2aae4721e77900"))){
                        
                        FileOpen.ZooFile(userType);
                        LogOut.Log();
                    }
                    
                    else {
                        
                        System.out.println("Invalid Password!");
                        System.out.println();
                        attempts--; // -1 from attempt limit
                        continue;
                    }
                }
                
                if (attempts == 0) {
                    System.out.println();
                    System.out.println("Too many failed login attempts!");
                    System.out.println("Goodbye!");
                }
            break;
            }
            
             if (menuSelection == '2') { // if user wishes to exit
                 boolean yesNoLoop = true; // loop for y/n
                 while (yesNoLoop){ // while loop is true
                
                System.out.println("Are you sure you want to exit? (y/n)");
                yesNo = scnr.nextLine();
                
                switch(yesNo) { // switch case for exit (y/n)(just for variance)
                    case "y": 
                        System.out.println("Goodbye!");
                        System.exit(0);
                    case "Y":
                        System.exit(0);
                    case "n":
                        System.out.println();
                        yesNoLoop = false; // yes no loop ends -> user goes to-
                                           // menu
                    case "N":
                        yesNoLoop = false;
                    default:
                        System.out.println("Error, please type y or n");
                        System.out.println();
                        continue;
                }
                    
             }
        }
              
            else { // if input is not 1 or 2 -> asks for user input again
                System.out.println("Error, please enter 1 or 2.");
                System.out.println();
                continue;
            }
        }
    }
}

```

### Python Code : 

```python

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

    if userFileSelect == "veterinarian":  # Reads the veterinarian file and prints
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

    while logoutLoop:  # Logout loop is used to ensure user is kept in logout menu until they select 1 or 2

        logoutSelection = input()

        if logoutSelection == '1':
            logoutLoop = False
            main()  # Returns user to main function

        elif logoutSelection == '2':
            print("Goodbye!")
            sys.exit()  # Exits / terminates the program

        else:
            print("Error, please type 1 or 2\n")
            continue


# Main function; contains most the primary menu login system and asks for user password and username

def main():
    menu = True
    attempts = 3

    print("Welcome to the authentication system.")

    while menu:  # Menu loop for login attempts

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
                    print(attempts, "Attempt(s) left\n")

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

                elif yesNo in ['n', 'N']:
                    yesNoLoop = False  # Ends loop and returns to main if user input is n or N
                    main()

                else:
                    print("Error, please type y or n!")  # Error message ( not y/Y or n/N)
                    continue # Loop
        else:
            print("\nError, please enter 1 or 2\n\n")  # Menu options, if user does not input 1 or  2
            continue  # Loop


if __name__ == "__main__":
    main()
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/Scymas/SNHU_Capstone/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://help.github.com/categories/github-pages-basics/) or [contact support](https://github.com/contact) and we’ll help you sort it out.

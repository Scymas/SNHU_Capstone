# Schuyler Enneman
# CS-499-T6571
# Data Structures and Algorithms
# Milestone 3

# Note: Requires openpyxl, xlsxwriter, and xlrd packages
# This code is based off of my CS-260 C++ code; using two data structures
# The data structures shown here are a singly linked list and a binary tree

# References --
# Data Structures found from: https://www.tutorialspoint.com/python_data_structure/index.htm
# Pandas read found from: https://medium.com/better-programming/using-python-pandas-with-excel-d5082102ca27
# Pandas write and other from: https://xlsxwriter.readthedocs.io/working_with_pandas.html

import sys
import pandas as pd
from openpyxl import load_workbook
from pip._vendor.distlib.compat import raw_input


# Class for linked list - Creates node containing head and next pointer

class node:
    def __init__(self, data=None):  # 'Constructor'
        self.data = data
        self.next = None


# Linked list class - Contains linked list print and add node
# Nodes are added to the front of the list vs the back
# There is only one traversal method for this data structure

class linkedList:
    def __init__(self):  # 'Constructor'
        self.head = node()  # head node
        self.tail = None  # Tail set to none
        self.length = 0  # Length 0

    # Add node to the front of the linked list

    def addNodeF(self, newData):
        newNode = node(newData)

        # New node is added to the head of the list

        newNode.next = self.head
        self.head = newNode

    # For printing linked lit

    def printList(self):
        pn = self.head  # set head
        while pn:
            print(pn.data)  # print data
            pn = pn.next  # set to next


# Class for binary tree and search - Binary tree search based on code

class treeNode:
    def __init__(self, data=None):  # data set to none initial* -- 'Constructor'
        self.data = data
        self.left = None  # left branch
        self.right = None  # right branch

    # Add the tree - creates tree based on nodes left / right

    def addTree(self, data=None):
        if data == self.data:
            return

        # go left branches (child)

        if data < self.data:
            if self.left is None:
                self.left = treeNode(data)
            else:
                self.left.addTree(data)

        # go right branches (child)

        else:
            if self.right is None:
                self.right = treeNode(data)
            else:
                self.right.addTree(data)

    # Tree traversal from - https://www.tutorialspoint.com/python_data_structure/python_tree_traversal_algorithms.htm
    # The main difference between traversals is how order branches are executed

    # Pre order traversal

    def traversal(self, root=None):
        elements = []  # list object for elements
        if root:
            elements.append(root.data)  # current node value
            elements += self.traversal(root.left)  # traverse left branch from root
            elements += self.traversal(root.right)  # traverse right branch from root

        return elements  # Returns elements[]

    # Post (reverse) order traversal

    def postTraversal(self, root=None):
        elements = []
        if root:
            elements = self.postTraversal(root.left)  # ""
            elements += self.postTraversal(root.right)  # ""
            elements.append(root.data)

        return elements

    # In order traversal - for

    def inTraversal(self, root=None):
        elements = []
        if root:
            elements = self.inTraversal(root.left)  # ""
            elements.append(root.data)
            elements += self.inTraversal(root.right)  # ""

        return elements


# Tree function for user data
# Accepts user input and inserts into tree nodes

def userTreeSearchPost():
    menuLoop = True
    root = treeNode("Root")  # Assign root node to s, "Root"

    while menuLoop is True:  # loop for menu

        print("Tree root is word 'Root'")
        print("Would you like to add a new leaf? (y/n)")
        yesNo = input()

        if yesNo in ["y", "Y"]:

            # Loop for user to enter 10 'objects' which will be put into the binary tree
            print("Enter data (10 objects): ")
            for i in range(10):
                tree = raw_input()
                root.addTree(tree)

            print("\n")
            print(root.postTraversal(root), "\n")  # Traversal for printing tree
            menuLoop = False  # Ends menu loop

        elif yesNo in ["n", "N"]:
            menuLoop = False  # Ends menu loop

        else:
            print("Error, please enter y or n\n")
            continue  # loop


# Inverse traversal tree function

def userTreeSearchIn():
    menuLoop = True
    root = treeNode("Root")  # Assign root node to s, "Root"

    while menuLoop is True:  # loop for menu

        print("Tree root is word 'Root' - Branches are created alphabetically")
        print("Would you like to add a new leaf? (y/n)")
        yesNo = input()

        if yesNo in ["y", "Y"]:

            # Loop for user to enter 10 'objects' which will be put into the binary tree

            print("Enter data (10 objects): ")
            for i in range(10):
                tree = raw_input()
                root.addTree(tree)

            print("\n")
            print(root.inTraversal(root), "\n")  # Traversal for printing tree
            menuLoop = False  # Ends menu loop

        elif yesNo in ["n", "N"]:
            menuLoop = False  # Ends menu loop

        else:
            print("Error, please enter y or n\n")
            continue  # loop


# This function is for the binary tree but uses the Fruits and Amounts data from the excel spreadsheet
# The information is limited as there are only a few nodes
# This is primarily to show that the data from within the excel sheet can be placed in -
# a data structure.

def treeSearchFruits(fruitData, amountData):
    fruits = fruitData
    amounts = amountData

    fruitString = " ".join(map(str, fruits))  # Use map to convert to string
    amountString = " ".join(map(str, amounts))

    #     root
    #    /    \
    #  fruits  amounts

    root = treeNode("Root")  # Root node set to root
    root.addTree(fruitString)  # Use fruit data for node
    root.addTree(amountString)  # Use fruit data for node

    print("\n")
    print(root.traversal(root), "\n")  # Traversal for printing tree


# Function for traversing the linked list --
# This function allows the user to add data to the linked list
# This data is lost after the function is exited though and does -
# not save the data to the spreadsheet. This is primarily for -
# showing the linked list can use a combination of user input -
# and spreadsheet data.

def listSearch(fruitData, amountData):
    menuLoop = True
    fruits = fruitData
    amounts = amountData
    lst1 = []  # List for fruit / amount

    list1 = linkedList()
    list1.head = node(fruits)  # head node is set to fruits (spreadsheet)
    n2 = node(" ")  # space
    n3 = node(amounts)  # node 3 is set to amounts

    # Set node / list order

    list1.head.next = n2
    n2.next = n3

    while menuLoop is True:  # loop

        print("Would you like to add a new node? (y/n)")
        yesNo = input()

        if yesNo in ["y", "Y"]:

            # Iterates ten times for user objects
            # These objects are saved to a list

            print("Enter new node: ")
            print("Enter 10 objects: ")
            for i in range(10):
                n4 = raw_input()  # Raw input in list
                lst1.append(n4)  # Appends list

            list1.addNodeF(lst1)  # Puts list into front node
            list1.printList()  # Displays linked list
            print("\n")
            menuLoop = False  # Ends loop

        elif yesNo in ["n", "N"]:
            list1.printList()  # Displays linked list w/o user data
            print("\n")
            menuLoop = False  # Ends loop

        else:
            print("Error, please enter y or n\n")
            continue  # loop


# This function is used to append data to the excel spreadsheet
# I found this append information from -
# https://medium.com/better-programming/using-python-pandas-with-excel-d5082102ca27
# In this function the user's data is added to the spreadsheet

def addData():
    addLoop = True

    while addLoop:  # Loop for y/n selection

        print("Please type the name of a fruit: ")
        userFruit = input()  # Input for fruit

        print("Please type the amount of fruit: ")
        userAmount = input()  # Input for amount of fruit

        # Data frame for adding data to the excel spreadsheet
        df2 = pd.DataFrame({"Fruits": [userFruit], "Amounts": [userAmount]})

        # Setup writer using openpyxl
        writer = pd.ExcelWriter("FruitList.xlsx", engine="openpyxl")

        # Load spreadsheet as workbook
        writer.book = load_workbook("FruitList.xlsx")

        # Copies current loaded spreadsheet
        writer.sheets = dict((ws.title, ws) for ws in writer.book.worksheets)

        # Reads excel file
        reader = pd.read_excel(r'FruitList.xlsx')

        # Writes to the sheet; no index or header setting
        df2.to_excel(writer, index=False, header=False, startrow=len(reader) + 1)

        # Closes writer for other inputs
        writer.close()

        print("Data added\nAdd more data? (Y/N)")

        # Choice to add more data or return to menu
        yesNo = input()

        if yesNo in ['y', 'Y']:
            continue  # loop

        elif yesNo in ['n', 'N']:
            addLoop = False  # Ends loop
            main()  # main call
        else:
            print("Error, Returning to menu\n")
            break  # break loop


# Main function - Contains primary menu loop
# Also contains Pandas module to read excel spreadsheet
# The excel sheet data is also converted to a list

def main():
    # Import the data sheet from Excel (simple)

    # Pandas reads excel spreadsheet and assigns it to a variable

    df2 = pd.read_excel("FruitList.xlsx", header=None, names=["Fruits", "Amounts"])

    # The two main categories are converted to lists (Fruit and Amounts)
    # The variables are declared here to be passed to other functions

    fruits = df2["Fruits"].values.tolist()
    amounts = df2["Amounts"].values.tolist()
    print("Data Loaded!\n")

    menuLoop = True
    yesNoLoop = True

    while menuLoop is True:  # Loop for Menu
        print("---Menu---")
        print("Please Make a Selection")
        print("1: Display Spreadsheet Data")
        print("2: Linked List Data - Add Node")
        print("3: Add Data to Spreadsheet")
        print("4: Binary Tree - Pre Order Traversal with Spreadsheet Data")
        print("5: Binary Tree - Inverse Traversal with User Data")
        print("6: Binary Tree - In order Traversal with User Data")
        print("9: Exit")

        menuChoice = input()

        # Menu choices - calls functions

        if menuChoice == "1":

            # uses zip to pair tuples
            # This is how to get fruits and amounts lined up together
            for a, b in zip(fruits, amounts):
                print(a, b, )
            print("\n")

        elif menuChoice == "2":
            listSearch(fruits, amounts)

        elif menuChoice == "3":
            addData()

        elif menuChoice == "4":
            treeSearchFruits(fruits, amounts)

        elif menuChoice == "5":
            userTreeSearchPost()

        elif menuChoice == "6":
            userTreeSearchIn()

        elif menuChoice == "9":

            while yesNoLoop is True:

                exitChoice = input("Exit? (y/n): ")

                if exitChoice in ["y", "Y"]:
                    print("Goodbye!")
                    sys.exit()

                elif exitChoice in ["n", "N"]:
                    yesNoLoop = False
                    main()

                else:
                    print("Error, please type y or n!")
                    continue

        else:
            print("Error")
            continue


if __name__ == '__main__':
    main()

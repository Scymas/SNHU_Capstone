// Schuyler Enneman
// CS-260-J1540
// 3-2 Programming Activity: Lists and Searching

/* This file is the basis for the Milestone 3 project
   This file uses seperate csv data and uses it within the data structures; this particular - 
   data structure uses a linked list with a sort algorithm. This involves setting pointers - 
   along with having the correct csv data availbile. A seperate parser is also needed for -
   the data reading. The new code (Python) is inspired by this project but with a combination - 
   of binary trees using multiple traversal methods. 
*/


#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    // FIXME (1): Internal structure for list entries, housekeeping variables


	// Structure called node
	struct node {
		Bid bid;
		node *next;
		node() { // constructor
			next = nullptr; // next is always set to null
		}
	};

	node *head; // head pointer
	node *tail; // tail pointer
	int size; // int for counter




public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    // FIXME (2): Initialize housekeeping variables

	// initialize head, tail, and size
	head = nullptr;
	tail = nullptr;
	size = 0;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    // FIXME (3): Implement append logic

	// new pointer
	node *newnode = new node;

	newnode -> bid = bid; // pointer access bid and assign to bid

	// append from ZyBooks - 3.2 (also prepend)

	if (head == nullptr) {
		head = newnode;
		tail = newnode;
	}

	else {
		tail -> next = newnode; // access next pointer
		tail = newnode; // set tail to the new node (last entry)
	}

	size++; // increment +1
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // FIXME (4): Implement prepend logic

	// new pointer
	node *newnode = new node;

	newnode -> bid = bid; // pointer access bid and assign to bid

	if (head == nullptr) {
		head -> next = newnode; // next pointer will be head
		head = newnode;
	}

	else {
		head = newnode; // head is always new node (1st entry)
	}

	size++; // increment +1
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // FIXME (5): Implement print logic

	// new pointer (head)
	node *printnode = head;

	// using for loop, as long as i < size (elements)
	for (int i = 0; i < Size(); i++){

		// access for printnode to bid , output csv data
		cout << printnode -> bid.bidId << ":"  << printnode -> bid.title << "|"
		<< printnode -> bid.amount << "|" << printnode -> bid.fund << "." << endl;

		printnode = printnode -> next; // printnode -> next node
	}
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // FIXME (6): Implement remove logic

	//Note: I cannot figure out this part -- This section of code is not completed for that reason

	// new pointer (head)
	node *removenode = head;
	node *newnode = new node;


	// using for loop, as long as i < size (elements)
	for (int i = 0; i < Size(); i++){
		if (head -> bid.bidId == bidId) { // bid id == bid id
			head = nullptr; // head null pointer
			delete head; // delete head pointer from struct
		}

		else {
			newnode = newnode -> next;
			removenode = removenode -> next;
		}

		size --; // decrease size -1
	}

}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // FIXME (7): Implement search logic

	// new pointer (head)
	node *searchnode = head;

	// using for loop, as long as i < size (elements)
	for (int i = 0; i < Size(); i++){

		// if bidId == bidId , return the searchnode bid
		if (searchnode -> bid.bidId == bidId) {

			return searchnode -> bid; // return bid

		}

		searchnode = searchnode -> next; // searchnode -> next node
	}

}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bidList.Remove(bidKey);

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}

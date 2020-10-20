// Schuyler Enneman
// October 12 2019
// CS 260
// 6-2 Trees

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

// FIXME (1): Internal structure for tree node
struct Node {

	Bid bid; // bid bid
	Node *left; // left
	Node *right; // right

	Node() { // constructor for left and right set to null
		left = nullptr;
		right = nullptr;
	}

};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
	root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (2a) Implement inserting a bid into the tree

	// check for root
	if (root == nullptr) {
		root = new Node; // create root (new Node)
		root -> bid = bid;
		root -> left = nullptr; // set root left and right to nullptr
		root -> right = nullptr;
	}

	else {
		addNode(root, bid); // add node ; root and bid
	}

}


/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (4a) Implement removing a bid from the tree

	// This remove algorithm is taken from ZyBooks : Figure 6.5.1

	Node *par = 0;
	Node *cur = root;

	while (cur != nullptr) {

		if (cur -> bid.bidId == bidId) { // remove leaf
			if (!cur -> left && !cur -> right) {
				if (par == nullptr) {
					root = nullptr;
				}

				else if (par -> left == cur) {
					par -> left == nullptr;
				}

				else {
					par -> right = nullptr;
				}
			}

			else if (cur -> left && !cur -> right) { // remove node that only has left child
				if (par == nullptr) {
					root = cur -> left;
				}

				else if (par -> left == cur) {
					par -> left = cur -> left;
				}

				else {
					par -> right = cur -> left;
				}

			}

			else if (!cur -> left && cur -> right) { // remove node that only has right child

				if (!par) {
					root = cur -> right;
				}

				else if (par -> left == cur) {
					par -> left = cur -> right;
				}

				else {
					par -> right = cur -> right;
				}


			}

			else { // remove node that has two children
				Node* suc = cur -> right;
				while(suc -> left != nullptr) {
					suc = suc -> left;
				}

				// Remove successor from bidId
				cur -> bid = suc -> bid; // set current bid, left, right
				cur -> left = suc -> left;
				cur -> right = suc -> right;
			}


		}

		else if (cur -> bid.bidId < bidId) { // search right (bidId)
			par = cur;
			cur = cur -> right;
		}

		else { // search left
			par = cur;
			cur = cur -> left;
		}


	}

	return; // node not found

}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (3) Implement searching the tree for a bid

	Node *search = root;

	while (search != nullptr) { // search while search is not null / look for match
		if (bidId == search -> bid.bidId) {
			return search -> bid;
		}

		if (bidId < search -> bid.bidId) {
			search = search -> left;
		}
		else {
			search = search -> right;
		}
	}

	// Return bid
	Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (2b) Implement inserting a bid into the tree

	if (node -> bid.bidId.compare(bid.bidId) > 0) { // if bid > add node to left tree
		if (node -> left == nullptr) {
			node -> left = new Node(bid);
		}

		else {
			addNode =  new Node(bid); // Struct node (bid) (error)
		}

	}

	// add the node to right tree if bid is not greater
	else {
		if (node -> right == nullptr) {
			node -> right = new Node(bid);
		}

		else {
			 addNode(node -> right, bid); // addNode (right)
		}

	}



}
void BinarySearchTree::inOrder(Node* node) {
}
//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
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
    str.erase(remove(str.begin(), str.end(), ch), str.end()); // this line is sending me errors, not sure how to fix it.
    return atof(str.c_str());
}

/**
 * The one and only main() method
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

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}

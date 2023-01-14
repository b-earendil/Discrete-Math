/** 
	Description : 
	Templated Binary Search Tree Used to Benchmark Insertion
	Under Best-Case (Random) Insertion and Worst-Case
	(Sequential) Insertion... Airline No-Fly List Demo to 
	Demonstrate Searching with BST

	Demos : 
	1. Benchmark Insertion
	2. Airline No-Fly List 

	Note: Hashing would be a better match than BST for this 
	particular application
**/

#include "BST.hpp" 

#include <iostream> // std::cout
#include <fstream> // file I/O
#include<iomanip> // std::setw
#include<vector> // std::vector
#include <utility> // std::pair
#include <tuple> // std::tuple
#include <ctime> // std::time
#include <random> // srand() , rand()
#include <chrono> // high_resolution_clock

void calculateBSTInsertionTime(std::vector<std::tuple<int, double, double>> &trials, int n);
void printBSTInsertionTrialTimes(const std::vector<std::tuple<int, double, double>>& trials);

void populateBSTWithNoFlyData(BinarySearchTree<int, std::string>& noFlyList);
void populateVectorWithPassengerManifest(std::vector<std::pair<int, std::string>>& passengerList);
void verifyPassengers(BinarySearchTree<int, std::string>& noFlyList, std::vector<std::pair<int, std::string>> passengerList);



int main() {
	/*
			  ---Testing BST Methods--- 
		+  insert(), height(), search(), remove()
		+  print_inorder(), print_preorder(), print_postorder
		+  min_key(), max_key(), return_count()
	*/
	BinarySearchTree<int, std::string> bst;
	bst.insert(10, "a");
	bst.insert(5, "a");
	bst.insert(20, "a");
	bst.insert(8, "a");
	bst.insert(30, "a");
	bst.insert(25, "a");
	bst.insert(40, "a");

	std::cout << "\n--------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Testing BST : insert(), returnCount(), height(), search(), max(), min(), traversals" << std::endl;
	std::cout << "--------------------------------------------------------------------------------------\n" << std::endl;

	std::cout << "Insert: 10, 5, 20, 8, 30, 25, 40";

	/*
						 [10]
					   /      \
					[5]	      [20]
					   \		 \
					   [8]		  [30]
							      /   \
								[25]  [40]
	*/		
	std::cout << "\nNumber of Nodes : " << bst.returnCount();
	std::cout << "\nHeight : " << bst.height();
	std::cout << "\nValue 25 Found? : " << std::boolalpha << bst.search(25);
	std::cout << "\nValue 205 Found? : " << std::boolalpha << bst.search(205);

	std::cout << "\n\n--Inorder Traversal--\n";
	bst.printInorder();
	std::cout << "\n--Preorder Traversal--\n";
	bst.printPreorder();
	std::cout << "\n--Postorder Traversal--\n";
	bst.printPostorder();

	std::cout << "\nMax Key: " << bst.maxKey() << std::endl;
	std::cout << "Min Key: " << bst.minKey() << std::endl;

	/*
	Upon removal of node, choose inorder predecessor or inorder successor
	to take it's place... based on the height of the left and right subtree
	of the node to be removed. Small optimization to mantain optimal height
	of BST. 

	Note: AVL tree needed if we want self-balancing behavior

	Before				  [10]
					  InorderPred
				     /			\
				  [5]			 [20] // <- remove
				    \				\
				    [8]				 [30]
									 /   \
								   [25]  [40]
							  InorderSucc

	After
						 [10]
					   /      \
					[5]	      [25]
					   \		 \
					   [8]		  [30]
								     \
								     [40]

	
	*/	

	std::cout << "\nRemove: remove(20)" << std::endl;
	bst.remove(20, "a");
	std::cout << "Number of Nodes: " << bst.returnCount() << std::endl;
	std::cout << "Height : " << bst.height() << std::endl;


	std::cout << "\n--Inorder Traversal--\n";
	bst.printInorder();
	std::cout << "\n--Preorder Traversal--\n";
	bst.printPreorder();
	std::cout << "\n--Postorder Traversal--\n";
	bst.printPostorder();

	std::cout << "\n\n--------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Testing BST Insertion Times : Best Case (Random), Worst Case (Sequential)" << std::endl;
	std::cout << "--------------------------------------------------------------------------------------" << std::endl;


	std::cout << "\n\t\t\t---BST Insertion Times--- " << std::endl;

	// a vector of times can be used to store many trials
	std::vector<std::tuple<int, double, double>> trials; 	
	/*
		 Helper function to test best/worst case BST insertion time

		 Note:  Due to limited stack space we chose to use 
			    iterative_insert_helper(). However, recursive_insert_helper() 
			    is also implemented in BinarySearchTree.hpp
	*/
	int n = 100;
	for (int i = 0, j = 1; i < 10; i++, j++) {
		calculateBSTInsertionTime(trials, n * j * 10);
	}
	printBSTInsertionTrialTimes(trials);

	std::cout << "\n--------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Testing BST Search : No-Fly List" << std::endl;
	std::cout << "--------------------------------------------------------------------------------------" << std::endl;

	BinarySearchTree<int, std::string> noFlyList;
	std::vector<std::pair<int, std::string>> passengerManifest;

	// fill BST 
	populateBSTWithNoFlyData(noFlyList);
	// fill vector with passenger list for the departing flight
	populateVectorWithPassengerManifest(passengerManifest);
	// check if any passengers on departing flight are on no fly list
	verifyPassengers(noFlyList, passengerManifest);

	return 0;
}

// better to make this a const BST and define a search() method for
// const qualified types
void verifyPassengers(BinarySearchTree<int, std::string>& noFlyList, std::vector<std::pair<int, std::string>> passengerList) {
	// print header
	std::cout << std::endl;
	std::cout << "---Verify Passengers Before Takeoff---" << std::endl;
	std::cout << "Check Passenger Manifest Against No Fly List\n" << std::endl;

	std::cout << "United Airlines" << "\n" << "UA 1874 | " << "PHX to LA\n" << std::endl;
	
	std::cout << std::setw(30) << std::left << "FULL NAME " << std::setw(20) << "VERIFIED TO FLY?" << std::endl;
	for (auto p : passengerList) {
		std::cout << std::setw(30) << std::left << p.second;
		if (noFlyList.search(p.first)) {
			std::cout << std::setw(20) << "NO FLY LIST" << std::endl;
		}
		else {
			std::cout << std::setw(20) << "yes" << std::endl;
		}
	}
}

void populateVectorWithPassengerManifest(std::vector<std::pair<int, std::string>>& passengerList) {
	// declare ifstream and connect to file
	std::ifstream myFile("fakePassengerList.txt");

	int iD; std::string firstName; std::string lastName; std::string fullName;

	if (myFile.is_open()) {
		while (myFile.good()) {
			myFile >> iD; myFile >> firstName; myFile >> lastName;
			fullName = firstName + " " + lastName;
			if (!myFile.eof()) {
				//std::cout << iD << " " << fullName << std::endl;
				passengerList.push_back(std::make_pair(iD, fullName));
			}
		}
	}
	else {
		std::cerr << "File open error" << std::endl;
	}
	myFile.close();
}

void populateBSTWithNoFlyData(BinarySearchTree<int, std::string>& noFlyList) {
	
	// declare ifstream and connect to file
	std::ifstream myFile("fakeNoFlyList.txt");

	int iD; std::string firstName; std::string lastName; std::string fullName;

	if (myFile.is_open()) {
		while (myFile.good()) {
			myFile >> iD; myFile >> firstName; myFile >> lastName;
			fullName = firstName + " " + lastName;
			if (!myFile.eof()) {
				//std::cout << iD << " " << fullName << std::endl;
				noFlyList.insert(iD, fullName);
			}
		}
	}
	else {
		std::cerr << "File open error" << std::endl;
	}
	myFile.close();
}

void printBSTInsertionTrialTimes(const std::vector<std::tuple<int, double, double>>& trials) {
	// print the results from each trial
	int n = 1;
	//for (auto it = trials.begin(); it != trials.end(); ++it) {
	for (auto& t : trials) {
		{
			std::cout << "Sample Size: " << "\t" << std::get<0>(t) << "\t" <<" Random:"  << "\t" << std::get<1>(t) << "\t"
				<< " Sequential: " << "\t" << std::get<2>(t) << std::endl;
		}
	}
}

void calculateBSTInsertionTime(std::vector<std::tuple<int, double, double>>& trials, int n) {
	/*
			 ---Best Case BST Insertion Time--- 
		+	Inserted Keys Have Random Values
	*/

	// params: sampleSize, worstCaseInsertionTime, bestCaseInsertionTime
	std::tuple<int, double, double> times;

	BinarySearchTree <int, std::string> bstGood;

	// time the insertion
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++)
		bstGood.insert(std::rand() % n + 1, "r");
	auto stop = std::chrono::high_resolution_clock::now();
	// store the sample size
	std::get<0>(times) = n;
	// store the time
	std::get<1>(times) = std::chrono::duration_cast
		<std::chrono::microseconds>(stop - start).count();

	/*
			  ---Worst Case BST Insertion Time--- 
		+	Inserted Keys Have Sequential Values

		Ex:
				[2] 
				   \ 
				   [3] 
					 \ 
					  [5]  
						\ 
						[10] 
							...
	*/
	BinarySearchTree <int, std::string > bstBad;
	// time the insertion
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		bstBad.insert(i, "s");
	}
	stop = std::chrono::high_resolution_clock::now();
	// store the time
	std::get<2>(times) = std::chrono::duration_cast
		<std::chrono::microseconds>(stop - start).count();

	// store this trial
	trials.push_back(times);
}



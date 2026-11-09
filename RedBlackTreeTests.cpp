
#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}

void TestConstructor(){
	cout << "Testing Constructor W/Int Input..." << endl;
	RedBlackTree rbt = RedBlackTree(15);
	assert(rbt.ToPrefixString() == " B15 ");

	// added test
	// the int constructor counts its one node
	assert(rbt.Size() == 1);

	cout << "PASSED!"<< endl << endl;
}

void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Right Left
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	// more tests go here
	// consider some symmetry!
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(60); 
	// right right situation
	// one left rotation at 30
	assert(rbt->ToPrefixString() == " B45  R30  R60 ");
	delete rbt;
 
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(35); 
	// right left (zig-zag) 
	// rotate right at 45 then left at 30
	assert(rbt->ToPrefixString() == " B35  R30  R45 ");
	delete rbt;
 
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(15);
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	// cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;

	// added tests
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	assert(rbt->ToPrefixString() == " B30  B15  R10  B45 ");
	delete rbt;
 
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(50);
	assert(rbt->ToPrefixString() == " B30  B15  B45  R50 ");
	delete rbt;
 
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10);
	rbt->Insert(5);
	assert(rbt->ToPrefixString() == " B15  B10  R5  B30 ");
	delete rbt;
 
	rbt = new RedBlackTree();
	rbt->Insert(62);
	rbt->Insert(60);
	rbt->Insert(58);
	rbt->Insert(55);
	assert(rbt->ToPrefixString() == " B60  B58  R55  B62 ");
	assert(rbt->ToInfixString() == " R55  B58  B60  B62 ");
	delete rbt;

	// cout << "TESTS MISSING" << endl << endl;
	
	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;

	// added tests
	rbt = new RedBlackTree();
	rbt->Insert(20);
	rbt->Insert(10);
	rbt->Insert(6);
	rbt->Insert(15);
	rbt->Insert(30);
	assert(rbt->ToPrefixString() == " B10  B6  B20  R15  R30 ");
	assert(rbt->ToInfixString() == " B6  B10  R15  B20  R30 ");
	delete rbt;
 
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(50);
	rbt->Insert(60);
	assert(rbt->ToPrefixString() == " B30  B15  B50  R45  R60 ");
	delete rbt;
	
	// cout << "TESTS MISSING" << endl << endl;
	
	cout << "PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	// added tests
	RedBlackTree empty = RedBlackTree();
	assert(empty.ToPrefixString() == "");
	assert(empty.ToPostfixString() == "");
	RedBlackTree one = RedBlackTree(8);
	assert(one.ToInfixString() == " B8 ");
	assert(one.ToPostfixString() == " B8 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	//cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	// probably should have a delete or something here
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

// added test
void TestDuplicateInsert(){
	cout << "Testing Duplicate Insert..." << endl;
 
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(10);
	rbt.Insert(5);
	rbt.Insert(20);
	bool threw = false;
	try
	{
		rbt.Insert(5);
	} 
	catch(invalid_argument &e)
	{
		threw = true;
	}
	assert(threw);
	assert(rbt.Size() == 3);
	assert(rbt.ToPrefixString() == " B10  R5  R20 ");
 
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);

	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	// added tests
	assert(rbt2.Size() == 6);
	assert(rbt1.Size() == 7);
	assert(!rbt2.Contains(200));
	rbt2.Insert(1);
	assert(!rbt1.Contains(1));
 
	RedBlackTree empty = RedBlackTree();
	RedBlackTree emptyCopy = RedBlackTree(empty);
	assert(emptyCopy.ToInfixString() == "");
	assert(emptyCopy.Size() == 0);

	// assignment operator tests
	RedBlackTree b = RedBlackTree(5);
	b = rbt1;
	assert(b.ToPrefixString() == rbt1.ToPrefixString());
	rbt1.Insert(300);
	assert(!b.Contains(300));
	RedBlackTree &sameTree = b; // done through a reference so the compiler doesn't warn about b = b
	b = sameTree;
	assert(b.Size() == 7);

	cout << "PASSED!" << endl << endl;
}


void TestContains(){
	cout << "Testing Contains..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	assert(rbt->Contains(6) == false);
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(rbt->Contains(34));

	// added tests
	assert(rbt->Contains(40));
	assert(rbt->Contains(22));
	assert(rbt->Contains(12));
	assert(rbt->Contains(55));

	assert(!rbt->Contains(0));
	assert(!rbt->Contains(30));
	assert(!rbt->Contains(100));
	assert(!rbt->Contains(-5));

	delete rbt;

	// cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}


void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	// added tests
	RedBlackTree rbt = RedBlackTree(20);
	assert(rbt.GetMin() == 20);
	assert(rbt.GetMax() == 20);
 
	rbt.Insert(10);
	rbt.Insert(6);
	rbt.Insert(15);
	rbt.Insert(30);
	rbt.Insert(-4);
	rbt.Insert(100);
	assert(rbt.GetMin() == -4);
	assert(rbt.GetMax() == 100);
 
	RedBlackTree empty = RedBlackTree();
	bool threwMin = false;
	try
	{
		empty.GetMin();
	} 
	catch(invalid_argument &e)
	{
		threwMin = true;
	}
	assert(threwMin);
	bool threwMax = false;
	try
	{
		empty.GetMax();
	} 
	catch(invalid_argument &e)
	{
		threwMax = true;
	}
	assert(threwMax);

	// cout << "TESTS MISSING" << endl << endl;

	cout << "PASSED!" << endl << endl;
}

// added test
void TestSize(){
	cout << "Testing Size..." << endl;
 
	RedBlackTree rbt = RedBlackTree();
	assert(rbt.Size() == 0);
	for(int i = 1; i <= 50; i++)
	{
		rbt.Insert(i);
		assert(rbt.Size() == (unsigned long long int)i);
	}
 
	cout << "PASSED!" << endl << endl;
}

// added test
void TestPrivate(){
	RedBlackTree rbt = RedBlackTree();
	rbt.PrivateTests();
}


int main(){

	
	TestSimpleConstructor();
	TestConstructor();
	
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();

	TestDuplicateInsert();

	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();
	TestSize();

	TestPrivate();
	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}

// Sources:
// ChatGPT was used generating test cases.
// https://www.cs.usfca.edu/~galles/visualization/RedBlack.html visualizer was used to check the test cases
// Video lecture and worksheet
// ran "leaks --atExit -- ./rbt-tests" to check for memory leaks while writing the code


// To earn the 0.0001 extra credit points, I thought about this comment for a very long time.
// I took a walk. I drew pictures of obviously trees on a piece of paper. And I did my laundry which is pretty mundane and physical for me.
// Then I remembered that cool people know "having a life outside of CS" is not really real.
// So I came back and rotated some more nodes instead of doing other things and trying to be funny.
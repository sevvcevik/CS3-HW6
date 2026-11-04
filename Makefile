all: rbt-tests-first rbt-tests

rbt-tests-first: RedBlackTreeTestsFirstStep.cpp RedBlackTree.cpp RedBlackTree.h
	g++ -Wall -g RedBlackTreeTestsFirstStep.cpp RedBlackTree.cpp -o rbt-tests-first

rbt-tests: RedBlackTreeTests.cpp RedBlackTree.cpp RedBlackTree.h
	g++ -Wall -g RedBlackTreeTests.cpp RedBlackTree.cpp -o rbt-tests

clean:
	rm -f rbt-tests-first rbt-tests
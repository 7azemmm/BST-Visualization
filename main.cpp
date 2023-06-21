#include <iostream>
#include "BSTree.h"
using namespace std;

int main() {
	/* int array[16] = {50,76,21,4,32,64,15,52,14,100,83,2,3,70,87,80};
	BSTree T;
	cout << "printing the tree before adding the elements\n";
	T.display();
	cout << "printing the tree after adding elements \n";
	for(int i = 0; i < 16; i++) {
		T.InsertLeaf(array[i]);
	}
	T.display();
	cout << endl;
	T.erase(1);
	cout << "disply after delete process\n";
	T.display();
	//T.~BSTree();
	//cout << endl;
	//T.display(); */

	// Initialising variables
	sf::RenderWindow win(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BST-VISUALIZATION");
	BSTree bst;
	int array[16] = { 50,76,21,4,32,64,15,52,14,100,83,2,3,70,87,80 };

	// Adding all the array values to the bst
	for (int i = 0; i < 16; i++) {
		bst.InsertLeaf(array[i]);
	}

	// Main loop
	bool running = true;
	while (running) {
		// Handling events
		sf::Event event;
		while (win.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				running = false;
				win.close();
			}
		}

		bst.draw(win, bst.getRoot());

		win.display();
	}

	return 0;
}

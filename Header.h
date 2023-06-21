#pragma once
#pragma once
#include <string.h>
#include <SFML/Graphics.hpp>

#define WINDOW_HEIGHT 768
#define WINDOW_WIDTH 1366

class BSTree {

private:
	/* Node class */
	class Node {
	public:
		int data;
		int height; // The level of the tree that the node exists (1 for the root)
		Node* left;
		Node* right;
		sf::CircleShape circle;

		//Node constructor
		Node(int  value) {
			data = value;
			height = 1;    // Default height for the root
			left = nullptr;
			right = nullptr;

			// Setting up the circle that will be drawn onto the screen
			circle.setRadius(20.0f);
			circle.setFillColor(sf::Color::White);
			circle.setOutlineColor(sf::Color::Black);
			circle.setOutlineThickness(2.0f);
			circle.setOrigin(20.0f, 20.0f);
			circle.setPosition(WINDOW_WIDTH / 2, 30);  // Default position (for the root)
		}

		// Draws the node as a circle in the given window
		void draw(sf::RenderWindow& window, sf::Font& font);
	};

	/* ATTRIBUTES */

	Node* root;

	/* PRIVATE METHODS */

	// Private method for recursive insertion in the tree
	void InsertLeaf_private(int value, Node* ptr);

	// Private method for recursive "pretty printing"
	void display_private(Node* ptr);

	void erase_Private(int data, Node* remove);

	int FindSmallestPrivate(Node* ptr);

	void RemoveRootMatch();

	// the node that we are remove was marked with match node and this parent mark with remove node
	// the boolean var represents the relation between the remove node and the matching node 
	void RemoveMatch(Node* remove, Node* match, bool left);

	// Its a method to create leaves
	Node* CreateLeaf(int value);

	void RemoveSubtree(Node* ptr); // ptr pointer represents the start point for delete subtree or tree.

public:
	// binary search tree constractor 
	BSTree();

	~BSTree();

	void InsertLeaf(int value);

	// Check if the tree is empty or not
	bool Empty();

	// Display's the BST values sorted (lowest to largest)
	void display();

	// Erase a certain value from the BST
	void erase(int data);

	// Finds the min value of all values that currently exist inside the BST
	int FindSmallest();

	// Recursively draws the tree
	void draw(sf::RenderWindow& window, Node* node, sf::Font& font);

	// Updates the height of all nodes in the bst
	void updatePos(Node* node);

	/* GETTERS & SETTERS */

	inline Node* getRoot() { return root; }
};

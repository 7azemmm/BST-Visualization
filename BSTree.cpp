#include "BSTree.h"
#include<iostream>
using namespace std;

BSTree::BSTree() {
	root = NULL;
}

BSTree::~BSTree() {
	RemoveSubtree(root);
}

void BSTree::RemoveSubtree(Node* ptr) {

	if (ptr != NULL) {
		// Start by recursively removing all nodes under the one given
		if (ptr->left != NULL) { // if true  we will transport to recursive step
			RemoveSubtree(ptr->left);
		}
		if (ptr->right != NULL) { // if true  we will transport to recursive step
			RemoveSubtree(ptr->right);
		}

		// Then remove the node itself
		delete ptr;
	}
	root = NULL;
}

bool BSTree:: Empty() {
	return root == nullptr;
}

BSTree:: Node* BSTree::CreateLeaf(int value) {
	Node* ptr = new Node(value);
	ptr->left = NULL;
	ptr->right = NULL;

	return ptr;
}

// This method just calls the private recursive method for insertion
void BSTree::InsertLeaf(int value) {

	InsertLeaf_private(value, root);

}

// This recursive method searches for the correct position to insert the given value
void  BSTree:: InsertLeaf_private(int value, Node* ptr) {
	// When the BST is empty we just insert a new node with the given value as the root
	if ( Empty() ) {
		root = CreateLeaf(value);
	}
	// If the value is < than the one in the current node, it needs to be placed in the left sub-tree
	else if (value < ptr->data) {
		// If the sub-tree exists (there are nodes on the left) we continue to go down that path
		if (ptr->left != NULL) {
			InsertLeaf_private(value, ptr->left);
		}
		// If not, we insert a new node there
		else {
			ptr->left = CreateLeaf(value);
		}
	}
	// Same for the right sub-tree
	else if (value > ptr->data) {
		if (ptr->right != NULL) {
			InsertLeaf_private(value, ptr->right);
		}
		else {
			ptr->right = CreateLeaf(value);
		}
	}
	else {
		cout << "the element : " << value << " has already added on the tree";
	}
}

// This method just calls the recursive private on for displaying
void  BSTree::display() {
	display_private(root);
}

// Recursive "pretty printing" method
void BSTree::display_private(Node* ptr) {
	// Start printing the values of the tree from lowest(left) value to the largest(right) value
	if (!Empty()) {
		// First the left-most nodes
		if (ptr->left != NULL) {
			display_private(ptr->left);
		}
		// Then the value of the current node
		cout << ptr->data << " ";
		// and then the right-most values
		if (ptr->right != NULL) {
			display_private(ptr->right);
		}
	}
	else {
		cout << "The Tree is Empty\n";
	}
}

// This method just calls the recursive private on for erasing values
void  BSTree::erase(int data) {
	erase_Private(data, root);
}

// This method recursively finds of removeing the node that we want to delete;
void BSTree::erase_Private(int data, Node* remove) {
	if (!Empty()) {
		if (root->data == data) {
			RemoveRootMatch();
		}
		else {
			if (remove->data > data && remove->left != NULL) {
				remove->left->data == data? 

				//for delete the node
				RemoveMatch(remove, remove->left,true):

				//for recursive 
				erase_Private(data, remove->left);
			}
            else if (remove->data < data && remove->right != NULL) {
				remove->right->data == data ?

				//for delete the node
				RemoveMatch(remove, remove->right, false) :

				//for recursive 
				erase_Private(data, remove->right);
			}
			else {
				cout << "The node  " << data << " is not found on the tree\n";
			}
		}
	}
	else {
		cout << "The tree is Empty as there's nothing to delete it \n";
	}
}

// This method just calls the recursive private on for finding the smallest value
int  BSTree:: FindSmallest() {
	return FindSmallestPrivate(root);
}

/* in the private method we can start at subtree if we would like as we use to represent smallestRightSubtree
  by passing the node that we start at it as in this method.
*/
int BSTree::FindSmallestPrivate(Node* ptr) {
	if (!Empty()) {
		if (ptr->left != NULL) {  // if this statment is true we must travers down by recursiev process.
			return FindSmallestPrivate(ptr->left);
		}
		else {
			return ptr->data;
		}
	}

	else {
		cout << "The tree is empty\n";
		return -1;
	}
}

void BSTree::RemoveRootMatch() {
	if (!Empty()) {
		Node* delptr = root;
		int rootData = root->data;
		int smallestRightSubtree;
		//case 1: that the root do not have any children
		if (root->left == NULL && root->right == NULL) {
			root = NULL;
			delete delptr;
		}
		//case 2: that  the root have one child 
		else if (root->left == NULL && root->right != NULL) {
			root = root->right;
			delptr->right = NULL;
			delete delptr;
		cout << "The root node with data  " << rootData << " was deleted ." << " and  the new root contans data " << root->data << endl;
		}
		//case 2: that  the root have one child
		else if (root->left != NULL && root->right == NULL) {
			root = root->left;
			delptr->left = NULL;
			delete delptr;
			cout << "The root node with data  " << rootData << " was deleted ." << " and  the new root contans data " << root->data << endl;
		}
		//case 3 : that  the root have two children
		else {
			smallestRightSubtree = FindSmallestPrivate(root->right);
			erase_Private(smallestRightSubtree, root);// to delete the smallest node in subtree
			root->data = smallestRightSubtree; //overwrite info on the deleted node;
			cout << "The root data contains data " << rootData << " was overwritten with data  " << root->data;

		}
	}
	else {
		cout << "Can not remove the root as the Tree is empty\n";
	}
}

// the node that we are remove was marked with match node and this parent marke with remove node 
// the boolen var is represent the relation between the remove node and the matching node 
void BSTree:: RemoveMatch(Node* remove, Node* match,bool left) {
	if (!Empty()) {
		Node* delptr;
		int matchData = match->data;
		int smallestRightSubtree;

		//case 1 : where the matching node that want to delete do not have any children
		if (match->left == NULL && match->right == NULL) {
			delptr = match;                                                  //remove node represent parent node
			left == true ? remove->left =NULL  : remove->right = NULL; //check the node that we deleted left or righr
			delete delptr;
			cout << "The node that contans data " << matchData << " Was deleted\n";

		}

		//case 2 : where the matching node that want to delete  have one  child
		else if (match->left == NULL && match->right != NULL) {                                                                             //remove node represent parent node
			left == true ? remove->left = match->right : remove->right = match->right;  //connect the parent with child 
			match->right = NULL; // disconnect our matching node  form the tree
			delptr = match;
			delete delptr;
			cout << "The node that contans data " << matchData << " Was deleted\n";
		}

		//case 2 : where the matching node that want to delete  have one  child
		else if (match->left != NULL && match->right == NULL) {                                                                             //remove node represent parent node
			left == true ? remove->left = match->left : remove->right = match->left;  //connect the parent with child 
			match->left = NULL;
			delptr = match;
			delete delptr;
			cout << "The node that contans data " << matchData << " Was deleted\n";
		}

		//case 3 : where the matching node that want to delete  have two  children
		else {
			smallestRightSubtree = FindSmallestPrivate(match->right);
			erase_Private(smallestRightSubtree, match); // to delete the smallest node in subtree
			match->data = smallestRightSubtree;


		}

	}
	else {
		cout << "Can not remove match. as the tree is empty\n";
	}
}

// Recursively draws the BST in the given window, starting from the given node/root
void BSTree::draw(sf::RenderWindow& window, Node* node) {
	// Returning on nullptr nodes (no node to draw)
	if (node == nullptr) return;

	// Drawing the current node
	window.draw(root->circle);

	// And finally drawing it's children (if they exist)

	if (node->left != nullptr) {
		// Drawing a line to connect the nodes 
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(node->circle.getPosition().x, node->circle.getPosition().y + 30), sf::Color::Black),
			sf::Vertex(sf::Vector2f(node->left->circle.getPosition().x, node->left->circle.getPosition().y - 30), sf::Color::Black)
		};
		window.draw(line, 2, sf::Lines);

		// Recursively calling the function for the left child of the current node
		draw(window, node->left);
	}

	if (node->right != nullptr) {
		// Drawing a line to connect the nodes 
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(node->circle.getPosition().x, node->circle.getPosition().y + 30), sf::Color::Black),
			sf::Vertex(sf::Vector2f(node->right->circle.getPosition().x, node->right->circle.getPosition().y - 30), sf::Color::Black)
		};
		window.draw(line, 2, sf::Lines);

		// Recursively calling the function for the right child of the current node
		draw(window, node->right);
	}
}

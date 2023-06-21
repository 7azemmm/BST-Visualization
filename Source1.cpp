#include <iostream>
#include "Header.h"
using namespace std;

enum State {
	IDLE,
	START,
	INSERTING,
	REMOVING,
	END
};

// Draws a button on the screen at the given 
bool drawButton(sf::RenderWindow& window, const string str, sf::Font& font, sf::Vector2f pos, sf::Vector2f size, sf::Color c, bool pressable = true);

// Check if the give point collides with the given rectangle
bool checkCollisionPointRect(sf::RectangleShape& rect, sf::Vector2f point);

// Fills the screen with the given Color(like window.clear) or the given texture
void fillScreen(sf::RenderWindow& window, sf::Color color, sf::Texture* texture = nullptr, bool resetRect = false);

int main() {
	// Initialising variables

	sf::RenderWindow win(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BST-GAME", sf::Style::Default);

	BSTree bst;
	State state = START;
	string input;

	sf::Font font;
	// Attempting to load font
	if (!font.loadFromFile("BestOfTreat.otf")) {
		cerr << "Failed to load Font" << endl;
	}
	sf::Text my_text;
	my_text.setFont(font);
	my_text.setString("hello,\n We will teach how binary search tree is built and visualize to you what happens \n \n\n\n \t\t\t\t\t\t\t\t\tDescription : \n\n Binary Search Tree is a node-based binary tree data structure which has : \n\nThe left subtree of a node contains only nodes with keys lesser than the node key.\n\nThe right subtree of a node contains only nodes with keys greater than the node key\n\nThe left and right subtree each must also be a binary search tree\n\nnow we will see visualization for Binar search tree\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t press on visualize");
	my_text.setPosition(10, 10);
	// Main loop
	while (win.isOpen()) {
		// Clear window
		win.clear(sf::Color(1, 50, 32));

		// Handling events
		sf::Event event;
		while (win.pollEvent(event)) {
			// Checking for window close
			if (event.type == sf::Event::Closed)
				win.close();

			// Checking for user input through keyboard
			// NOTE: We only care about that if we are in an INSERTING or REMOVING state
			if (event.type == sf::Event::TextEntered && (state == INSERTING || state == REMOVING)) {
				if (event.text.unicode >= '0' && event.text.unicode <= '9') // Making sure input is a number
					input += event.text.unicode;
			}
		}

		// Drawing starting screen
		if (state == START) {
			// Print the starting image

			win.draw(my_text);

			// Draw start button
			bool pressed = drawButton(win, "VISUALIZE", font, sf::Vector2f(1090, 650), sf::Vector2f(90, 50), sf::Color(1, 50, 32), 1);
			if (pressed) state = IDLE;
		}
		// Drawing BST visualization screen
		else if (state == IDLE) {
			// Draw the bst
			bst.draw(win, bst.getRoot(), font);

			// Draw the insert button
			string str = "insert";
			bool insert = drawButton(win, str, font, sf::Vector2f(10, 10), sf::Vector2f(100, 30), sf::Color::Blue);
			if (insert) state = INSERTING;

			// Draw remove button
			str = "remove";
			insert = drawButton(win, str, font, sf::Vector2f(WINDOW_WIDTH - 110, 10), sf::Vector2f(100, 30), sf::Color::Red);
			if (insert) state = REMOVING;

			/* Process for INSERTING / REMOVING states */
			if (state == INSERTING || state == REMOVING) {
				fillScreen(win, sf::Color(0, 0, 0, 100));  // Shading background

				// Draw main rectangle
				sf::RectangleShape rect;
				rect.setPosition(sf::Vector2f(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4));
				rect.setSize(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
				rect.setFillColor(sf::Color::Green);
				win.draw(rect);

				// Draw Label
				sf::Text text;
				text.setFont(font);
				text.setString("GIVE NUMBER");
				text.setCharacterSize(70);
				text.setStyle(sf::Text::Bold);
				text.setFillColor(sf::Color::Black);
				text.setPosition(WINDOW_WIDTH / 4 + 40, WINDOW_HEIGHT / 4 + 20);
				win.draw(text);

				// Draw user input line
				sf::RectangleShape inputRect;
				inputRect.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 15));
				inputRect.setSize(sf::Vector2f(100, 30));
				inputRect.setFillColor(sf::Color(255, 255, 255));
				win.draw(inputRect);

				// Draw current input
				text.setString(input);
				text.setCharacterSize(20);
				text.setStyle(sf::Text::Bold);
				text.setPosition(sf::Vector2f(inputRect.getPosition()));
				win.draw(text);

				// OK button and it's functionality
				bool OK = drawButton(win, "OK", font, inputRect.getPosition() + sf::Vector2f(25, 50), sf::Vector2f(50, 30), sf::Color::Black);
				if (OK && input.length() != 0) {
					int value = stoi(input);

					if (state == REMOVING) {
						bst.erase(value);
						bst.updatePos(bst.getRoot());  // When removing we also need to update the circle positions
					}
					else bst.InsertLeaf(value);  // state == INSERTING

					// Reset state and input
					state = IDLE;
					input.clear();
				}
			}

		}


		win.display();
	}

	return 0;
}

void fillScreen(sf::RenderWindow& window, sf::Color color, sf::Texture* texture, bool resetRect) {
	// Creating a rectangle with origin at (0,0) (by default)
	sf::RectangleShape rect;

	// Setting it's size equal to the size of the window
	sf::Vector2u size = window.getSize();
	rect.setSize(sf::Vector2f(float(size.x), float(size.y)));
	rect.setFillColor(color);

	// When a texture is passed, the user wants that as a background and not just a color
	if (texture != nullptr)
		rect.setTexture(texture, resetRect);

	// Drawing into the screen
	window.draw(rect);
}

bool checkCollisionPointRect(sf::RectangleShape& rect, sf::Vector2f point) {
	sf::FloatRect r = rect.getGlobalBounds();

	// Checking manually whether the point is within the rectangle
	if (point.x >= r.left && point.x <= r.left + r.width
		&& point.y >= r.top && point.y <= r.top + r.height) {
		return true;
	}

	return false;
}

bool drawButton(sf::RenderWindow& window, const string str, sf::Font& font, sf::Vector2f pos, sf::Vector2f size, sf::Color c, bool pressable) {
	bool pressed = false;

	// Creating rect
	sf::RectangleShape startButton;
	startButton.setSize(size);
	startButton.setPosition(pos);
	startButton.setFillColor(c);


	// If the button is not pressable(label) then we jsut draw it and return
	if (!pressable) {
		window.draw(startButton);
		return false;
	}

	/* PRESSABLE BEHAVIOUR */

	// Checking if mouse is hovering over the button
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	if (checkCollisionPointRect(startButton, sf::Vector2f(mousePos))) {
		// Shading button when mouse is hovering over it
		startButton.setFillColor(sf::Color(200, 157, 124, 200));

		// Check for user left mouse button click (also checking if it was previously pressed)
		pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	}

	window.draw(startButton);


	// Draw the text on top
	sf::Text text;
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(pos + sf::Vector2f(5, 5));
	window.draw(text);

	return pressed;
}
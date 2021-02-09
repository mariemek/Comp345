#include <string>
#include "Cards.h"
#include <iostream>
using namespace std;


int main() {

	int hello;

    // create a deck
    Deck deck = Deck();

    // generate the cards
    deck.generateDeck();
    cout << "\n\n___________________________________________________Initial Deck\n\n" << endl;
    deck.printDeck();

    // shuffle the deck
    deck.shuffleDeck();
    cout << "\n\n____________________________________________________ Shuffled Deck\n\n" << endl;
    deck.printDeck();


    cout << "\n\n___________________________________________________Card Space\n\n" << endl;
    // draw initial hand
    Hand hand = Hand(&deck);
   // hand.printHand();
	//

    //Testing exchange method
    int coins = 8;
    int index = 0;
    while (index >= 0) {
        hand.printHand();
        cout << "Please enter the index of the card you want tp pick or a negative number to exit: ";
        cin >> index;
        hand.exchange(index, &coins);
    }
}
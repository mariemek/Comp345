//===================================================================
// Course: COMP 345
// Professor: Nora Houari
// Team: 14
// Students:
//      Adam Yafout - 40040306
//      Bryan Lee - 40079332
//      Carl Randyl Tuquero - 40067781
//      Sobhan Mehrpour - 40122438
//      Vithura Muthiah - 40062305
//===================================================================

#include "Player.h"
#include <iostream>
#include "Cards/Cards.h"
#include "BiddingFacility.h"
using namespace std;

// ============================================
// Player Implementation
// ============================================

// Player default constructor.
Player::Player()
{
	name = "Odysseus";
	numOfCoins = 0;
	bidFaci = new BiddingFacility();
	playerTerritory = list<Territory*>();
	playerHand = list<Card*>();
	cities = list<City*>();
	armies = list<Army*>();
}

// Player value constructor.
Player::Player(string aName, int coinNum)
{
	name = aName;
	numOfCoins = coinNum;
	bidFaci = new BiddingFacility();
	playerTerritory = list<Territory*>();
	playerHand = list<Card*>();
	cities = list<City*>();
	armies = list<Army*>();
}

// Player copy constructor.
Player::Player(Player& anotherPlayer)
{
	name = anotherPlayer.name;
	numOfCoins = anotherPlayer.numOfCoins;

	if (anotherPlayer.bidFaci)
		bidFaci = new BiddingFacility(*(anotherPlayer.bidFaci));
	else
		bidFaci = nullptr;

	// Shallow copy because the map is the same.
	for (Territory* territory : anotherPlayer.playerTerritory)
	{
		playerTerritory.push_back(territory);
	}

	for (Card* card : anotherPlayer.playerHand)
	{
		playerHand.push_back(new Card(*card));
	}

	for (City* city : anotherPlayer.cities)
	{
		cities.push_back(new City(*city));
	}

	for (Army* army : anotherPlayer.armies)
	{
		armies.push_back(new Army(*army));
	}
}

// Player destructor.
Player::~Player()
{
	// Cards and territories must be deallocated independently since they belong to all players.

	if (bidFaci)
	{
		delete bidFaci;
		bidFaci = nullptr;
	}

	// Deallocating all cities.
	for (list<City*>::iterator iter = cities.begin(); iter != cities.end(); ++iter)
	{
		City* tempCity = *iter;
		delete tempCity;
		tempCity = nullptr;
	}

	// Deallocating all armies.
	for (list<Army*>::iterator iter = armies.begin(); iter != armies.end(); ++iter)
	{
		Army* tempArmy = *iter;
		delete tempArmy;
		tempArmy = nullptr;
	}
}

// Switched Pay coin into a boolean type 
// Pay coin.
bool Player::payCoin(int& cost)
{
	if (this->numOfCoins >= cost)
	{
		numOfCoins = numOfCoins - cost;
		cout << this->name << " has now " << this->numOfCoins << endl;
		return true;
	}
	else
	{
		cout << this->name + " doesn't have enough coins " << endl;
		return false;
	}
}

// Creates new army.
void Player::placeNewArmies(Territory* territory)
{
	Army* army = new Army(this, territory);
	territory->addArmy();
	armies.push_back(army);
	cout << "Created " << *army << " in " << *territory << endl;
	army = nullptr;
}

// Moves army. Should work for both land and water.
void Player::moveArmies(Army* army, Territory* endLocation)
{
	Territory* oldPos = army->getPosition();
	oldPos->removeArmy();
	army->setPosition(endLocation);
	endLocation->addArmy();
	cout << "Moved " << *army << " from " << *oldPos << " to " << *endLocation << endl;
	oldPos = nullptr;
}

// Moves army over land.
void Player::moveOverLand(Army* army, Territory* endLocation)
{
	Territory* oldPos = army->getPosition();
	oldPos->removeArmy();
	army->setPosition(endLocation);
	endLocation->addArmy();
	cout << "Moved " << *army << " overland from " << *oldPos << " to " << *endLocation << endl;
	oldPos = nullptr;
}

// Creates a city on the territory. Is not currently functional because we have no idea of what a city is.
void Player::buildCity(Territory* territory)
{
	City* city = new City(this, territory);
	this->cities.push_back(city);
	cout << *city << " is built in " << *territory;
	city = nullptr;
}

// Destroys army and deallocates dynamic memory.
void Player::destroyArmy(Army* army)
{
	army->getPosition()->removeArmy();
	army->getOwner()->armies.remove(army);
	cout << *army << " is destroyed!";
	delete army;
	army = nullptr;
}

// Returns player name.
string Player::getName()
{
	return name;
}

void Player::setName(string n) {
	name = n;
}

int Player::getCoins() {
	return numOfCoins;
}

void Player::setCoins(int c) {
	numOfCoins = c;
}

BiddingFacility* Player::getBidFaci() const { 
	return bidFaci;
}

// Returns list of player armies.
list<Army*>* Player::getArmies()
{
	return &armies;
}

// toString
ostream& operator<<(ostream& strm, const Player& player)
{
	return strm << player.name << ": " << player.numOfCoins << " coins.";
}

Player& Player::operator= (const Player& anotherPlayer)
{
	if (&anotherPlayer == this)
		return *this;

	name = anotherPlayer.name;
	numOfCoins = anotherPlayer.numOfCoins;

	if (anotherPlayer.bidFaci)
		bidFaci = new BiddingFacility(*(anotherPlayer.bidFaci));
	else
		bidFaci = nullptr;

	// Shallow copy because the map is the same.
	for (Territory* territory : anotherPlayer.playerTerritory)
	{
		playerTerritory.push_back(territory);
	}

	for (Card* card : anotherPlayer.playerHand)
	{
		playerHand.push_back(new Card(*card));
	}

	for (City* city : anotherPlayer.cities)
	{
		cities.push_back(new City(*city));
	}

	for (Army* army : anotherPlayer.armies)
	{
		armies.push_back(new Army(*army));
	}

	return *this;
}

// ============================================
// Army Implementation
// ============================================

// Default constructor.
Army::Army()
{
	owner = nullptr;
	position = nullptr;
}

// Army constructor.
Army::Army(Player* anOwner, Territory* aPosition)
{
	owner = anOwner;
	position = aPosition;
}

// Copy constructor.
Army::Army(Army& anotherArmy)
{
	// Shallow copies because the owner and position will the same.
	if (anotherArmy.owner)
	{
		owner = anotherArmy.owner;
	}
	else
	{
		owner = nullptr;
	}

	if (anotherArmy.position)
	{
		position = anotherArmy.position;
	}
	else
	{
		position = nullptr;
	}
}

// Army destructor.
Army::~Army()
{
	// Doesn't make sense to delete them because owner/position will exist even after an army is deleted.
	owner = nullptr;
	position = nullptr;
}

// Returns owner name.
string Army::getOwnerName()
{
	return (*owner).getName();
}

// Returns pointer to owner.
Player* Army::getOwner()
{
	return owner;
}

// Returns pointer to current position.
Territory* Army::getPosition()
{
	return position;
}

// Changes position.
void Army::setPosition(Territory* newPosition)
{
	position = newPosition;
}

// Army's toString
ostream& operator<<(ostream& strm, const Army& army)
{
	return strm << army.owner->getName() << "'s army";
}

// Assignment operator overload.
Army& Army::operator=(Army& anotherArmy)
{
	if (&anotherArmy == this)
		return *this;

	// Shallow copies because the owner and position will the same.
	if (anotherArmy.owner)
	{
		owner = anotherArmy.owner;
	}
	else
	{
		owner = nullptr;
	}

	if (anotherArmy.position)
	{
		position = anotherArmy.position;
	}
	else
	{
		position = nullptr;
	}

	return *this;
}

// ============================================
// City Implementation
// ============================================

// Default constructor.
City::City()
{
	owner = nullptr;
	position = nullptr;
}

// City constructor.
City::City(Player* anOwner, Territory* aPosition)
{
	owner = anOwner;
	position = aPosition;
}

City::City(City& anotherCity)
{
	// Shallow copies because the owner and position will the same.
	if (anotherCity.owner)
	{
		owner = anotherCity.owner;
	}
	else
	{
		owner = nullptr;
	}

	if (anotherCity.position)
	{
		position = anotherCity.position;
	}
	else
	{
		position = nullptr;
	}
}

// City destructor.
City::~City()
{
	// Doesn't make sense to delete them because owner/position will exist even after an army is deleted.
	owner = nullptr;
	position = nullptr;
}

// Returns owner name.
string City::getOwnerName()
{
	return owner->getName();
}

// Returns pointer to owner.
Player* City::getOwner()
{
	return owner;
}

// Returns pointer to current position.
Territory* City::getPosition()
{
	return position;
}

// City's toString
ostream& operator<<(ostream& strm, const City& city)
{
	return strm << city.owner->getName() << "'s city";
}

// Assignment operator overload.
City& City::operator=(City& anotherCity)
{
	if (&anotherCity == this)
		return *this;

	// Shallow copies because the owner and position will the same.
	if (anotherCity.owner)
	{
		owner = anotherCity.owner;
	}
	else
	{
		owner = nullptr;
	}

	if (anotherCity.position)
	{
		position = anotherCity.position;
	}
	else
	{
		position = nullptr;
	}

	return *this;
}
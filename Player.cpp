#include "Player.h"
#include <iostream>
#include "Cards/Cards.h"
#include "BiddingFacility.h"
using namespace std;
// ============================================
// Player Implementation
// ============================================



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

// Player destructor.
Player::~Player()
{
	// Not deallocating biddingFacility because it is shared by all players, so it must be deallocated at the end of the program itself.
	// Cards and territories must also be deallocated independently since they belong to all players.

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
bool Player::PayCoin(int& cost)
{
	if (this->numOfCoins > cost)
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
void Player::PlaceNewArmies(Territory* territory)
{
	Army* army = new Army(this, territory);
	territory->AddArmy();
	armies.push_back(army);
	cout << "Created " << *army << " in " << *territory << endl;
	army = nullptr;
}

// Moves army. Should work for both land and water.
void Player::MoveArmies(Army* army, Territory* endLocation)
{
	Territory* oldPos = army->GetPosition();
	oldPos->RemoveArmy();
	army->SetPosition(endLocation);
	endLocation->AddArmy();
	cout << "Moved " << *army << " from " << *oldPos << " to " << *endLocation << endl;
	oldPos = nullptr;
}

// Moves army over land.
void Player::MoveOverLand(Army* army, Territory* endLocation)
{
	Territory* oldPos = army->GetPosition();
	oldPos->RemoveArmy();
	army->SetPosition(endLocation);
	endLocation->AddArmy();
	cout << "Moved " << *army << " overland from " << *oldPos << " to " << *endLocation << endl;
	oldPos = nullptr;
}

// Creates a city on the territory. Is not currently functional because we have no idea of what a city is.
void Player::BuildCity(Territory* territory)
{
	City* city = new City(this, territory);
	this->cities.push_back(city);
	cout << *city << " is built in " << *territory;
	city = nullptr;
}

// Destroys army and deallocates dynamic memory.
void Player::DestroyArmy(Army* army)
{
	army->GetPosition()->RemoveArmy();
	army->GetOwner()->armies.remove(army);
	cout << *army << " is destroyed!";
	delete army;
	army = nullptr;
}

// Returns player name.
string Player::GetName()
{
	return name;
}

void Player::SetName(string n) {
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
list<Army*>* Player::GetArmies()
{
	return &armies;
}

// toString
ostream& operator<<(ostream& strm, const Player& player)
{
	return strm << player.name << ": " << player.numOfCoins << " coins.";
}

// ============================================
// Army Implementation
// ============================================

// Army constructor.
Army::Army(Player* anOwner, Territory* aPosition)
{
	owner = anOwner;
	position = aPosition;
}

// Army destructor.
Army::~Army()
{
	// Doesn't make sense to delete them because owner/position will exist even after an army is deleted.
	owner = nullptr;
	position = nullptr;
}

// Returns owner name.
string Army::GetOwnerName()
{
	return (*owner).GetName();
}

// Returns pointer to owner.
Player* Army::GetOwner()
{
	return owner;
}

// Returns pointer to current position.
Territory* Army::GetPosition()
{
	return position;
}

// Changes position.
void Army::SetPosition(Territory* newPosition)
{
	position = newPosition;
}

// Army's toString
ostream& operator<<(ostream& strm, const Army& army)
{
	return strm << army.owner->GetName() << "'s army";
}

// ============================================
// City Implementation
// ============================================

// City constructor.
City::City(Player* anOwner, Territory* aPosition)
{
	owner = anOwner;
	position = aPosition;
}

// City destructor.
City::~City()
{
	// Doesn't make sense to delete them because owner/position will exist even after an army is deleted.
	owner = nullptr;
	position = nullptr;
}

// Returns owner name.
string City::GetOwnerName()
{
	return owner->GetName();
}

// Returns pointer to owner.
Player* City::GetOwner()
{
	return owner;
}

// Returns pointer to current position.
Territory* City::GetPosition()
{
	return position;
}

// City's toString
ostream& operator<<(ostream& strm, const City& city)
{
	return strm << city.owner->GetName() << "'s city";
}

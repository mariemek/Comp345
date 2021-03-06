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

#pragma once
#include <list>
#include <iostream>
#include <vector>


class Observer
{
public:
	virtual ~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};

// the subject Class
class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	virtual ~Subject();
private:
	std::list<Observer*>* _observers;

};

// Forward declarations to make the compiler happy.
class Player;
class Card;
class Hand;
class Map;

// A class that encapsulates each turn.
// Provides methods that allow the player to pick their card and play it.
class Turn : public Subject
{
private:
	Player* playerTurn;
	Card* selectedCard;
	Hand* gameHand;
	Map* gameMap;
	int maxNumOfTurns;
	int selectedIndex;

public:
	// Constructors and destructors.
	Turn();
	Turn(int, Map*, Hand*, Player* = nullptr);
	Turn(const Turn&);
	~Turn();

	// Setters and getters.
	Player* getPlayerTurn();
	void setPlayerTurn(Player*);
	Card* getSelectedCard();
	void setSelectedCard(Card*);
	Hand* getGameHand();
	void setGameHand(Hand*);
	Map* getGameMap();
	void setGameMap(Map*);
	int getMaxNumOfTurns();
	void setMaxNumOfTurns(int);
	int getSelectedIndex();
	void setSelectedIndex(int);

	// Service methods.
	void playTurn();

	// Operators.
	friend std::ostream& operator <<(std::ostream& output, const Turn& turn);
	const Turn& operator =(const Turn&);
};

class TurnView : public Observer
{
public :
	TurnView();
	TurnView(Turn* t);
	~TurnView();
	void Update();
	void display();
private:
	Turn* _subject;
};

// An observer that updates whenever it's a new player's turn.
class PlayerTurnViewer : public Observer
{
public:
	// Constructors and destructors.
	PlayerTurnViewer();
	PlayerTurnViewer(Turn* turn);
	PlayerTurnViewer(const PlayerTurnViewer& other);
	~PlayerTurnViewer();

	// Important method.
	void Update();

	// Operators.
	friend std::ostream& operator <<(std::ostream& stream, const PlayerTurnViewer& obj);
	PlayerTurnViewer operator =(const PlayerTurnViewer& other);

private:
	Turn* subject;
	Player* playerTurn;
	int turnCount;
};

// An observer that updates whenever it's a new player's turn.
class CardPickViewer : public Observer
{
public:
	// Constructors and destructors.
	CardPickViewer();
	CardPickViewer(Turn* turn);
	CardPickViewer(const CardPickViewer& other);
	~CardPickViewer();

	// Important method.
	void Update();

	// Operators.
	friend std::ostream& operator <<(std::ostream& stream, const CardPickViewer& obj);
	CardPickViewer operator =(const CardPickViewer& other);

private:
	Turn* subject;
	Card* selectedCard;
};

//Prints messages dictating the current state of the player's action.
class PlayerActionViewer : public Observer
{
public:
	PlayerActionViewer();
	PlayerActionViewer(Player* player);
	PlayerActionViewer(const PlayerActionViewer& other);
	~PlayerActionViewer();

	// Important method.
	void Update();

	// Operators.
	friend std::ostream& operator <<(std::ostream& stream, const PlayerActionViewer& obj);
	PlayerActionViewer operator =(const PlayerActionViewer& other);

private:
	Player* subject;
	std::string playerAction;

};

// Keeps track of a players card bonuses and prints a message if one changes.
class CardBonusViewer : public Observer
{
public:
	CardBonusViewer();
	CardBonusViewer(Player* player);
	CardBonusViewer(const CardBonusViewer& other);
	~CardBonusViewer();

	// Important method.
	void Update();

	// Operators.
	friend std::ostream& operator <<(std::ostream& stream, const CardBonusViewer& obj);
	CardBonusViewer operator =(const CardBonusViewer& other);

private:
	Player* subject;
	int moveBonus;
	int flightBonus;
	int armyBonus;
	bool immunityBonus;
};

class GameState : public Subject {
private:
	Map* map;
	std::vector<int> coins;
	std::vector<int> continents;
	std::vector<int> victoryPoints;
	std::vector<int> territories;
	std::vector<int> elixirAmount;

public:
	// Constructors & destructor
	GameState();
	GameState(Map* map);
	GameState(const GameState&);
	~GameState();

	// Accessors & Mutators
	std::vector<int> getCoins();
	std::vector<int> getContinents();
	std::vector<int> getVictoryPoints();
	std::vector<int> getTerritories();
	std::vector<int> getElixirAmount();
	void setCoins(std::vector<int>);
	void setContinents(std::vector<int>);
	void setVictoryPoints(std::vector<int>);
	void setTerritories(std::vector<int>);
	void setElixirAmount(std::vector<int>);

	// Functions
	void computeGameState();
};

class View: public Observer{
	// Member variable.
private:
	GameState *gmstate;

public:
	// Constructors & destructor
	View();
	View(GameState*);
	~View();

	// Function
	void display(int i);
	virtual void Update();

private:
	void printbar(int);
	std::vector<int> coins;
	std::vector<int> continents;
	std::vector<int> victoryPoints;
	std::vector<int> territories;
	std::vector<int> elixirAmount;
};

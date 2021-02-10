#include "Player.h"

int main()
{
	BiddingFacility* bidding = new BiddingFacility();
	Territory* territory1 = new Territory();
	Territory* territory2 = new Territory();
	Player* player1 = new Player("Achilles", bidding);

	player1->PlaceNewArmies(territory1);

	Army* army = player1->GetArmies()->front();
	player1->MoveArmies(army, territory2);
	player1->MoveOverLand(army, territory1);
	player1->DestroyArmy(army);

	return 0;
}


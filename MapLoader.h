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
#include "Map.h"
#include <string>
#include <fstream>
#include <sstream>

class MapLoader {
    // Map being built.
    Map *map;

public:
    // Constructors.
    MapLoader();
    MapLoader(const MapLoader&);

    // Destructor.
    ~MapLoader();
    
    // Public methods.
    void readMapFile(std::string fileName, int);
    bool verifyFile(std::string fileName);
    Map* getMap();

    // Overloaded assignment operator.
    MapLoader& operator=(const MapLoader&);
    
private:
    // Helper methods for reading a map file.
    void createContinent(std::ifstream&);
    void joinTerritories(std::ifstream&);
    void createBoard(std::ifstream&, std::map<int, std::map<std::string, Territory*>>&, int&, bool&, int&);
    bool shouldCreateBoard(int&);
    bool verifyContinent(std::istringstream&);
    bool verifyJoin(std::istringstream&);
    bool verifyBoard(std::istringstream&);
    friend std::ostream& operator<<(std::ostream&, const MapLoader&);
};

// Forward declaration to make compiler happy.
class Player;

MapLoader* startGame();
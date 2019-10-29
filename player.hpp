#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <random>
#include <time.h>

class Player
{
    public:
        std::string name;
        std::vector<std::string> heroMap;
        std::vector<std::string> enemyMap;
        std::vector<std::string> shipPositions;
        int shipCount;
        void generateMap(bool isEnemy);
        void printMap(bool isEnemy);
        bool hit(std::string coords);
        void resetShipPositions();

};
class Ship : public Player
{
    public:
        std::vector<std::string> setShipPosition(Player& player);
        void markShipSunk(Player& player);
        void print();
        std::vector<std::string> position;
        int size;
        int life;
        std::string name;
};
bool checkSpace(int x, int y, int dir, int size, Player& player);
#endif
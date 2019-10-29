#include "player.hpp"
std::string getShip(std::unordered_map<std::string, Ship>& ships, std::string square){
    for(auto& a : ships){
        for(std::string str : ships[a.first].position){
            if(str == square){
                return a.first;
            }
        }
    }
}
int main(){
    Player player;
    player.generateMap(true);
    player.resetShipPositions();
    Ship ship;
    std::vector<std::string> shipNames = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};
    std::vector<int> shipSizes = {5, 4, 3, 3, 2};
    std::unordered_map<std::string, Ship> ships;
    for(int i = 0; i < 5; ++i){
        ship.size = shipSizes[i];
        ship.life = shipSizes[i];
        ship.name = shipNames[i];
        ship.position = ship.setShipPosition(player);
        ships[shipNames[i]] = ship;
        player.shipCount++;
    }
    std::string square = "";
    std::string result = "";
    while(1){
        system("clear");
        player.printMap(true);
        std::cout << square << ": " << result << "\n";
        if(player.shipCount == 0){
            std::cout << "You won!\n";
            break;
        }
        std::cout << "Fire: ";
        std::cin >> square;
        if(player.hit(square)){
            result = "HIT!";
            std::string hitShip = getShip(ships, square);
            ships[hitShip].life--;
            if(ships[hitShip].life == 0){
                result += hitShip + " sunk!";
                ships[hitShip].markShipSunk(player);
                player.shipCount--;
            }
        }
        else{
            result = "MISS!";
        }
    }
}
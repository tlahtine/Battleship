#include "player.hpp"
void Player::generateMap(bool isEnemy)
{
    if(isEnemy)
    {
        enemyMap.clear();
        for(int i = 0; i < 10; i++)
        {
            if(i < 9)
            {
                std::string str = " " + std::to_string(i + 1) + "| | | | | | | | | | |";
                enemyMap.emplace_back(str);
            }
            else
            {
                enemyMap.emplace_back("10| | | | | | | | | | |");
            }
        }
    }
}
void Player::printMap(bool isEnemy){
    std::cout << "  |A|B|C|D|E|F|G|H|I|J|\n";
    if(isEnemy){
        for(std::string str : enemyMap){
            std::cout << str << std::endl;
        }
    }
    std::cout << "---Legend---\n";
    std::cout << "O Ship\n";
    std::cout << "@ Sunk ship\n";
    std::cout << "X Missed attack\n";
}
bool Player::hit(std::string square){
    int x = int(square[0]) - 65;
    int y = stoi(square.substr(1)) - 1;
    if(enemyMap[y][3 + x * 2] != ' '){
        return false;
    }
    if(shipPositions[y][x] == 'O'){
        enemyMap[y][3 + x * 2] = 'O';
        return true;
    }
    else{
        enemyMap[y][3 + x * 2] = 'X';
    }
    return false;
}
void Player::resetShipPositions(){
    shipPositions.clear();
    std::string str = "          ";
    for(int i = 0; i < 10; ++i){
        shipPositions.emplace_back(str);
    }
}
void Ship::markShipSunk(Player& player){
    for(std::string square : position){
        int x = int(square[0]) - 65;
        int y = stoi(square.substr(1)) - 1;
        player.enemyMap[y][3 + x * 2] = '@';
    }
}
std::vector<std::string> Ship::setShipPosition(Player& player){
    int x, y, dir;
    std::string str = "ABCDEFGHIJ";
    std::vector<std::string> pos;
    srand(time(0));
    dir = rand() % 2;
    if(dir == 0){
        x = rand() % (10 - size);
        y = rand() % 10;
    }
    else{
        x = rand() % 10;
        y = rand() % (10 - size);
    }
    while(!checkSpace(x, y, dir, size, player)){
        dir = rand() % 2;
        if(dir == 0){
            x = rand() % (10 - size);
            y = rand() % 10;
        }
        else{
            x = rand() % 10;
            y = rand() % (10 - size);
        }
    }
    if(dir == 0){
        for(int i = x; i < x + size; ++i){
            player.shipPositions[y][i] = 'O';
            pos.emplace_back(str[i] + std::to_string(y + 1));
        }
        if(x > 0){
            player.shipPositions[y][x - 1] = 'X';
        }
        if(x + size < 10){
            player.shipPositions[y][x + size] = 'X';
        }
        if(y > 0){
            for(int i = x; i < x + size; ++i){
                player.shipPositions[y - 1][i] = 'X';
            }
        }
        if(y < 9){
            for(int i = x; i < x + size; ++i){
                player.shipPositions[y + 1][i] = 'X';
            }
        }
    }
    if(dir == 1){
        for(int i = y; i < y + size; ++i){
            player.shipPositions[i][x] = 'O';
            pos.emplace_back(str[x] + std::to_string(i + 1));
        }
        if(y > 0){
            player.shipPositions[y - 1][x] = 'X';
        }
        if(y + size < 10){
            player.shipPositions[y + size][x] = 'X';
        }
        if(x > 0){
            for(int i = y; i < y + size; ++i){
                player.shipPositions[i][x - 1] = 'X';
            }
        }
        if(x < 9){
            for(int i = y; i < y + size; ++i){
                player.shipPositions[i][x + 1] = 'X';
            }
        }
    }
    return pos;
}
bool checkSpace(int x, int y, int dir, int size, Player& player){
    if(dir == 0){
        std::string str = player.shipPositions[y];
        for(int i = x; i < x + size; ++i){
            if(str[i] != ' '){
                return false;
            }
        }
    }
    if(dir == 1){
        for(int i = y; i < y + size; ++i){
            std::string str = player.shipPositions[i];
            if(str[x] != ' '){
                return false;
            }
        }
    }
    return true;
}
void Ship::print(){
    std::cout << name << ": ";
    for(std::string str : position){
        std::cout << str << ", ";
    }
    std::cout << "\n";
}
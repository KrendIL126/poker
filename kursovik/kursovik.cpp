#include <iostream>
#include <time.h>
#include <vector>
#include "Deck.h"
#include "Player.h"
#include "Table.h"
#include "Dealer.h"

int main() {
    srand((unsigned)time(NULL));
    Table t;
    Player np = Player();
    for (int i = 0; i < 8; i++)
        t.addPlayer(&np, i);
    int k = 0;
    std::string playerName;
    std::vector<Player> players;
    std::cout << "Enter amount of players (1<=n<=8): " << std::endl;
    std::cin >> k;
    for (int i = 0; i < k; i++) {
        std::printf("Player #%d,\nEnter your name: ", i);
        std::cin >> playerName;
        players.push_back(Player(playerName, 100));
    }
    for (int i = 0; i < players.size(); i++)
        t.addPlayer(&players[i], i);

    Dealer d(&t);
    
    while (k > 1) {
        d.goPreflop();
        d.goFlop();
        d.goTurn();
        d.goRiver();
        std::cout << std::endl << std::endl;


        d.getTable()->printTable();
        d.showdown();
        for (int i = 0; i < 8; i++)
            if (d.getTable()->getPlayer(i)->getName() != "0") 
                if (d.getTable()->getPlayer(i)->getCash() < 10) {
                    d.getTable()->addPlayer(&np, i);
                    k--;
                }
        d.getTable()->moveBtn();
        for (int i = 0; i < 5; i++)
            d.getTable()->setBoard(Card(), i);
    }
    for (int i = 0; i < 8; i++)
        if (d.getTable()->getPlayer(i)->getName() != "0") {
            std::cout << "WINNER: " << d.getTable()->getPlayer(i)->getName();
            std::cout << " - " << d.getTable()->getPlayer(i)->getCash() << std::endl;
        }
    return 0;
}
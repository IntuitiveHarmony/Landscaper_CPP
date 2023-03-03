#include <iostream>
#include <string>
#include <vector>


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Tool class to provide tools for the player to acquire and use throughout the game
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Tool {
    public:
        Tool(std::string n, int c, int p) {
            name = n;
            cost = c;
            profit = p;
        }
    // private:
        std::string name;
        int cost;
        int profit;
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Landscaper class defines the player and many of it's member functions form the game itself
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Landscaper {
    public:
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Construct and initialize Landscaper
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Landscaper(std::string n, int f, std::vector<Tool> tB, Tool cT, bool e) : 
            name(n), 
            funds(f), 
            toolBox(tB), 
            currentTool(cT),
            exit(e)
            {}

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Get Input from the user for their name
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void ChangeName() {
            std::cout << "Welcome to Landscaper!\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            std::cout << "Go to work in order to gain funds. Upgrade tools to maximize profit.\nThe game is won when the player acquires the higest upgrade to their tool box and $500 funds\n\n";
            std::cout << "What is your name? ";
            std::cin >> name;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        }
    
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Increase player funds according to the profit of their current tool in use
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void GoToWork() {
            funds += currentTool.profit;
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Buy tool from the store.  It checks the player's funds and will put the tool in the players toolbox if they have enough $$$.  If not it wil give them a message with the difference so they know how much to save.
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void BuyTool(Tool newTool) {
            if(funds >= newTool.cost) {
                toolBox.push_back(newTool);
                funds -= newTool.cost;
                currentTool = newTool;
                // for(int i = 0; i < store.size(); i++) {
                //     if(currentTool.name == store.at(i)) {
                //         store.erase(store.begin() + store.at(i))
                //     }
                // }
            } 
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Prints Store to the console and gives user ability to purchase tools
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void GoToStore(std::vector<Tool> store) {
            std::cout << "\nWelcome to the store!\n\nWhat would you like to purchase?\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
            for(int i = 0; i < store.size(); i++) {
                std::cout << i + 1 << ". " << store[i].name << " Cost: $" << store[i].cost << " Profit: $" << store[i].profit << std::endl;
            }
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // Store choice input from user
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            std::string choice;

            std::cout << "E. EXIT STORE\n\n";
            std::cout << "Please make a selection.\n" << std::endl;
            std::cin >> choice;
            if(choice == "1" || choice == "2" || choice == "3") {
                Tool newTool = store.at(stoi(choice) - 1);
                if(funds >= store.at(stoi(choice) - 1).cost) {
                    // std::cout << newTool.cost; 
                    BuyTool(store.at(stoi(choice) - 1));
                    store.erase((store.begin())
                        // + stoi(choice) - 1
                        );
                } else {
                std::cout << "You are short $" << newTool.cost - funds << std::endl;
            }
                
                // store.erase(store.begin());
            } else if (choice == "e" || choice == "E") { 
                
            } else {
                std::cout << std::endl << choice << " is not a valid option\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
            }
        }

        void ExitGame() {
            std::cout << "\nThank you for playing Landscaper, " << name << "!\n";
            std::cout<< "Here are your final stats:\n\tFunds: $" << funds << "\n\tTool in use: " << currentTool.name << std::endl;  
            exit = true;
        }
    
    
    // ~~~~~~~~~~~~~~~~~
    // Player Attributes
    // ~~~~~~~~~~~~~~~~~
    // private:
        std::string name;
        int funds;
        std::vector<Tool> toolBox;
        Tool currentTool;
        bool exit;
};


int main() {
    // ~~~~~~~~~~~~~~~~~~~~~
    // Instansiate each tool
    // ~~~~~~~~~~~~~~~~~~~~~
    Tool hands("Bare Hands", 0, 1);
    Tool scissors("Scissors", 5, 5);
    Tool lawnMower("Lawn Mower", 25, 25);
    Tool ridingLawnMower("Riding Lawn Mower", 150, 50);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Store of tools for player to buy from
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::vector<Tool> store = {scissors, lawnMower, ridingLawnMower};
    
    
    // ~~~~~~~~~~~~~~~~~~~~~~
    // Instansiate the player
    // ~~~~~~~~~~~~~~~~~~~~~~
    Landscaper player("Name", 0, {}, hands, false); 

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Ask player name to start the game
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    player.ChangeName();


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Set conditions to win game
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~
    while((player.funds <= 500 || player.currentTool.name != "Riding Lawn Mower") && !player.exit) {
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Daily Choice Allow player to choose to go to work, shop for tools or quit game.
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        std::string dailyChoice;
        std::cout << "\nGood morning " << player.name << "! You have $" << player.funds << std::endl;
        std::cout << "You are using your " << player.currentTool.name << " for a profit of $" << player.currentTool.profit << std::endl;
        std::cout << "\nWhat would you like to do?\nPlease type a number and press enter:\n\t1. Go to work\n\t2. Go to the store\n\tQ. EXIT GAME\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Daily choice input from user
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        std::cin >> dailyChoice;
        if(dailyChoice == "1") {
            player.GoToWork();
        } else if(dailyChoice == "2") {
            player.GoToStore(store);
        } else if(dailyChoice == "q" || dailyChoice == "Q") {
            player.ExitGame();
        } else {
            std::cout << std::endl << dailyChoice << " is not a valid option\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        }
        
    }
    // ~~~~~~~~~~~~~~~~~~~~~~~~~
    // Winning message upon exit
    // ~~~~~~~~~~~~~~~~~~~~~~~~~
    if(player.funds >= 500) {
        std::cout << "\nCongragulations, you have won!" << std::endl;
    }
    
    player.ExitGame();
    
    
    return 0;
}
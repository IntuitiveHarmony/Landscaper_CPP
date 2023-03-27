#include <iostream>
#include <string>
#include <vector>


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Tool class to provide tools for the player to acquire and use throughout the game
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Tool {
    public:
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Construct and initialize Tool
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Tool(std::string n, int c, int p) : 
            name(n),
            cost(c),
            profit(p)
            {}
        // ~~~~~~~~~~~~~
        // Tool Getters
        // ~~~~~~~~~~~~~
        std::string GetName() {
            return name;
        }
        int GetCost() {
            return cost;
        }
        int GetProfit() {
            return profit;
        }
    private:
        std::string name;
        int cost;
        int profit;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Store class to house the tools
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Store {
    public:
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Construct and initialize Store
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Store(std::vector<Tool> t) : 
            shelf(t)
            {}
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Remove tool from shelf upon purchase
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void SellTool(int index) {
            shelf.erase(shelf.begin() + index);
        }
        std::vector<Tool> shelf;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Landscaper class defines the player and many of it's member functions form the game
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Describe the game and get Input from the user for their name
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void ChangeName() {
            std::cout << "Welcome to Landscaper!\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            std::cout << "\tIn order to obtain funds, go to work. \n\tMaximize profit by upgrading your tools from the store.\n\n\tYou win the game once: \n\t\tYou have $500 in funds and\n\t\tHave acquired the highest tool upgrade.\n\n";
            std::cout << "What is your name? ";
            std::cin >> name;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        }
    
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Increase player funds according to the profit of their current tool in use
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void GoToWork() {
            funds += currentTool.GetProfit();
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Buy tool from the store.  
        // It checks the player's funds and will put the tool in the players toolbox if they have enough $$$.  
        // If not it wil give them a message with the difference so they know how much to save.
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void BuyTool(Tool newTool) {
            if(funds >= newTool.GetCost()) {
                toolBox.push_back(newTool);
                funds -= newTool.GetCost();
                currentTool = newTool;
            } 
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Prints Store to the console and gives user ability to purchase tools
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void GoToStore(Store* store) {
            std::cout << "\nWelcome to the store!\n\nWhat would you like to purchase?\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
            for(int i = 0; i < store->shelf.size(); i++) {
                std::cout << i + 1 << ". " << store->shelf[i].GetName() << " -- Cost: $" << store->shelf[i].GetCost() << " Profit: $" << store->shelf[i].GetProfit() << std::endl;
            }
            std::cout << "E. EXIT STORE\n\n";
            std::cout << "Please make a selection.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
            
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // Tool purchase input from user
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            std::string choice;
            std::cin >> choice;
            if(choice == "1" || choice == "2" || choice == "3") {
                Tool newTool = store->shelf.at(stoi(choice) - 1);
                if(GetFunds() >= store->shelf.at(stoi(choice) - 1).GetCost()) {
                    BuyTool(store->shelf.at(stoi(choice) - 1));
                    store->SellTool((stoi(choice) - 1));
                } else {
                    std::cout << "\nYou are short $" << newTool.GetCost() - GetFunds() << " for the " << newTool.GetName() << std::endl;
                }
            } else if (choice == "e" || choice == "E") { 
                // Exit store 
            } else {
                std::cout << std::endl << choice << " is not a valid option\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
            }
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Allow user to exit game from main menu
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void ExitGame() {
            std::cout << "\nThank you for playing Landscaper, " << name << "!\n";
            std::cout<< "Here are your final stats:\n\tFunds: $" << funds << "\n\tTool in use: " << currentTool.GetName() << std::endl;  
            exit = true;
        }
        // ~~~~~~~~~~~~~~~~~~~
        // Landscaper Getters
        // ~~~~~~~~~~~~~~~~~~~
        std::string GetName() {
            return name;
        }
        int GetFunds() {
            return funds;
        }
        std::vector<Tool> GetToolBox() {
            return toolBox;
        }
        Tool GetCurrentTool() {
            return currentTool;
        }
        bool GetExit() {
            return exit;
        }
    // ~~~~~~~~~~~~~~~~~
    // Player Attributes
    // ~~~~~~~~~~~~~~~~~
    private:
        std::string name;
        int funds;
        std::vector<Tool> toolBox;
        Tool currentTool;
        bool exit;
};


int main() {
    // ~~~~~~~~~~~~~~~~~~~~~
    // Instantiate each tool
    // ~~~~~~~~~~~~~~~~~~~~~
    Tool hands("Bare Hands", 0, 1);
    Tool scissors("Scissors", 5, 5);
    Tool lawnMower("Lawn Mower", 25, 25);
    Tool ridingLawnMower("Riding Lawn Mower", 150, 50);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Instantiate the store of tools for player to buy from
    // Make pointer to the store to load into the GoToStore Function
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Store store({scissors, lawnMower, ridingLawnMower});
    Store* storePtr = &store;
    
    // ~~~~~~~~~~~~~~~~~~~~~~
    // Instantiate the player
    // ~~~~~~~~~~~~~~~~~~~~~~
    Landscaper player("Name", 0, {}, hands, false); 

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Ask player name to start the game
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    player.ChangeName();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Set conditions to win game
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~
    while((player.GetFunds() <= 500 || player.GetCurrentTool().GetName() != "Riding Lawn Mower") && !player.GetExit()) {
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Daily Choice Allow player to choose to go to work, shop for tools or quit game.
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        std::string dailyChoice;
        std::cout << "\nGood morning " << player.GetName() << "! You have $" << player.GetFunds() << std::endl;
        std::cout << "You are using your " << player.GetCurrentTool().GetName() << " for a profit of $" << player.GetCurrentTool().GetProfit() << std::endl;
        std::cout << "\nWhat would you like to do?\nPlease type a number and press enter:\n\t1. Go to work\n\t2. Go to the store\n\tQ. QUIT GAME\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Daily choice input from user
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        std::cin >> dailyChoice;
        if(dailyChoice == "1") {
            player.GoToWork();
        } else if(dailyChoice == "2") {
            player.GoToStore(storePtr);
        } else if(dailyChoice == "q" || dailyChoice == "Q") {
            player.ExitGame();
        } else {
            std::cout << std::endl << dailyChoice << " is not a valid option\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
        }
        
    }
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~
    // Winning message upon exit
    // ~~~~~~~~~~~~~~~~~~~~~~~~~
    if(player.GetFunds() >= 500) {
        std::cout << "\nCongragulations, you have won!" << std::endl;
    }
    
    player.ExitGame();
    
    return 0;
}
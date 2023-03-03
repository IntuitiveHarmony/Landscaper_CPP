# Landscaper C++

I will build this simple game to help solidify my understanding of some of the fundamental concepts when learning a new programming language.

<hr />
<br />

Play this game in the console at [Replit](https://replit.com/@IntuitiveHarmon/LandscaperCPP?v=1 "Landscaper_CPP Replit") 

Check out the code at [gitHub](https://github.com/IntuitiveHarmony/Landscaper_CPP "Landscaper_CPP gitHub") 

<br />

## Finally!!

I have been waiting so long to put this together in C++

This is actually my third attempt at creating this game. I have previously built a few crude versions while learning JavaScipt and Python. I also utilized it as a means of familiarizing myself with the `useState()` hook in React.

Throughout this project, I consistently encountered the challenge of realizing the importance of patience. I tend to be impulsive and struggle with concentrating on fundamental concepts. My ultimate goal with C++ is to develop plugins for Digital Audio Workstations or standalone software based musical instruments. Consequently, while I know it is important, I often find it difficult to focus on tasks such as deleting a specific index from a vector because I am eager for my skillset to match my aspirations.

<br />

## Dynamic Choice

One sucess I had in this project was making it so the user could still use the numbers to choose tools to purchase even as previous purchases were being deleted from the vector.  This will cause an `out of range` error however if the user selects `3` if a tool has already been purchased

``` c++
if(choice == "1" || choice == "2" || choice == "3") {
    Tool newTool = store->shelf.at(stoi(choice) - 1);
    if(funds >= store->shelf.at(stoi(choice) - 1).cost) {
        BuyTool(store->shelf.at(stoi(choice) - 1));
        store->SellTool((stoi(choice) - 1));
    } else {
        std::cout << "\nYou are short $" << newTool.cost - funds << " for the " << newTool.name << std::endl;
    }
} else if (choice == "e" || choice == "E") { 
    // Exit store 
} else {
    std::cout << std::endl << choice << " is not a valid option\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}
```
<br />

## .erase()

I had such a struggle getting a particular index to erase from the `shelf` vector within the `Store`.  The solution was to pass the store in as a pointer to the `GoToStore()` function and put a member function of `SellTool()` within.  Originally I had the store as a vector of tools.  I suppose I could have just passed in this vector as a pointer but once I had already made the `Store` class I didn't want to go back.  Besides, having a member function for the store is pretty convienient. Seeing the index within the vector removed once it was sold was a very satisfying feeling!

<br />

## Looking Forward

I would like to revisit this particular game soon and see if I can work out the potential `out of range` bug and also write in a condition that checks to see if the tool shelf in the store is empty before printing out the store.  If it is empty it will give the user a message indicating as much.

## I hope you enjoy playing this version of C++ Landcaper!

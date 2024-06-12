#include <iostream>
#include <vector>
#include <string>
#include <cctype> // for std::tolower
#include<cmath> // for power
#include <cstdlib> // for system function
#include <chrono> // for std::chrono
#include <thread> // for std::this_thread::sleep_for

// class to creat a hash table that can insert and search word
class hashFunction{

    private:

        // this function is used to calculate the hashed value of a given word
        int hashLetter(std::string word){
           int index = word.size() - 1; // length of the letter starting from 0
           int hashValue = 0; // initialize varaible to store the hashed value
           
            // loop through every characters and caculate its value
            for(char character : word){
                int characterValue;
                // space is 0
                if(character == ' '){
                    characterValue = 0;
                }
                // character convert to 1-26
                else{
                    characterValue = std::tolower(character) - 'a' + 1; // a is regarded as 1
                }
                
                // calculate the hashed value of each letter
                hashValue = (characterValue * (int)(pow(27, index))) + hashValue;
                // change the power by 1 for every letter
                index--;
            };

            // mod the value so it will be between 1-200
            return hashValue % size;
        }

    // this constructer is called whenever a hash table is created  
    public:
        int size;
        std::vector<std::string> table;
        // size(size) initialize the int size with the same value as the parameter
        hashFunction(int size) : size(size){
            table.resize(size); // resize the hash table to fit user's input
        }

    // function to map word into the table
    int insert(std::string word){
        // call function to obtain key
        int key = hashLetter(word);
        // check if the slot is not occupied
        while(!table[key].empty()){
            key+=1;
        }
        // if there is an open slot, we add it 
        table[key] = word;
    
        return key;
    }

    // function to search for the user given word
    int search(std::string word){

        int key = hashLetter(word);

        // search for non empty slot
        while(!table[key].empty()){
            // if found word, we return where it was store
            if(table[key] == word){
                return key;
            }
            // if the loop reaches the end and still hasnt found it then we print not found
            else if((key + 1) == table.size()){
                std::cout << "Word not found!";
                return -1;
            }
            // increment key by 1
            key+=1;
        }
        // empty slot assume word is not inserted
        return -1;
    }
};

int main(){

    std::string userInput;
    hashFunction hashTable(200); // hash table with 200 slots

    // do while loop for repetiion
    do{ 
        system("cls"); // clear terminal
        std::cout << "\n\t\t   Hash_table\n\t\t---------------";
        std::cout << "\n\t\t(a) insert word\n\t\t(b) search word\n\t\t(c) exit\n\n\t\tEnter: ";
        std::getline(std::cin, userInput); // Read entire line of input
        system("cls");

        if(userInput == "a"){
            std::cout << "\n\t\tEnter word: ";
            std::getline(std::cin, userInput);
            std::cout << "\t\tWord store at key: " << hashTable.insert(userInput); // insert the word to a specific key
            // Delay for 2 second
            std::this_thread::sleep_for(std::chrono::seconds(2)); // delay the terminal for 2 second before clearing
        }
        else if(userInput == "b"){
            std::cout << "\n\t\tSearch: ";
            std::getline(std::cin, userInput);
            std::cout << "\t\tWord at key: " << hashTable.search(userInput); // search based on value 
            // Delay for 2 second
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        else{
           break; // if enter c or any word will break loop
        }
    }
    while(userInput != "c"); // run as long as user doesnt enter c

    return 0;
}
#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generate_combinations(string fixed, string floating, int pos, set<string>& combinations) {
    // std::cout << "This is the begining" << std::endl;
    // std::cout << "fixed " << fixed << std::endl;
    // std::cout << "floating " << floating << std::endl;
    // std::cout << "pos " << pos+1 << std::endl;
    if (pos == fixed.length()) {
        combinations.insert(fixed);
        return;
    }
    if (fixed[pos] != '-') {
        generate_combinations(fixed, floating, pos+1, combinations);
        return;
    }
    
    // check if length of floating == number of blanks
    int numBlanks = 0;
    for (int i = 0; i < fixed.length(); i++){
        if (fixed[i] == '-'){
            numBlanks++;
        }
    }

    // std::cout << floating.length() << " " << numBlanks << " " << fixed << std::endl;
    if (floating.length() == numBlanks){
        //  std::cout << "inside this loop " << std::endl;
        //check all the floating chars in each of the blanks
        for (int i = 0; i < floating.length(); i++) {
            char c = floating[i];
            fixed[pos] = floating[i];
            // std::cout << "floating before " << floating << std::endl;
            floating.erase(i, 1);
            
            // std::cout << "Inside loop" << std::endl;
            // std::cout << "fixed " << fixed << std::endl;
            // std::cout << "floating after delete " << floating << std::endl;
            // std::cout << "pos " << pos+1 << std::endl;
            generate_combinations(fixed, floating, pos+1, combinations);
            floating.push_back(c);
            // std::cout << "floating after add back " << floating << std::endl;
        }
    }
    else {
        //check entire alphabet
        //if it exists in floating, delete the letter from floating
        for (char c = 'a'; c <= 'z'; c++) {
            for (int i = 0; i < floating.length(); i++){
                if (floating[i] == c){
                    floating.erase(i,1);
                    fixed[pos] = c;
                    generate_combinations(fixed, floating, pos+1, combinations);
                    floating.push_back(c);
                }
            }
                fixed[pos] = c;
                generate_combinations(fixed, floating, pos+1, combinations);
            }
    }
 }

bool is_valid_word(const string& word, const set<string>& dict) {
    return dict.find(word) != dict.end();
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    
// Initialize the set of all possible words to an empty set
    std::set<std::string> words;
    //std::cout<< "one " << std::endl;
    // Check if the input string has any empty slots
    size_t pos = in.find('-');
    if (pos == std::string::npos) {
        // If there are no empty slots, check if the input string is a valid word
        if (is_valid_word(in, dict)) {
            words.insert(in);
        }
        return words;
    }
    std::cout << "in words " << in << std::endl;
    std::cout << "floating letters " << floating << std::endl;
    
    // Generate all possible combinations of characters in the remaining empty slots
    std::set<std::string> combinations;
    //std::cout<< "two " << std::endl;
    generate_combinations(in, floating, 0, combinations);
    //std::cout<< "three " << std::endl;
    // Check if each combination is a valid English word and add it to the set of possible words
    std::set<std::string>::iterator it;
    for (it = combinations.begin(); it != combinations.end(); ++it) {
        if (is_valid_word(*it, dict)) {
            words.insert(*it);
        }
    }
   // std::cout<< "four " << std::endl;
    
    return words;
}

// Define any helper functions here

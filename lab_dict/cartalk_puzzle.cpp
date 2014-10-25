/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>


#include "cartalk_puzzle.h"
#include "common_words.h"



using namespace std;



/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of 
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector< StringTriple > cartalk_puzzle(PronounceDict d,
                                      const string& word_list_fname)
{
    /* Your code goes here! */
    vector<StringTriple> result;
    

    ifstream words(word_list_fname);
    string word1, word2, word3;

    if(words.is_open()) {
        while(getline(words, word1)){
        	if(word1.length() > 1){
        		
        		word3 = word1.substr(0,1) + word1.substr(2, word1.length()); 
        		word2 = word1.substr(1, word1.length());
        		
        		//std::cout << word2 << "," << word3 << std::endl;
        		
        		if(d.homophones(word1, word3) && d.homophones(word1, word2)){
        	 		StringTriple temp = std::make_tuple(word1, word2, word3);
        			result.push_back(temp);
        		}
        	
        	}
        
        }
    }
    
    
   
    
    return result;
}



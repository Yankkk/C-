/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    
    ifstream words(filename);
    string word;
    string sorts;
    

    if(words.is_open()) {
        while(getline(words, word)){
        	sorts = word;
        	std::sort(sorts.begin(), sorts.end());
        	if(dict.count(sorts) <= 0){
        		dict.insert(std::pair<string, vector<string>>(sorts, {word}));
        	}
        	else{
        		dict.find(sorts)->second.push_back(word);
        	}
          }
        }
   
}

/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
    /* Your code goes here! */
    
    for(auto it = words.begin(); it != words.end(); it ++){
    	string temp = *it;
    	string sorts = temp;
    	std::sort(sorts.begin(), sorts.end());
    	if(dict.count(sorts) <= 0 ){
    		dict.insert(std::pair<string, vector<string>>(sorts, {temp}));
    	}
    	else{
    		dict.find(sorts)->second.push_back(temp);
    	}
    	
    
    }
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string sorts = word;
    std::sort(sorts.begin(), sorts.end());
 	auto f = dict.find(sorts);
 	if(f != dict.end())
 		return dict.find(sorts)->second;
 	else
 		return vector<string>();
}       

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector< vector < string > >  result;
    for(auto it = dict.begin(); it != dict.end(); it++){
    	auto temp = it->second;
    	if(temp.size() > 1){
    		result.push_back(it->second);
    	}
    }
    
    
    return result;
}



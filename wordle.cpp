// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle_add_if_exists(
    const std::string& word,
    const std::set<std::string>& dict, 
    std::set<std::string>& res);

void wordleHelper(
    const std::string& in,
    const std::string pool,
    const std::set<std::string>& dict,
    int unknown_pos_count,
    int curr_pos,
    std::string word,
    std::set<std::string>& res);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    int unknown_pos_count = 0;
    for(size_t i = 0; i < in.size(); i++){
        if(in[i] == '-')
            unknown_pos_count++;
    }
    std::set<std::string> res;
    wordleHelper(in, floating, dict, unknown_pos_count, 0, in, res);
    return res;

}

// Define any helper functions here

void wordle_add_if_exists(
    const std::string& word,
    const std::set<std::string>& dict, std::set<std::string>& res)
{
    std::set<std::string>::iterator itr = dict.find(word);
    if(itr != dict.end()){
        res.insert(*itr);
    }
}

void wordleHelper(
    const std::string& in,
    const std::string pool,
    const std::set<std::string>& dict,
    int unknown_pos_count,
    int curr_pos,
    std::string word,
    std::set<std::string>& res)
{
    if(unknown_pos_count == 0){
        wordle_add_if_exists(word, dict, res);
        return;
    }
    if(in[curr_pos] != '-'){
        word[curr_pos] = in[curr_pos];
        curr_pos++;
        wordleHelper(in, pool, dict, unknown_pos_count, curr_pos, word, res);
        return;
    }
    if(unknown_pos_count <= (int)pool.size()){
        for(size_t i = 0; i < pool.size(); i++){
            string tempWord = word;
            tempWord[curr_pos] = pool[i];
            string tempPool = pool.substr(0,i) + pool.substr(i+1);
            wordleHelper(in, tempPool, dict, unknown_pos_count-1, curr_pos+1, tempWord, res);
        }
        return;
    }
    for(char x = 'a'; x <= 'z'; x++){
        string tempWord = word;
        tempWord[curr_pos] = x;
        size_t tempPos = pool.find(x);
        string tempPool;
        if((int)tempPos != -1){
            tempPool = pool.substr(0,tempPos) + pool.substr(tempPos+1);
        } else {
            tempPool = pool;
        }
        wordleHelper(in, tempPool, dict, unknown_pos_count-1, curr_pos+1, tempWord, res);
    }
}
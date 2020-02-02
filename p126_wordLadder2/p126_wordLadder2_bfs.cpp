#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <deque>

using namespace::std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        // Use BFS to find the endWord; meanwhile build a map to hold all possible paths (ladders)

        vector<vector<string>> ladders;
        
        // to keep the current word path (ladder)
        vector<string> ladder; 
        
        // Use set (hashtable) to hold the dictionary's words. As the average time complexity 
        // of read is O(1), it speeds up the searching compared to the vector (array).
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        // A map (hashtable) to hold all possible paths (ladder) in reverse order (from endWord to startWord).
        // The hash key is the child word, and the value is its parents (could have serveral parents).
        // For example, the word "cog" in the "Example 1" has two parents which are "dog" and "log".
        unordered_map<string, unordered_set<string>> parents; 
        
        deque<string> toVisit{beginWord};
        
        while (!toVisit.empty()) {
            // Remove from wordSet the words which has already been visited.
            // It not only speeds up the searching, but also saves us from using "visited" 
            // hashtable to handle duplications.
            for (auto &word : toVisit) wordSet.erase(word);
            
            int numOfWordsInCurrLevel = toVisit.size();
            while (numOfWordsInCurrLevel-- > 0) {
                auto word = toVisit.front();
                if (word == endWord) {
                    calculateLadder(word, parents, ladder, ladders);
                    return ladders;
                }
                
                toVisit.pop_front();             
                calculateWordsToVisit(word, wordSet, parents, toVisit);
            }
        }
        
        return ladders;
    }
    
private:
    void calculateLadder(const string &endWord, unordered_map<string, unordered_set<string>> &parents,  
                         vector<string> &currLadder, vector<vector<string>> &ladders) {
        // Use DFS to build the word path (ladder)
        
        currLadder.push_back(endWord);
        if (parents.find(endWord) == parents.end()){
            // The currLadder is in the reverse order (from endWord to beginWord), so
            // we need to reverse it when saving to the final result.
            ladders.push_back(vector<string>(currLadder.rbegin(), currLadder.rend()));
            return;
        }
        
        for (auto &word : parents[endWord]) {
            calculateLadder(word, parents, currLadder, ladders);
            currLadder.pop_back();
        }
    }
       
    void calculateWordsToVisit(const string &parentWord, unordered_set<string> &wordSet, 
                               unordered_map<string, unordered_set<string>> &parents, 
                               deque<string> &toVisit) {
        auto word = parentWord;
        for (int i = 0; i < word.size(); ++i) {
            auto ch = word[i];
            for (int j = 0; j < 26; ++j) {
                word[i] = 'a' + j;
                if (wordSet.find(word) != wordSet.end()) {
                    if (parents.find(word) == parents.end()) {
                        toVisit.push_back(word); // ensure the word appears in queue only once
                        parents[word] = unordered_set<string>();
                    }
                    parents[word].insert(parentWord);
                }
            }
            word[i] = ch;
        }
    }
};
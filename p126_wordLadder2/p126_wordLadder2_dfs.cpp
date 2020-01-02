#include <vector>
#include <string>
#include <unordered_set>

using namespace::std;

// Note Leetcode does not accept this DFS solution. It throws "Time Limit Exceeded" error.
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> shortestPaths;
        unordered_set<string> visited; // to indicate if a word has been processed
        vector<string> currentPath; // to hold the current word path (ladder)
        
        findLaddersDfs(beginWord, endWord, wordList, visited, currentPath, shortestPaths);
        
        return shortestPaths;
    }
    
private:
    void findLaddersDfs(const string &beginWord, const string &endWord, 
            const vector<string> &wordList, unordered_set<string> &visited, 
            vector<string> &currentPath, vector<vector<string>> &shortestPaths) {         
        currentPath.push_back(beginWord);
        if (beginWord == endWord) {
            // Clear all the ladders found before which have a longer length.
            if (!shortestPaths.empty() && currentPath.size() < shortestPaths[0].size()) {
                shortestPaths.clear();
            }
            shortestPaths.push_back(currentPath);
            return;
        }
        
        for (auto &word : wordList) {
            // Stop searching if the current ladder is longer than ladders found before.
            if (!shortestPaths.empty() && currentPath.size() >= shortestPaths[0].size()) break;
            
            if (visited.find(word) == visited.end() && areWordsTransformed(beginWord, word)) {
                visited.insert(word);
                findLaddersDfs(word, endWord, wordList, visited, currentPath, shortestPaths);
                currentPath.pop_back();
                visited.erase(word);
            }
        }
    }
    
    bool areWordsTransformed(const string &fromWord, const string &toWord) {
        // All words have the same length.       
        int diff = 0;
        for (int i = 0; i < fromWord.size(); ++i) {
            if (fromWord[i] != toWord[i]) {
                if (++diff > 1) return false;
            }
        }
        
        return diff == 1;
    }
};
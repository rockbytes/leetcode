#include <vector>
#include <string>
#include <unordered_set>
#include <deque>

using namespace::std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {      
        // Use set (hashtable) to hold the dictionary's words. As the average time complexity 
        // of read is O(1), it speeds up the searching compared to the vector (array).
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        
        // We keep the paths/ladders (instead of single word) in the queue. Once we 
        // find the endWord, the related paths in the queue are the answer. It saves
        // us from building ladders separately.
        deque<vector<string>> toVisit{{beginWord}}; 
        
        vector<vector<string>> answer;
        bool foundEndWord = false;
        
        while (!toVisit.empty()) {
            // Remove from wordSet the words which has already been visited.
            // It not only speeds up the searching, but also saves us from using "visited" 
            // hashtable to handle duplications.
            for (auto &path : toVisit) wordSet.erase(path.back());
            
            int cnt = toVisit.size();
            while (cnt-- > 0) {
                auto currPath = toVisit.front(); toVisit.pop_front();
                if (currPath.back() == endWord) {
                    answer.push_back(currPath);
                    foundEndWord = true;
                }
                
                if (!foundEndWord) calculateWordsToVisit(currPath, wordSet, toVisit);
            }
        }
        
        return answer;  
    }

private:
    void calculateWordsToVisit(const vector<string> &currPath, 
                               const unordered_set<string> &wordSet, 
                               deque<vector<string>> &toVisit) {
        auto word = currPath.back();
        for (int i = 0; i < word.size(); ++i) {
            auto tmp = word[i];
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                word[i] = ch;
                if (wordSet.find(word) != wordSet.end()) {
                    toVisit.push_back(currPath);
                    toVisit.back().push_back(word);
                }
            }
            word[i] = tmp;
        }
    }
};
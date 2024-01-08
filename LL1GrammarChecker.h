//
// Created by 左媛 on 2024/1/8.
//

#ifndef LL1GRAMMARCHECKER_H
#define LL1GRAMMARCHECKER_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
using namespace std;

class LL1GrammarChecker {
private:
    unordered_map<string, unordered_set<string>> firstSets;
    unordered_map<string, unordered_set<string>> followSets;

public:
    LL1GrammarChecker(unordered_map<string, unordered_set<string>>& first,
                      unordered_map<string, unordered_set<string>>& follow);

    bool isLL1Grammar(unordered_map<string, vector<vector<string>>>& grammar);

private:
    bool checkDistinctFirstSets(const vector<vector<string>>& productions);
    bool checkNullableIntersection(const string& nonTerminal, const vector<vector<string>>& productions);
    std::unordered_set<std::string> computeFirstSet(const std::vector<string>& symbols);
    bool isNullable(const vector<string>& symbols);
};

#endif  // LL1GRAMMARCHECKER_H
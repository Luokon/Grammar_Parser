//
// Created by 左媛 on 2024/1/8.
//

#include "LL1GrammarChecker.h"
#include <iostream>

LL1GrammarChecker::LL1GrammarChecker(unordered_map<string, unordered_set<string>>& first,
                                     unordered_map<string, unordered_set<string>>& follow)
        : firstSets(first), followSets(follow) {}

bool LL1GrammarChecker::isLL1Grammar(std::unordered_map<string, vector<vector<string>>>& grammar) {
    for (const auto& [nonTerminal, productions] : grammar) {
        if (!checkDistinctFirstSets(productions)) {
            cout << "产生式的右部FIRST集合相交： " << nonTerminal << endl;
            return false;
        }

        if (!checkNullableIntersection(nonTerminal, productions)) {
            cout << "产生式的右部FIRST集合与FOLLOW集合相交： " << nonTerminal << endl;
            return false;
        }
    }

    return true;
}

bool LL1GrammarChecker::checkDistinctFirstSets(const vector<vector<string>>& productions) {
    unordered_set<string> firstSetUnion;
    for (const auto& production : productions) {
        unordered_set<string> firstSet = computeFirstSet(production);
        for (const auto& symbol : firstSet) {
            if (firstSetUnion.count(symbol) > 0) {
                return false;  // FIRST集合相交
            }
        }
        firstSetUnion.insert(firstSet.begin(), firstSet.end());
    }
    return true;
}

bool LL1GrammarChecker::checkNullableIntersection(const string& nonTerminal, const vector<vector<string>>& productions) {
    unordered_set<string> nullableSet;
    for (const auto& production : productions) {
        if (isNullable(production)) {
            nullableSet.insert(followSets[nonTerminal].begin(), followSets[nonTerminal].end());
        }
    }

    unordered_set<string> firstSetUnion;
    for (const auto& production : productions) {
        unordered_set<string> firstSet = computeFirstSet(production);
        for (const auto& symbol : firstSet) {
            if (nullableSet.count(symbol) > 0) {
                return false;  // FIRST集合与FOLLOW集合相交
            }
        }
        firstSetUnion.insert(firstSet.begin(), firstSet.end());
    }
    return true;
}

unordered_set<string> LL1GrammarChecker::computeFirstSet(const vector<string>& symbols) {
    unordered_set<string> firstSet;
    for (const auto& symbol : symbols) {
        if (firstSets.find(symbol) != firstSets.end()) {
            firstSet.insert(firstSets[symbol].begin(), firstSets[symbol].end());
            if (!isNullable(symbols)) {
                break;
            }
        } else {
            firstSet.insert(symbol);
            break;
        }
    }
    return firstSet;
}

bool LL1GrammarChecker::isNullable(const vector<string>& symbols) {
    for (const auto& symbol : symbols) {
        if (firstSets.find(symbol) != firstSets.end() && firstSets[symbol].count("ε")) {
            return true;
        }
    }
    return false;
}

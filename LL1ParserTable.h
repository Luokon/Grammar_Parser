//
// Created by 左媛 on 2024/1/8.
//

#ifndef LL1_PARSER_TABLE_H
#define LL1_PARSER_TABLE_H

#include <unordered_map>
#include <map>
#include <vector>
#include <string>

using namespace std;

class LL1ParserTable {
public:
    LL1ParserTable();

    void addEntry(const string& nonTerminal, const string& terminal, const vector<string>& production);
    vector<string> getProduction(const string& nonTerminal, const string& terminal);
    bool hasEntry(const string& nonTerminal, const string& terminal);

private:
    unordered_map<string, map<string, vector<string>>> table;
};

#endif // LL1_PARSER_TABLE_H

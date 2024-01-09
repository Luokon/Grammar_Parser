//
// Created by 左媛 on 2024/1/8.
//

#ifndef LL1_PARSER_TABLE_H
#define LL1_PARSER_TABLE_H
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <iomanip>
#include <set>
using namespace std;

class LL1ParserTable {
public:
    static void getParserTable(unordered_map<string, unordered_map<string, vector<string>>> &parserTable,
                        const unordered_map<string, vector<vector<string>>> &G,
                        const unordered_map<string, unordered_set<string>> &firstSets,
                        const unordered_map<string, unordered_set<string>> &followSets,
                        unordered_map<string, unordered_map<string, vector<string>>> &firstMap);

    static void printParserTable(const unordered_map<string, unordered_map<string, vector<string>>> &parserTable);
};

#endif // LL1_PARSER_TABLE_H

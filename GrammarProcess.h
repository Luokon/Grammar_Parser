//
// Created by 左媛 on 2024/1/6.
//

#ifndef GRAMMAR_PARSER_GRAMMARPROCESS_H
#define GRAMMAR_PARSER_GRAMMARPROCESS_H
#include <bits/stdc++.h>
using namespace std;

class GrammarProcess {
public:
    static void display(const unordered_map<string, vector<vector<string>>>& G);
    static void directLeftRecursion(unordered_map<string, vector<vector<string> > >& G); // 消除直接左递归
    static bool hasIndirectRecursion(const string &nonTerminal, const vector<vector<string>> &productions,
                                     unordered_map<string, vector<vector<string>>> &G, unordered_set<string> &visited); // 判断是否存在间接左递归
    static void eliminateIndirectRecursion(unordered_map<string, vector<vector<string> > > &G); // 消除间接左递归

    static void calculateFirstSet(unordered_map<string, vector<vector<string>>> &G,
                                  unordered_map<string, unordered_set<string>> &firstSets,
                                  unordered_map<string, unordered_map<string, vector<string> > > &firstMap);

    static void calculateFirstSetDFS(unordered_map<string, vector<vector<string>>> &G, const string &symbol,
                                     unordered_set<string> &firstSet, unordered_map<string, unordered_set<string>> &firstSets,
                                     unordered_map<string, unordered_map<string, vector<string>>> &firstMap);

    static void calculateFollowSet(unordered_map<string, vector<vector<string>>> &G,
                            unordered_map<string, unordered_set<string>> &firstSets,
                            unordered_map<string, unordered_set<string>> &followSets, const string &start);



};


#endif //GRAMMAR_PARSER_GRAMMARPROCESS_H

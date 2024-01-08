//
// Created by 左媛 on 2024/1/6.
//

#ifndef GRAMMAR_PARSER_GRAMMARPARSER_H
#define GRAMMAR_PARSER_GRAMMARPARSER_H
#include <bits/stdc++.h>
using namespace std;

class grammarParser {
public:
    static void display(const unordered_map<string, vector<vector<string>>>& G);
    static void directLeftRecursion(unordered_map<string, vector<vector<string> > >& G); // 消除直接左递归

    static void eliminateIndirectRecursion(unordered_map<string, vector<vector<string> > > &G); // 消除间接左递归
    static vector<string> indirectRecursionDFS(const string &father, string first, vector<string> &result,
                                               const unordered_map<string, vector<vector<string>>> &G, set<string> visit);

    static void simplifyGrammar(unordered_map<string, vector<vector<string> > >& G, string start);
    static void markReachableProductions(unordered_map<string, vector<vector<string> > > &G, const string &start,
                                         unordered_set<string> &reachable);

    static void calculateFirstSet(unordered_map<string, vector<vector<string>>> &G,
                                  unordered_map<string, unordered_set<string>> &firstSets);

    static void calculateFirstSetDFS(unordered_map<string, vector<vector<string>>> &G, const string &symbol,
                                     unordered_set<string> &firstSet, unordered_map<string, unordered_set<string>> &firstSets);

    static void calculateFollowSet(unordered_map<string, vector<vector<string>>> &G,
                            unordered_map<string, unordered_set<string>> &firstSets,
                            unordered_map<string, unordered_set<string>> &followSets, const string &start);
};


#endif //GRAMMAR_PARSER_GRAMMARPARSER_H

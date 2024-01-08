//
// Created by zy on 2024/1/6.
//

#ifndef GRAMMAR_PARSER_GRAMMARPARSER_H
#define GRAMMAR_PARSER_GRAMMARPARSER_H
#include <bits/stdc++.h>
using namespace std;

class grammarParser {
public:
    static void directLeftRecursion(unordered_map<string, vector<vector<string> > >& G, string start); // 消除直接左递归
    static void eliminateIndirectRecursion(unordered_map<string, vector<vector<string> > > &G); // 消除间接左递归
    static void simplifyGrammar(unordered_map<string, vector<vector<string> > >& G, string start);
    static void markReachableProductions(unordered_map<string, vector<vector<string> > > &G, const string &start,
                                         unordered_set<string> &reachable);

    static void calculateFirstSet(unordered_map<string, vector<string>> &G,
                                  unordered_map<string, unordered_set<string>> &firstSets);

    static void calculateFirstSetDFS(unordered_map<string, vector<vector<string>>> &G, const string &symbol,
                                 unordered_set<string> &firstSet);

    static void calculateFollowSet(unordered_map<string, vector<string>> &G,
                       unordered_map<string, unordered_set<string>> &firstSets,
                       unordered_map<string, unordered_set<string>> &followSets, const string &start);

    static void display(const unordered_map<string, vector<vector<string>>>& G);


    static bool
    hasIndirectRecursion(const string &start, vector<string> &production,
                         unordered_map<string, vector<vector<string>>> &G);

    static void convertToDirectRecursion(const string &nonTerminal, vector<string> &production,
                                  unordered_map<string, vector<vector<string>>> &G);


    static vector<string> indirectRecursionDFS(const string &father, string first, vector<string> &newProductions,
                                        const unordered_map<string, vector<vector<string>>> &G,
                                               set<string> visit);
};


#endif //GRAMMAR_PARSER_GRAMMARPARSER_H

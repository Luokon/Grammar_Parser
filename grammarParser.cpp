//
// Created by zy on 2024/1/6.
//

#include "grammarParser.h"

// 显示当前文法
void grammarParser::display(const unordered_map<string, vector<vector<string> > >& G)
{
    for (const auto& [nonterminal, productions] : G)
    {
        cout << nonterminal << "->";
        for (int i = 0; i < productions.size(); ++i)
        {
            const vector<string>& production = productions[i];
            for (int j = 0; j < production.size(); ++j)
            {
                cout << production[j] ;
            }
            if (i != productions.size() - 1)
            {
                cout << "|";
            }
        }
        cout << endl;
    }
}
// 间接左递归转换直接左递归
vector<string > grammarParser::indirectRecursionDFS(const string& father, string first, vector<string> & result,
                                                    const unordered_map<string, vector<vector<string>>>& G,
                                                    set<string> visit)
{
    if (first == father) {
        result.insert(result.begin(), father);
        return result;
    }

    if(!visit.count(first))
    {
        if (G.count(first)) {   // 非终结符
            vector<vector<string>> productions = G.at(first);

            for (auto production : productions) {
                if (G.count(production[0]) && ( !visit.count(production[0]) || (production[0] == father) ) ) {    // 确保非终结符
                    result.insert(result.begin(), production.begin() + 1 , production.end());
                    result = indirectRecursionDFS(father, production[0], result, G, visit);
                }
            }
            visit.insert(first);
        }
    }
    return result;
}

void grammarParser::eliminateIndirectRecursion(unordered_map<string, vector<vector<string>>>& G)
{
    unordered_map<string, vector<vector<string>>> newG(G);
    bool flag = false;
    for(auto& [father, productions] : G)
    {
        vector<vector<string>> newProductions;
        for(auto &production: productions)
        {
            string first = production[0];
            if(G.count(first) && first != father)
            {// 自上而下推导看是否有间接递归
                vector<string> result;  // 初始插入
                set<string> visit;
                visit.insert(father);
                result = indirectRecursionDFS(father, first, result, G, visit);

                if(result[0] == father)
                {
                    flag = true;
                    // 第一个产生式
                    vector<string> tail(production.begin() + 1, production.end()); //当前产生式的末尾
                    while (!result.empty())
                    {
                        vector<string> split(result.begin(), find(result.begin()+1, result.end(), father));
                        split.insert(split.end(), tail.begin(), tail.end());
                        newProductions.push_back(split);
                        result.erase(result.begin(), find(result.begin()+1, result.end(), father));
                    }
                }
                else newProductions.push_back(production);
            }
            else newProductions.push_back(production);
        }
        newG[father] = newProductions;
    }
    if(flag)
    {
        G = newG;
        cout << "\n消除间接左递归（将其转换为直接左递归）：\n";
        display(G);
    }
    else cout<<"该文法没有间接左递归\n";
}
//// 直接左递归消除处理
//void grammarParser::directLeftRecursion(unordered_map<string, vector<vector<string> > >& G, string start)
//{
//    bool flag = false;
//    unordered_map<string, vector<string>> newGrammar;
//
//    for (const auto& [nonTerminal, productions] : G) {
//        vector<string> nonRecursiveProductions;
//        vector<string> recursiveProductions;
//
//        for (const string& production : productions) {
//            if (production.substr(0, nonTerminal.size()) == nonTerminal) {
//                flag = true;
//                recursiveProductions.push_back(production.substr(nonTerminal.size()));
//            } else {
//                nonRecursiveProductions.push_back(production);
//            }
//        }
//
//        if (!recursiveProductions.empty()) {
//            string newNonTerminal = nonTerminal + "'";
//
//            for (const string& recursiveProduction : recursiveProductions) {
//                newGrammar[newNonTerminal].push_back(recursiveProduction + newNonTerminal);
//            }
//
//            for (const string& nonRecursiveProduction : nonRecursiveProductions) {
//                newGrammar[nonTerminal].push_back(nonRecursiveProduction + newNonTerminal);
//            }
//            newGrammar[newNonTerminal].push_back("ε");
//        } else {
//            for (const string& nonRecursiveProduction : nonRecursiveProductions) {
//                newGrammar[nonTerminal].push_back(nonRecursiveProduction);
//            }
//        }
//    }
//    if(flag) {
//        G = newGrammar;
//        cout<<"\n消除直接左递归：\n";
//        display(G);
//    } else {
//        cout<<"\n该文法没有直接左递归，继续处理\n";
//    }
//
//};
//
//// 使用深度优先搜索将能从开始符号到达的非终结符标记
//void grammarParser::markReachableProductions(unordered_map<string, vector<vector<string> > >& G, const string& start, unordered_set<string>& reachable) {
//    reachable.insert(start);
//
//    for (auto production : G[start]) {
//        for (int i = 0; i < production.size(); i++) {
//            if(!isupper(production[i])) continue;
//
//            string str;
//            str.push_back(production[i]);
//
//            if (i < production.size() - 1 && production[i + 1] == '\'') {
//                str.push_back('\'');
//                i++;
//            }
//
//            if (G.find(str) != G.end() && reachable.count(str) == 0) {
//                markReachableProductions(G, str, reachable);
//            }
//        }
//    }
//}
//void grammarParser::simplifyGrammar(unordered_map<string, vector<vector<string> > >& G, string start) {
//    // 移除不能与开始符号关联的表达式，即没被标记的非终结符与其表达式
//    unordered_set<string> reachable;
//    markReachableProductions(G, start, reachable);
//
//    for (auto it = G.begin(); it != G.end();) {
//        if (reachable.count(it->first) == 0) {
//            it = G.erase(it);
//        } else {
//            ++it;
//        }
//    }
//    cout<<"\n处理完成后的文法：\n";
//    display(G);
//}
//
//// 计算FIRST集合
//void grammarParser::calculateFirstSetDFS(unordered_map<string, vector<vector<string> > >& G, const string& symbol, unordered_set<string>& firstSet) {
//    if (firstSet.find(symbol) != firstSet.end()) {
//        return;  // 已经计算过，避免重复计算
//    }
//
//    for (const string& production : G[symbol]) {
//        string firstSym;
//        firstSym.push_back(production[0]);
//        if(production[1] == '\'') firstSym += "'";
//        if(production == "ε") firstSym = production;
//        // 发现希腊符号占两个字符无法单一输出，暂时不接受除了ε的希腊字符
//
//        if (G.find(firstSym) != G.end()) {
//            // 非终结符，递归计算FIRST集合
//            calculateFirstSetDFS(G, firstSym, firstSet);
//            unordered_set<string> firstSetOfFirstChar = firstSet;
//            for (const string& firstSymbol : firstSetOfFirstChar) {
//                if (firstSymbol != "ε") {
//                    firstSet.insert(firstSymbol);
//                }
//            }
//        } else {
//            // 终结符，直接添加到FIRST集合
//            firstSet.insert(firstSym);
//        }
//    }
//}
//void grammarParser::calculateFirstSet(unordered_map<string, vector<string>>& G, unordered_map<string, unordered_set<string>> &firstSets) {
//    for (auto& production : G) {
//        const string& symbol = production.first;
//        unordered_set<string> firstSet;
//        calculateFirstSetDFS(G, symbol, firstSet);
//        firstSets[symbol] = firstSet;
//    }
//
//    cout << "\nFIRST集合：\n";
//    for (const auto& i : firstSets) {
//        cout << "FIRST(" << i.first << ") = {";
//        for (const auto& symbol : i.second) {
//            cout <<" "<< symbol << " ";
//        }
//        cout << "}\n";
//    }
//}
//
//// 计算FOLLOW集合
//void grammarParser::calculateFollowSet(unordered_map<string, vector<string>>& G, unordered_map<string, unordered_set<string>>& firstSets, unordered_map<string, unordered_set<string>>& followSets, const string& start) {
//    // 初始化起始符号的FOLLOW集合
//    followSets[start].insert("$");
//
//    // 遍历产生式，计算FOLLOW集合
//    for (const auto& [nonTerminal, productions] : G) {
//        for (const string& production : productions) {
//            for (size_t i = 0; i < production.size(); ++i) {
//                string symbol;
//                symbol.push_back(production[i]);
//                if(i < production.size() - 1 && production[i + 1] == '\'')
//                    symbol += "'", i++;
//
//                if (G.find(symbol) != G.end()) {
//                    // 非终结符
//                    if (i < production.size() - 1) {
//                        // 非终结符后面还有符号
//                        string nextSymbol = string(1, production[i + 1]);
//                        if(i < production.size() - 2 && production[i + 2] == '\'')
//                            nextSymbol += "'";
//
//                        if (G.find(nextSymbol) != G.end()) {
//                            // 后继符号是非终结符
//                            const unordered_set<string>& firstSet = firstSets[nextSymbol];
//                            unordered_set<string>& followSet = followSets[symbol];
//                            for (const string& firstSymbol : firstSet) {
//                                if (firstSymbol != "ε") {
//                                    followSet.insert(firstSymbol);
//                                }
//                            }
//                            if (firstSet.find("ε") != firstSet.end()) {
//                                // FIRST集合包含ε，则将其后的FIRST集合加入FOLLOW集合
//                                const unordered_set<string>& nextFirstSet = followSets[nextSymbol];
//                                for (const string& nextFirstSymbol : nextFirstSet) {
//                                    followSet.insert(nextFirstSymbol);
//                                }
//                            }
//                        } else {
//                            // 后继符号是终结符
//                            followSets[symbol].insert(nextSymbol);
//                        }
//                    } else {
//                        // 非终结符是产生式的最后一个符号
//                        const unordered_set<string>& followSet = followSets[nonTerminal];
//                        for (const string& followSymbol : followSet) {
//                            followSets[symbol].insert(followSymbol);
//                        }
//                    }
//                }
//            }
//        }
//    }
//    cout << "\nFOLLOW集合：\n";
//    for (const auto& i : followSets) {
//        cout << "FOLLOW(" << i.first << ") = {";
//        for (const auto& symbol : i.second) {
//            cout <<" "<< symbol << " ";
//        }
//        cout << "}\n";
//    }
//}
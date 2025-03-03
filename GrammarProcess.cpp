//
// Created by 左媛 on 2024/1/6.
//

#include "GrammarProcess.h"

// 显示当前文法
void GrammarProcess::display(const unordered_map<string, vector<vector<string> > >& G)
{
    for (const auto& [nonterminal, productions] : G)
    {
        cout << nonterminal << " ->";
        for (int i = 0; i < productions.size(); ++i)
        {
            const vector<string>& production = productions[i];
            for (int j = 0; j < production.size(); ++j)
            {
                cout <<" " << production[j] ;
            }
            if (i != productions.size() - 1)
            {
                cout << " |";
            }
        }
        cout << endl;
    }
}

// 间接左递归转换直接左递归
bool GrammarProcess::hasIndirectRecursion(const string& nonTerminal, const vector<vector<string>>& productions, unordered_map<string, vector<vector<string>>>& G, unordered_set<string>& visited) {
    visited.insert(nonTerminal);  // 将当前非终结符标记为已访问

    for (const vector<string>& production : productions) {
        // 如果产生式的第一个符号是一个非终结符且不等于当前非终结符
        if (G.find(production[0]) != G.end() && production[0] != nonTerminal) {
            // 如果该非终结符已经被访问过，则存在直接左递归
            if (visited.find(production[0]) != visited.end()) {
                return true;
            }

            // 检查该非终结符的产生式是否存在间接左递归
            if (hasIndirectRecursion(production[0], G[production[0]], G, visited)) {
                return true;
            }
        }
    }

    visited.erase(nonTerminal);  // 移除当前非终结符的访问标记
    return false;
}
void GrammarProcess::eliminateIndirectRecursion(unordered_map<string, vector<vector<string>>>& G) {
    bool flag = false;
    unordered_map<string, vector<vector<string>>> newGrammar;
    for (auto& [nonTerminal, productions] : G) {
        unordered_set<string> visited;
        // 深度搜索查看当前产生式是否含有间接左递归
        if (hasIndirectRecursion(nonTerminal, productions, G, visited)) {
            // 当前产生式含有左递归，则将其全部替换至直接左递归
            flag = true;

            while (1)
            {
                bool change = false;
                for (const vector<string>& production : productions) {
                    string first = production[0];
                    if (G.find(first) != G.end() && first != nonTerminal) {
                        // 存在还需要替换的产生式
                        change = true;
                        vector<vector<string>> productionsNew;
                        for(auto i: G[first]) {
                            vector<string> productionNew;
                            for (auto j: i) {
                                productionNew.push_back(j);
                            }
                            productionNew.insert(productionNew.end(), production.begin() + 1, production.end());
                            productionsNew.push_back(productionNew);
                        }
                        productions.erase(productions.begin());
                        productions.insert(productions.end(), productionsNew.begin(), productionsNew.end());
                    }
                }
                if(change) break;
            }
        }
    }
    if (flag) {
        cout << "\n消除间接左递归（将其转换为直接左递归）：\n";
        display(G);
    } else {
        cout << "该文法没有间接左递归\n";
    }
}
// 使用深度优先搜索将能从开始符号到达的非终结符标记
void GrammarProcess::markReachableProductions(unordered_map<string, vector<vector<string>>>& G, const string& start, unordered_set<string>& reachable)
{
    reachable.insert(start);

    if (G.find(start) != G.end()) {
        for (const auto& production : G[start]) {
            for (const auto& symbol : production) {
                if (G.count(symbol)) {
                    string nonTerminal = symbol;

                    if (!production.empty() && production[1] == "'") {
                        nonTerminal += "'";
                    }

                    if (reachable.count(nonTerminal) == 0) {
                        markReachableProductions(G, nonTerminal, reachable);
                    }
                }
            }
        }
    }
}
void GrammarProcess::simplifyGrammar(unordered_map<string, vector<vector<string> > >& G, string start) {
    // 移除不能与开始符号关联的表达式，即没被标记的非终结符与其表达式
    unordered_set<string> reachable;
    markReachableProductions(G, start, reachable);
    bool flag = false;
    for (auto it = G.begin(); it != G.end();) {
        if (reachable.count(it->first) == 0) {
            it = G.erase(it);
            flag = true;
        } else {
            ++it;
        }
    }
    if(flag)
    {
        cout<<"\n删去与开始符号无关联符号后的文法：\n";
        display(G);
    }
}
// 直接左递归消除处理
void GrammarProcess::directLeftRecursion(unordered_map<string, vector<vector<string>>>& G)
{
    bool flag = false;
    unordered_map<string, vector<vector<string>>> newGrammar;

    for (const auto& [nonTerminal, productions] : G) {
        vector<vector<string>> nonRecursiveProductions;
        vector<vector<string>> recursiveProductions;

        for (const auto& production : productions) {
            if (production[0] == nonTerminal) {
                flag = true;
                recursiveProductions.push_back(vector<string>(production.begin() + 1, production.end()));
            } else {
                nonRecursiveProductions.push_back(production);
            }
        }

        if (!recursiveProductions.empty()) {
            string newNonTerminal = nonTerminal + "'";

            for (const auto& recursiveProduction : recursiveProductions) {
                vector<string> newProduction = recursiveProduction;
                newProduction.push_back(newNonTerminal);
                newGrammar[newNonTerminal].push_back(newProduction);
            }

            for (const auto& nonRecursiveProduction : nonRecursiveProductions) {
                vector<string> newProduction = nonRecursiveProduction;
                newProduction.push_back(newNonTerminal);
                newGrammar[nonTerminal].push_back(newProduction);
            }
            newGrammar[newNonTerminal].push_back({"ε"});
        } else {
            for (const auto& nonRecursiveProduction : nonRecursiveProductions) {
                newGrammar[nonTerminal].push_back(nonRecursiveProduction);
            }
        }
    }

    if (flag) {
        G = newGrammar;
        cout << "\n消除直接左递归：\n";
        display(G);
    } else {
        cout << "\n该文法没有直接左递归，继续处理\n";
    }
}

// 计算FIRST集合
void GrammarProcess::calculateFirstSetDFS(unordered_map<string, vector<vector<string>>>& G, const string& symbol,
                                          unordered_set<string>& firstSet, unordered_map<string, unordered_set<string>>& firstSets,
                                          unordered_map<string, unordered_map<string, vector<string>>> &firstMap) {
    if (firstSet.find(symbol) != firstSet.end()) {
        return; // 已经计算过，避免重复计算
    }

    for (const vector<string>& production : G[symbol]) {
        bool allSymbolsNullable = true;
        for (const string& prodSymbol : production) {
            if (G.find(prodSymbol) != G.end()) {
                // 非终结符，递归计算FIRST集合
                calculateFirstSetDFS(G, prodSymbol, firstSet, firstSets, firstMap);
                unordered_set<string> firstSetOfProdSymbol = firstSets[prodSymbol];
                for (const string& first : firstSetOfProdSymbol) {
                    if (first != "ε") {
                        firstSet.insert(first);
                        firstMap[symbol][first] = production;
                    }
                }
                if (firstSetOfProdSymbol.find("ε") == firstSetOfProdSymbol.end()) {
                    allSymbolsNullable = false;
                    break;
                }
            } else {
                // 终结符，直接添加到FIRST集合
                firstSet.insert(prodSymbol);
                firstMap[symbol][prodSymbol] = production;
                allSymbolsNullable = false;
                break;
            }
        }
        if (allSymbolsNullable) {
            firstSet.insert("ε");
        }
    }
}

void GrammarProcess::calculateFirstSet(unordered_map<string, vector<vector<string>>>& G, unordered_map<string, unordered_set<string>>& firstSets,
                                       unordered_map<string, unordered_map<string, vector<string>>> &firstMap)
                                      {
    bool updated;
    do {
        updated = false;
        for (auto& production : G) {
            const string& symbol = production.first;
            unordered_set<string> firstSet;
            calculateFirstSetDFS(G, symbol, firstSet, firstSets, firstMap);
            if (firstSets[symbol] != firstSet) {
                firstSets[symbol] = firstSet;
                updated = true;
            }
        }
    } while (updated);

    cout << "\nFIRST集合：\n";
    for (const auto& i : firstSets) {
        cout << "FIRST(" << i.first << ") = {";
        for (const auto& symbol : i.second) {
            cout << " " << symbol << " ";
        }
        cout << "}\n";
    }
}
// 计算FOLLOW集合
void GrammarProcess::calculateFollowSet(unordered_map<string, vector<vector<string>>>& G, unordered_map<string, unordered_set<string>>& firstSets, unordered_map<string, unordered_set<string>>& followSets, const string& start) {
    // 初始化起始符号的FOLLOW集合
    followSets[start].insert("$");

    bool updated;
    do {
        updated = false;
        // 遍历产生式，计算FOLLOW集合
        for (const auto& [nonTerminal, productions] : G) {
            for (const vector<string>& production : productions) {
                for (size_t i = 0; i < production.size(); ++i) {
                    // 遍历产生式中的符号
                    const string& symbol = production[i];
                    if (G.find(symbol) != G.end()) {

                        // 非终结符
                        unordered_set<string>& followSet = followSets[symbol];
                        if (i < production.size() - 1) {
                            // 非终结符后面还有符号，就将其 FIRST 集合加入当前 FOLLOW 集合
                            const string& nextSymbol = production[i + 1];
                            if (G.find(nextSymbol) != G.end()) {
                                // 后继符号是非终结符
                                const unordered_set<string>& firstSet = firstSets[nextSymbol];
                                for (const string& firstSymbol : firstSet) {
                                    if (firstSymbol != "ε") {
                                        if (followSet.insert(firstSymbol).second) {
                                            updated = true;
                                        }
                                    }
                                }
                                if (firstSet.find("ε") != firstSet.end()) {
                                    // 若当前符号后面所有符号FIRST集合都包含ε，则将当前左部符号的 FOLLOW 集合加入当前非终结符的 FOLLOW 集合
                                    bool isAdd = true;
                                    for (size_t j = i + 1; j < production.size(); ++j)
                                    {
                                        if(G.find(production[j]) == G.end() || firstSets[production[j]].find("ε") == firstSets[production[j]].end())
                                        {   // 后面有终结符也不能加
                                            isAdd = false;
                                        }
                                    }
                                    if(isAdd)
                                    {
                                        for (auto followSymbol : followSets[nonTerminal]) {
                                            if (followSet.insert(followSymbol).second) {
                                                updated = true;
                                            }
                                        }
                                    }

                                }
                            } else{
                                // 终结符直接加入
                                if(followSet.insert(nextSymbol).second)
                                {
                                    updated = true;
                                }
                            }
                        } else {
                            // 非终结符是产生式的最后一个符号
                            for (const string& followSymbol : followSets[nonTerminal]) {
                                if (followSet.insert(followSymbol).second) {
                                    updated = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (updated);

    cout << "\nFOLLOW集合：\n";
    for (const auto& i : followSets) {
        cout << "FOLLOW(" << i.first << ") = {";
        for (const auto& symbol : i.second) {
            cout << " " << symbol << " ";
        }
        cout << "}\n";
    }
}



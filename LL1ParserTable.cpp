//
// Created by luokon on 2024/1/8.
//

#include "LL1ParserTable.h"

// 建立预测分析表
void LL1ParserTable::getParserTable(unordered_map<string, unordered_map<string, vector<string>>>& parserTable,
                                    const unordered_map<string, vector<vector<string>>>& G,
                                    const unordered_map<string, unordered_set<string>>& firstSets,
                                    const unordered_map<string, unordered_set<string>>& followSets,
                                    unordered_map<string, unordered_map<string, vector<string>>> &firstMap) {
    for (const auto& [nonTerminal, productions] : G) {
        const unordered_set<string>& firstSet = firstSets.at(nonTerminal);

        // 递归遍历 FIRST 集合
        for (const string& terminal : firstSet) {
            if (terminal != "ε") {
                parserTable[nonTerminal][terminal] = firstMap[nonTerminal][terminal];
            }
        }

        // 如果 FIRST 集合中包含 ε，则将 FOLLOW 集合对应的产生式赋给预测分析表
        if (firstSet.find("ε") != firstSet.end()) {
            const unordered_set<string>& followSet = followSets.at(nonTerminal);

            for (const string& terminal : followSet) {
                parserTable[nonTerminal][terminal].emplace_back("ε");
            }
        }
    }
}

void LL1ParserTable::printParserTable(const unordered_map<string, unordered_map<string, vector<string>>>& parserTable) {
    cout << "LL1 Parser Table:" << endl;

    for(auto [a, b] : parserTable)
    {
        for(auto [col, production]: b)
        {
            cout<<a<<", "<<col<<" : ";
            for(auto s: production)
            {
                cout<<s;
            }
            cout<<"\n";
        }
    }
    // 打印列
//    cout << setw(10) << left << " ";
//    set<string> col;
//    for (const auto& [nonTerminal, terminalMap] : parserTable) {
//        for(auto  [first, second] : terminalMap)
//            col.insert(first);
//    }
//    for(auto i: col)
//    {
//        cout << setw(10) << i << " ";
//    }
//    cout << endl;
//
//    for (const auto& nonTerminalMap : parserTable) {
//        const auto& nonTerminal = nonTerminalMap.first;
//        cout << setw(10) << left << nonTerminal;    // 打印行
//
//        const auto& terminalMap = nonTerminalMap.second;
//        for (const auto& terminal : terminalMap) {
//            const auto& production = terminal.second;
//            cout << setw(10) << left << nonTerminal << "->";
//
//            for (size_t i = 0; i < production.size(); i++) {
//                cout << production[i];
//                if (i < production.size() - 1) {
//                    cout << "|";
//                }
//            }
//        }
//        cout << endl;
//    }
}

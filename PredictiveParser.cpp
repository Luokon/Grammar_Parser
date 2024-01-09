//
// Created by luokon on 2024/1/8.
//

#include "PredictiveParser.h"

// 建立预测分析表
void PredictiveParser::getParserTable(unordered_map<string, unordered_map<string, vector<string>>>& parserTable,
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

void PredictiveParser::printParserTable(const unordered_map<string, unordered_map<string, vector<string>>>& parserTable) {
    cout << "LL1 Parser Table:" << endl;

    for (const auto& [row, columns] : parserTable) {
        for (const auto& [col, production] : columns) {
            cout << row << ", " << col << " : ";
            for (const auto& symbol : production) {
                cout << symbol;
            }
            cout << "\n";
        }
    }
//    cout << setw(10) << "Non-Terminal" << " | ";
//    for (const auto& [terminal, _] : parserTable.begin()->second) {
//        cout << setw(10) << terminal << " | ";
//    }
//    cout << endl;
//    cout << setfill('-') << setw(12) << "" << "+";
//    for (size_t i = 0; i < parserTable.begin()->second.size(); ++i) {
//        cout << setw(12) << "" << "+";
//    }
//    cout << setfill(' ') << endl;
//
//    for (const auto& [nonTerminal, columns] : parserTable) {
//        cout << setw(10) << nonTerminal << " | ";
//        for (const auto& [_, production] : columns) {
//            for (const auto& symbol : production) {
//                cout << setw(10) << symbol;
//            }
//            cout << " | ";
//        }
//        cout << endl;
//    }
}

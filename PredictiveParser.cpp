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
    set<string> col;
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
        for(const auto& produvtion: productions)
        {
            for(auto terminal : produvtion)
            {
                if(G.find(terminal) == G.end())
                {
                    col.insert(terminal);
                }
            }
        }
    }
    col.insert("$");
    // 将没有的空填补为 ERROR
    for (const auto& [row, columns] : parserTable) {
        for (auto i: col) {
            if(parserTable[row][i].empty()) {
                parserTable[row][i] = vector<string>({"ERROR"});
            }
        }
    }
}

void PredictiveParser::printParserTable(const unordered_map<string, unordered_map<string, vector<string>>>& parserTable) {
//    cout << "LL1 Parser Table:" << endl;
//
//    for (const auto& [row, columns] : parserTable) {
//        for (const auto& [col, production] : columns) {
//            cout << row << ", " << col << " : ";
//            for (const auto& symbol : production) {
//                cout << symbol;
//            }
//            cout << "\n";
//        }
//    }
    cout << "LL1 Parser Table:" << endl;
    cout << setw(10) << "NonTerminal" << " | ";
    set<string> col;
    for (auto [terminal, p] : parserTable) {
        for(auto [a, productions] : p)
            col.insert(a);
    }
    for(auto i: col) {
        cout << setw(10) << i << " | ";
    }
    cout << endl;
    for(int i = 0; i < col.size() + 1; i++)
    cout << setfill('-') << setw(13) << "+";

    cout << setfill(' ') << endl;

    for (const auto& [nonTerminal, columns] : parserTable) {
        cout << setw(10) << nonTerminal << " | ";
        for (const auto& [_, production] : columns) {
            string s = "";
            for (const auto& symbol : production) {
                s += symbol + " ";
            }
            cout<<setw(10)<<s<<" | ";
        }
        cout << endl;
    }
}

// 自顶向下分析
void PredictiveParser::LL1Parser(unordered_map<string, unordered_map<string, vector<string>>> parserTable, vector<string> sentence, string start)
{
    cout<<"分析的句子：";
    sentence.push_back("$");
    for(auto i: sentence)
    {
        cout<<i<<" ";
    }
    cout<<endl;
    stack<string> parseStack;
    parseStack.push("$");  // 终止符
    parseStack.push(start);  // 开始符号

    int index = 0;

    vector<string> errors; // 记录错误信息
    bool flag = true;
    while (!parseStack.empty()) {
        string x = parseStack.top();
        parseStack.pop();
        if(x == "ε") continue;
        if(!parserTable.count(x)) {
            // 栈顶为终结符
            if(x == sentence[index])
            {
                index++;
            }else {
                flag = false;
                cout << "位置 "<< index << "错误：无法识别" << x << endl;
                index++;
            }
        } else {
          // 栈顶为非终结符
          if(x == "$") {
              // 分析结束
              for(auto i: sentence) cout<< i << " ";
              cout << "分析结束，语法正确\n";
              break;
          }
          else {
              // 查分析表找对应产生式
              if(!parserTable[x][sentence[index]].empty() && parserTable[x][sentence[index]][0] != "ERROR")
              { // 逆序入栈
                  for (auto it = parserTable[x][sentence[index]].rbegin(); it != parserTable[x][sentence[index]].rend(); ++it) {
                      parseStack.push(*it);
                  }
              }
              else {
                  flag = false;
                  cout << "位置 "<< index << "错误：" << x << "，"<< sentence[index] << "无法找到对应产生式\n";
              }
          }
        }
    }
    if(flag) cout << "分析完成，句子合法!\n";
    else cout << "分析完成，句子不合法！\n";
}
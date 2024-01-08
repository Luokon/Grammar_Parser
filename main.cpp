#include <bits/stdc++.h>
#include "grammarParser.h"

using namespace std;


ifstream  fin;   // 读取文件的指针，用于获取文法
unordered_map<string, vector<vector<string> > > G;   // 将读入文件的文法存入动态数组中方便操作，即表达式非终结符为key，右部每个产生式为一个vector，其中装非终结符和终结符
unordered_map<string, unordered_set<string> > firstSets; // FIRST集合
unordered_map<string, unordered_set<string> > followSets; // FOLLOW集合
string starter; // 文法开始符，默认第一个符号

void inputGrammar()
{
    G.clear();
    string line;
    while (getline(fin, line))
    {
        string nonterminal;
        vector<vector<string>> productions;

        size_t arrowPos = line.find("->");
        if (arrowPos != string::npos)
        {
            nonterminal = line.substr(0, arrowPos - 1);
            if(starter.empty()) starter = nonterminal;
            string productionStr = line.substr(arrowPos + 3);   // 产生式右边

            vector<string> symbols;
            size_t spacePos = productionStr.find(" ");
            while (spacePos != string::npos)
            {
                string symbol = productionStr.substr(0, spacePos);
                symbols.push_back(symbol);
                productionStr = productionStr.substr(spacePos + 1);
                spacePos = productionStr.find(" ");

                if(productionStr[spacePos + 1] == '|')
                {
                    symbol = productionStr.substr(0, spacePos);
                    symbols.push_back(symbol);
                    productionStr = productionStr.substr(spacePos + 3);
                    spacePos = productionStr.find(" ");
                    productions.push_back(symbols);
                    symbols.clear();
                }

            }

            symbols.push_back(productionStr);
            productions.push_back(symbols);
        }

        G[nonterminal] = productions;
    }

    // 打印读取的文法规则
    cout<<"所读入的文法为：G("<<starter<<")\n";
    grammarParser::display(G);
}

int main()
{
    fin.open("F:\\ClionProject\\Grammar_Parser1.0\\test\\test1.txt", ios::in);
    if (!fin.is_open()) printf("ERROR: can not open the file\n");
    else
    {
        inputGrammar();

        // 词法分析

        // 语法分析
        grammarParser::eliminateIndirectRecursion(G);   // 进行查找间接左递归，将间接左递归转换为直接左递归，若没有则不作处理
//        grammarParser::directLeftRecursion(G, starter);    // 消除直接左递归，同理边判断边处理，没有则不做处理
//        grammarParser::simplifyGrammar(G, starter);     // 简化后最终版本
//        grammarParser::calculateFirstSet(G, firstSets); // FIRST集合
//        grammarParser::calculateFollowSet(G, firstSets, followSets, starter);  // FOLLOW集合
    }

    return 0;
}

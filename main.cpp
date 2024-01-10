#include <bits/stdc++.h>
#include "GrammarProcess.h"
#include "LL1GrammarChecker.h"
#include "PredictiveParser.h"
using namespace std;


ifstream  fin;   // 读取文件的指针，用于获取文法
unordered_map<string, vector<vector<string> > > G;   // 将读入文件的文法存入动态数组中方便操作，即表达式非终结符为key，右部每个产生式为一个vector，其中装非终结符和终结符
unordered_map<string, unordered_set<string> > firstSets; // FIRST集合
unordered_map<string, unordered_map<string, vector<string> > > firstMap; // 记录每个非终结符的FIRST集合中每个终结符所对应的产生式，方便后续处理预测分析表
unordered_map<string, unordered_set<string> > followSets; // FOLLOW集合
unordered_map<string, unordered_map<string, vector<string> > > parserTable; // 预测分析表
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
    GrammarProcess::display(G);
}
void show()
{
    // 终端显示界面
    cout << "*********** LL（1）语法分析器 ***********\n";
    cout << "*输入对应数字选择一个选项：              *\n";
    cout <<  "*       0. 测试包含间接左递归的文法      *\n";
    cout <<  "*       1. 测试只包含直接左递归的文法    *\n";
    cout <<  "*       2. 测试没有左递归的文法         *\n";
    cout <<  "*       3. 自己输入文法路径            *\n";
    cout <<  "*       4. 退出                     *\n";
    cout << "************************************\n";
    cout << "请输入数字并按下回车键：";
}
void showSentence()
{
    
}
int main()
{
    int cho = 0;
    while(cho != 4)
    {
        string path = "";
        show();
        cin >> cho;
        switch (cho) {
            case 0:
                // 选项0的操作
                path = "F:\\ClionProject\\Grammar_Parser\\test\\test0.txt";
                break;
            case 1:
                // 选项1的操作
                path = "F:\\ClionProject\\Grammar_Parser\\test\\test1.txt";
                break;
            case 2:
                // 选项2的操作
                path = "F:\\ClionProject\\Grammar_Parser\\test\\test2.txt";
                break;
            case 3:
                cout << "请输入你想分析的文法所存储的文件路径: ";
                cin >> path;
                cout << endl;
                break;
            case 4:
                return 0;
            default:
                cout << "无效的选项！" << endl;
                break;
        }
        fin.open(path, ios::in);
        if (!fin.is_open()) printf("ERROR: 文件不存在！\n");
        else
        {
            inputGrammar();
            // 语法分析
            GrammarProcess::eliminateIndirectRecursion(G);   // 进行查找间接左递归，将间接左递归转换为直接左递归，若没有则不作处理
            GrammarProcess::directLeftRecursion(G);    // 消除直接左递归，同理边判断边处理，没有则不做处理
            GrammarProcess::calculateFirstSet(G, firstSets, firstMap); // FIRST集合
            GrammarProcess::calculateFollowSet(G, firstSets, followSets, starter);  // FOLLOW集合

            // 判断是否为LL(1)文法
            LL1GrammarChecker grammarChecker(firstSets, followSets);
            bool isLL1 = grammarChecker.isLL1Grammar(G);
            if(isLL1)
            {
                cout<<"通过检验，该文法为LL（1）文法，可以继续分析，请选择接下来的动作：\n";


                PredictiveParser table;
                table.getParserTable(parserTable, G, firstSets, followSets, firstMap);
                table.printParserTable(parserTable);
                vector<string> sentence = {"*", "i", "+", "i"};
                PredictiveParser::LL1Parser(parserTable, sentence, starter);
            }
            else cout<<"该文法不是LL（1）文法\n";
        }
    }

    return 0;
}

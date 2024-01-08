//
// Created by luokon on 2024/1/8.
//

#include "LL1ParserTable.h"

LL1ParserTable::LL1ParserTable() {}

void LL1ParserTable::addEntry(const string& nonTerminal, const string& terminal, const vector<string>& production) {
    if (table.find(nonTerminal) == table.end()) {
        table[nonTerminal] = map<string, vector<string>>();
    }
    table[nonTerminal][terminal] = production;
}

vector<string> LL1ParserTable::getProduction(const string& nonTerminal, const string& terminal) {
    return table[nonTerminal][terminal];
}

bool LL1ParserTable::hasEntry(const string& nonTerminal, const string& terminal) {
    return table.find(nonTerminal) != table.end() && table[nonTerminal].find(terminal) != table[nonTerminal].end();
}
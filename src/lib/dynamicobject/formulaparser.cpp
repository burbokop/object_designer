#include "formulaparser.h"

#include <iostream>
#include <stack>
#include <utility>
#include <stdlib.h>


KFormulaParser::Error KFormulaParser::error() const {
    return m_error;
}


double KFormulaParser::parse(const std::string &formula) {
    std::stack<double> actionStack;
    std::stack<std::pair<int, char>> ops;

    auto microCall = [&actionStack, &ops, this] (std::function<double (double, double)>& f) {
        if(f) {
            double result = actionStack.top();
            actionStack.pop();
            result = f(actionStack.top(), result);
            actionStack.pop();
            actionStack.push(result);
        } else {
            m_error = UnresolvedOperation;
        }
        ops.pop();
    };

    const int order = 2; int level = 0;
    for (char* sp = const_cast<char*>(formula.c_str());; ++sp) {
        while (*sp == '(') { level += order; ++sp; }
        actionStack.push(strtod(sp, &sp));
        while (*sp == ')') { level -= order; ++sp; }

        if (!*sp) { while(!ops.empty()) microCall(operations[ops.top().second].second); break; }

        const int op =  operations[*sp].first + level;
        while (!ops.empty() && ops.top().first >= op) microCall(operations[ops.top().second].second);

        ops.push(std::make_pair(op, *sp));
    }
    return actionStack.top();
}


double KFormulaParser::parse(const QString &formula) {
    return parse(formula.toStdString());
}

std::string KFormulaParser::removeSpacing(const std::string &string) {
    std::string result;
    for(auto c : string) {
        if(c != ' ' && c != '\n' && c != '\t') {
            result.push_back(c);
        }
    }
    return result;
}

QString KFormulaParser::removeSpacing(const QString &string) {
    return QString::fromStdString(removeSpacing(string.toStdString()));
}


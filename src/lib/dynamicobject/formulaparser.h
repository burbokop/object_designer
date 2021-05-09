#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H

#include <QString>
#include <string>
#include <functional>
#include <map>


class KFormulaParser {
public:
    enum Error { NoError, UnresolvedOperation };
private:
    Error m_error = NoError;
    std::map<char, std::pair<int, std::function<double (double, double)>>> operations;
public:
    double parse(const std::string &formula);
    double parse(const QString &formula);
    static std::string removeSpacing(const std::string &string);
    static QString removeSpacing(const QString &string);
    template<typename T>
    void addOperation(char symbol, int order, T function) { operations[symbol] = { order, function }; }
    inline void addOperation(char symbol, int order, double (*function)(double, double)) { operations[symbol] = { order, function }; }

    Error error() const;

};

#endif // FORMULAPARSER_H

#ifndef KVALUESUBSTITUTE_H
#define KVALUESUBSTITUTE_H

#include <QRegularExpression>
#include <QString>
#include <QVariantMap>

class KValueSubstitutor {
public:
    static QString substitute(QString string, const QVariantMap &values, QRegularExpression regexp = QRegularExpression("([a-zA-Z][a-zA-Z0-9]*)"));
};

#endif // KVALUESUBSTITUTE_H

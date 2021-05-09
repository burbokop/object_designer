#include "kvaluesubstitute.h"

QString KValueSubstitutor::substitute(QString string, const QVariantMap &values, QRegularExpression regexp) {
    (void)regexp;
    //auto match = regexp.match(string);
    //int sumDelta = 0;
    //for (int i = 1; i <= match.lastCapturedIndex(); ++i) {
    //    auto captured = match.captured(i);
    //    auto value = values[captured].toString();
    //    auto delta = value.size() - match.capturedLength(i);
    //    string.replace(match.capturedStart(i) + sumDelta, match.capturedLength(i), value);
    //    sumDelta += delta;
    //}
    //return string;

    for(auto it = values.begin(); it != values.end(); ++it) {
        string.replace(it.key(), it.value().toString());
    }
    return string;
}

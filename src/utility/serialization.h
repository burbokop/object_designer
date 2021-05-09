#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <QDataStream>
#include <QVector>

//Q_DECLARE_METATYPE(QVector<double>)
inline QDataStream& operator<<(QDataStream& out, const QVector<double>& v) {
    for(auto vv : v)
        out << vv;
    return out;
}
inline QDataStream& operator>>(QDataStream& in, QVector<double>& v) {
    for(auto vv : v)
        in >> vv;
    return in;
}
inline int qVectorDoubleStreamOperatorsRegistration = qRegisterMetaTypeStreamOperators<QVector<double>>();

#endif // SERIALIZATION_H

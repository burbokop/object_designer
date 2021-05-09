#ifndef KOBJECTLIFETRACKER_H
#define KOBJECTLIFETRACKER_H

#include <klibcore/src/kmacro.h>

class KObjectLifeTracker : public QObject {
    Q_OBJECT
    K_PRIVATE_SINGLETON(KObjectLifeTracker)
    K_QML_SINGLETON(KObjectLifeTracker)


public:
    explicit KObjectLifeTracker(QObject *parent = nullptr);

signals:
    void watcherTriggered(QVariant value);


public slots:
    void sequentlyDestoy(QObject *trigger, QObject *target);
    void registerWatcher(QObject *trigger, QVariant arg);
};

#endif // KOBJECTLIFETRACKER_H

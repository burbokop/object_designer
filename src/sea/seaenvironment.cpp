#include "seaenvironment.h"

#include <QTimer>


SeaEnvironment::SeaEnvironment(QObject *parent) : QObject(parent) {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){
        auto it = vessels.begin();
        while (1) {
            if(it.operator*()->readyRemove()) {
                it = vessels.erase(it);
            } else {
                ++it;
            }
        }

        while(requestQueue.containsItemType<SeaCreateRequest>()) {
            //auto v = vesselFactory.createShared(requestQueue.dequeue<SeaCreateRequest>().value());
            //v->setParent(this);
            //vessels.push_back(v);
        }

        while(requestQueue.containsItemType<SeaDestroyRequest>()) {
            auto r = requestQueue.dequeue<SeaDestroyRequest>();
            for(auto v : vessels) { if(v->objectName() == r.value()) v->remove(); }
        }
    });
    timer->start(20);
}

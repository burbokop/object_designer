#ifndef CLIENT1_H
#define CLIENT1_H

#include <QObject>

#include <src/network/klocalsyncronizer.h>
#include <klibcore/src/kmacro.h>
#include <src/sea/pdfwriter.h>

class Client1 : public QObject {
    Q_OBJECT
    K_QML_INTERFACE(Client1)
    K_READONLY_PROPERTY(QString, msg, msg, setMsg, msgChanged, QString())
    K_READONLY_PROPERTY(QString, initialInfo, initialInfo, setInitialInfo, initialInfoChanged, QString())
    K_AUTO_PROPERTY(double, angle, angle, setAngle, angleChanged, 0)
    K_AUTO_PROPERTY(bool, checkBox, checkBox, setCheckBox, checkBoxChanged, 0)
    K_AUTO_PROPERTY(bool, lamp, lamp, setLamp, lampChanged, false)
    K_AUTO_PROPERTY(double, angle2, angle2, setAngle2, angle2Changed, false)

    K_AUTO_PROPERTY(double, slider1, slider1, setSlider1, slider1Changed, 0)
    K_AUTO_PROPERTY(double, slider2, slider2, setSlider2, slider2Changed, 0)
    K_AUTO_PROPERTY(double, slider3, slider3, setSlider3, slider3Changed, 0)
    K_AUTO_PROPERTY(double, slider4, slider4, setSlider4, slider4Changed, 0)
    K_AUTO_PROPERTY(double, slider5, slider5, setSlider5, slider5Changed, 0)
    K_AUTO_PROPERTY(double, slider6, slider6, setSlider6, slider6Changed, 0)

    K_CONST_PROPERTY(PdfWriter*, pdf, new PdfWriter(this))

public:
    explicit Client1(QObject *parent = nullptr);

signals:
    void messageReady(QString msg);

public slots:
    void sendMessage(QVariant msg);
};

#endif // CLIENT1_H

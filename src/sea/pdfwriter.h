#ifndef PDFWRITER_H
#define PDFWRITER_H

#include <klibcore/src/kmacro.h>

class HardwareViewerModel;
class PdfWriter : public QObject {
    Q_OBJECT
    K_AUTO_PROPERTY(QString, text, text, setText, textChanged, QString())
public:
    explicit PdfWriter(QObject *parent = nullptr);
    void checkFoder();
    void writeText(QString text);

    void writeTable(HardwareViewerModel *data);

signals:

};

#endif // PDFWRITER_H

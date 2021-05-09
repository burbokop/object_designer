#include "pdfwriter.h"

#include <QDir>
#include <QPainter>
#include <QPdfWriter>

#include <src/utility/hardwareviewermodel.h>

#include <src/graphics/paint/kpagepaintedtool.h>

PdfWriter::PdfWriter(QObject *parent) : QObject(parent) {
    connect(this, &PdfWriter::textChanged, this, &PdfWriter::writeText);

    QList<QMap<QString, QString>> list;

    HardwareViewerModel model({ "name", "type", "isWritable", "value" });
    model.push_back({ { "name", "aaa" }, { "type", "int" }, { "isWritable", "true" }, { "value", 0 } });
    model.push_back({ { "name", "null" }, { "type", "QVariant" }, { "isWritable", "false" }, { "value", QVariant() } });
    model.push_back({ { "name", "text" }, { "type", "QString" }, { "isWritable", "false" }, { "value", "ttt" } });
    model.push_back({ { "name", "text2" }, { "type", "QString" }, { "isWritable", "false" }, { "value", "ttt2" } });

    writeTable(&model);
}

void PdfWriter::checkFoder() {
    if(!QDir("./pdf").exists()) {
        QDir("./").mkdir("pdf");
    }
}

void PdfWriter::writeText(QString text) {
    checkFoder();


    QPdfWriter pdfwriter("./pdf/file1.pdf");
    pdfwriter.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&pdfwriter);

    painter.drawText(0, 0, text);

}

void PdfWriter::writeTable(HardwareViewerModel *data) {
    checkFoder();
    KPagePaintedTool modelpt;
    modelpt.addRow<400>("gogadoda", QTextOption(Qt::AlignVCenter | Qt::AlignLeft));
    modelpt.addRow<4000>(data, QTextOption(Qt::AlignCenter), true);
    modelpt.addRow<9000>("gogadoda2", QTextOption(Qt::AlignCenter));



    QPdfWriter pdfwriter("./pdf/table1.pdf");
    pdfwriter.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&pdfwriter);
    painter.setPen(QPen(QColor("#222244"), 10));
    modelpt.setWidth(painter.window().width());
    modelpt.setHeight(painter.window().height());
    modelpt.paint(&painter);
}

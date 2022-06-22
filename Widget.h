#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include "PortOperation.h"

class Widget : public QWidget
{
    Q_OBJECT

    QString portName;
    PortSettings settings;
    PortOperation port;
    bool portStatus;

    QPlainTextEdit textEditRecv;
    QPlainTextEdit textEditSend;
    QPushButton pushButtonSend;
    QPushButton pushButtonClear;

    QComboBox comboBoxUart;
    QLabel lable0;

    QComboBox comboBoxBaudRate;
    QLabel lable1;

    QComboBox comboBoxDataBit;
    QLabel lable2;

    QComboBox comboBoxParityBit;
    QLabel lable3;

    QComboBox comboBoxStopBit;
    QLabel lable4;

    QComboBox comboBoxFlowCont;
    QLabel lable5;

    QPushButton pushButtonStart;

protected slots:
    void appendText(QString text);
    void sendButtonClicked();
    void clearButtonClicked();
    void startButtonClicked();

    void comboxUartCharged(int index);
    void comboxBaudRateCharged(int index);
    void comboxDataBitCharged(int index);
    void comboxParityBitCharged(int index);
    void comboxStopBitCharged(int index);
    void comboxFlowContCharged(int index);
signals:
    void sendData(QString data);

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H

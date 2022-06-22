#ifndef PORTOPERATION_H
#define PORTOPERATION_H

#include <QObject>
#include <QString>
#include "win_qextserialport.h"


class PortOperation : public QObject
{
    Q_OBJECT

    Win_QextSerialPort* myCom;;
    QString reveText;

public:
    explicit PortOperation(QObject *parent = 0);
    bool openMyCom(QString portName, PortSettings settings);
    void writeMyCom(QString text);
    void closeMyCom();
    ~PortOperation();
    
signals:
    void updateUI(QString text);
public slots:
    void readMyCom();
};

#endif // PORTOPERATION_H

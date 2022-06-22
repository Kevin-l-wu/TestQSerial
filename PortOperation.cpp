#include <QDebug>

#include "qextserialport.h"
#include "qextserialbase.h"

#include "PortOperation.h"


PortOperation::PortOperation(QObject *parent) :
    QObject(parent)
{
    myCom = NULL;
    reveText.clear();
}


bool PortOperation::openMyCom(QString portName, PortSettings settings)
{
    bool ret = false;

    myCom = new Win_QextSerialPort(portName, QextSerialBase::EventDriven);

    if(myCom != NULL)
    {
        if(myCom->open(QIODevice::ReadWrite))
        {
            qDebug() << portName << " opened success";

            qDebug() << "myCom->isOpen() = " << myCom->isOpen();

            myCom->setBaudRate(settings.BaudRate);
            myCom->setDataBits(settings.DataBits);
            myCom->setParity(settings.Parity);
            myCom->setStopBits(settings.StopBits);
            myCom->setFlowControl(settings.FlowControl);

            connect(myCom, SIGNAL(readyRead()), this, SLOT(readMyCom()));

            ret = true;
        }
        else
        {
           qDebug() << portName << " opened fail";
           delete myCom;
           myCom = NULL;
        }
    }

    return ret;
}

void PortOperation::closeMyCom()
{
    if(myCom != NULL)
    {
        if(myCom->isOpen())
        {
            myCom->close();
        }

        delete myCom;
        myCom = NULL;
    }
}

void PortOperation::readMyCom()
{
    qDebug() << "PortOperation::readMyCom()";
    int len = myCom->bytesAvailable();
    qDebug() << "len = " << len;

    QByteArray temp;

    if(len > 0)
    {
        temp = myCom->readAll();
        reveText += temp.data();

        if((len % 32) != 0)
        {
            qDebug() << reveText;
            emit updateUI(reveText);
            reveText.clear();
        }
    }
}

void PortOperation::writeMyCom(QString text)
{
     myCom->write(text.toAscii());
}

PortOperation::~PortOperation()
{

}

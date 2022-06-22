#include <QDebug>
#include <QStringList>
#include <QFont>

#include "Widget.h"
#include "PortOperation.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    portName = "COM3";
    portStatus = false;

    QFont font("Courier New");

    settings.BaudRate = BAUD115200;
    settings.DataBits = DATA_8;
    settings.FlowControl = FLOW_OFF;
    settings.Parity = PAR_NONE;
    settings.StopBits = STOP_1;


    QStringList list("a");
    list.append("b");
    list.append("c");

    QStringList listUart("COM3");
    listUart.append("COM4");
    listUart.append("COM5");

    QStringList listBaudRate("9600");
    listBaudRate.append("19200");
    listBaudRate.append("38400");
    listBaudRate.append("57600");
    listBaudRate.append("115200");

    QStringList listDataBit("5");
    listDataBit.append("6");
    listDataBit.append("7");
    listDataBit.append("8");


    QStringList listParityBit("None");
    listParityBit.append("Even");
    listParityBit.append("Old");
    listParityBit.append("Mark");
    listParityBit.append("Space");

    QStringList listStopBit("1");
    listStopBit.append("1.5");
    listStopBit.append("2");

    QStringList listFlowCont("None");
    listFlowCont.append("RTS/CTS");
    listFlowCont.append("XON/XOFF");


    textEditRecv.setParent(this);
    textEditRecv.move(200, 20);
    textEditRecv.resize(500, 450);
    textEditRecv.setReadOnly(true);

    textEditRecv.setFont(font);

    pushButtonClear.setParent(this);
    pushButtonClear.move(720, 20);
    pushButtonClear.resize(80, 30);
    pushButtonClear.setText("Clear");

    textEditSend.setParent(this);
    textEditSend.move(200, 500);
    textEditSend.resize(500, 100);

    textEditSend.setFont(font);

    pushButtonSend.setParent(this);
    pushButtonSend.move(720, 500);
    pushButtonSend.resize(80, 30);
    pushButtonSend.setText("Send");

    lable0.setParent(this);
    lable0.move(20, 20);
    lable0.resize(60, 25);
    lable0.setText("Uart");

    comboBoxUart.setParent(this);
    comboBoxUart.move(80, 20);
    comboBoxUart.resize(80, 25);
    comboBoxUart.insertItems(0, listUart);


    lable1.setParent(this);
    lable1.move(20, 60);
    lable1.resize(60, 25);
    lable1.setText("BaudRate");

    comboBoxBaudRate.setParent(this);
    comboBoxBaudRate.move(80, 60);
    comboBoxBaudRate.resize(80, 25);
    comboBoxBaudRate.insertItems(0, listBaudRate);
    comboBoxBaudRate.setCurrentIndex(4);

    lable2.setParent(this);
    lable2.move(20, 100);
    lable2.resize(60, 25);
    lable2.setText("DataBit");

    comboBoxDataBit.setParent(this);
    comboBoxDataBit.move(80, 100);
    comboBoxDataBit.resize(80, 25);
    comboBoxDataBit.insertItems(0, listDataBit);
    comboBoxDataBit.setCurrentIndex(3);

    lable3.setParent(this);
    lable3.move(20, 140);
    lable3.resize(60, 25);
    lable3.setText("ParityBit");

    comboBoxParityBit.setParent(this);
    comboBoxParityBit.move(80, 140);
    comboBoxParityBit.resize(80, 25);
    comboBoxParityBit.insertItems(0, listParityBit);



    lable4.setParent(this);
    lable4.move(20, 180);
    lable4.resize(60, 25);
    lable4.setText("StopBit");

    comboBoxStopBit.setParent(this);
    comboBoxStopBit.move(80, 180);
    comboBoxStopBit.resize(80, 25);
    comboBoxStopBit.insertItems(0, listStopBit);

    lable5.setParent(this);
    lable5.move(20, 220);
    lable5.resize(60, 25);
    lable5.setText("FlowCont");

    comboBoxFlowCont.setParent(this);
    comboBoxFlowCont.move(80, 220);
    comboBoxFlowCont.resize(80, 25);
    comboBoxFlowCont.insertItems(0, listFlowCont);


    pushButtonStart.setParent(this);
    pushButtonStart.move(80, 260);
    pushButtonStart.resize(80, 30);
    pushButtonStart.setText("Start");

    this->setFixedSize(820, 620);


    connect(&pushButtonSend, SIGNAL(clicked()), this, SLOT(sendButtonClicked()));
    connect(&pushButtonClear, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));
    connect(&pushButtonStart, SIGNAL(clicked()), this, SLOT(startButtonClicked()));

    connect(&comboBoxUart, SIGNAL(currentIndexChanged(int)), this, SLOT(comboxUartCharged(int)));
    connect(&comboBoxBaudRate, SIGNAL(currentIndexChanged(int)), this, SLOT(comboxBaudRateCharged(int)));
    connect(&comboBoxDataBit, SIGNAL(currentIndexChanged(int)), this, SLOT(comboxDataBitCharged(int)));
    connect(&comboBoxParityBit, SIGNAL(currentIndexChanged(int)), this, SLOT(comboxParityBitCharged(int)));
    connect(&comboBoxStopBit, SIGNAL(currentIndexChanged(int)), this, SLOT(comboxStopBitCharged(int)));
    connect(&comboBoxFlowCont, SIGNAL(currentIndexChanged(int)), this, SLOT(comboxFlowContCharged(int)));

    connect(&port, SIGNAL(updateUI(QString)), this, SLOT(appendText(QString)));
}

void Widget::appendText(QString text)
{
     textEditRecv.appendPlainText(text);
}

void Widget::sendButtonClicked()
{
    qDebug() << "Widget::sendButtonClicked()";

    QString text = textEditSend.toPlainText();

    text += "\r\n";

    qDebug() << "text = " << text;

    if((portStatus == true) && (text.isEmpty() != true))
    {
        port.writeMyCom(text);
    }
}

void Widget::clearButtonClicked()
{
    qDebug() << "Widget::clearButtonClicked()";
    textEditRecv.clear();
}

void Widget::startButtonClicked()
{
    qDebug() << "Widget::startButtonClicked()";

    qDebug() << "Start: portStatus = " << portStatus ;

    if(portStatus == false)
    {
        if(port.openMyCom(portName, settings))
        {
            pushButtonStart.setText("Stop");
            portStatus = true;
        }
    }
    else
    {
        port.closeMyCom();

        pushButtonStart.setText("Start");

        portStatus = false;
    }

    qDebug() << "End: portStatus = " << portStatus ;


/*
    if(pushButtonStart.text() == "Start")
    {
        if(port.openMyCom(portName, settings))
        {
            pushButtonStart.setText("Stop");
        }
    }
    else
    {
        port.closeMyCom();
        pushButtonStart.setText("Start");
    }

*/
}


void  Widget::comboxUartCharged(int index)
{
    qDebug() << "Widget::comboxUartCharged: " << index;
    if(index == 0)
    {
        portName = "COM3";
    }
    else if(index == 1)
    {
        portName = "COM4";
    }
    else if(index == 2)
    {
        portName = "COM5";
    }
}

void Widget::comboxBaudRateCharged(int index)
{
    switch(index)
    {
        case 0:
            settings.BaudRate = BAUD9600;
            break;

        case 1:
            settings.BaudRate = BAUD19200;
            break;

        case 2:
            settings.BaudRate = BAUD38400;
            break;

        case 3:
            settings.BaudRate = BAUD57600;
            break;

        case 4:
            settings.BaudRate = BAUD115200;
            break;

        default:
            settings.BaudRate = BAUD115200;
            break;
    }
}

void Widget::comboxDataBitCharged(int index)
{
    switch(index)
    {
        case 0:
            settings.DataBits = DATA_5;
            break;
        case 1:
            settings.DataBits = DATA_6;
            break;
        case 2:
            settings.DataBits = DATA_7;
            break;
        case 3:
            settings.DataBits = DATA_8;
            break;
        default:
            settings.DataBits = DATA_8;
            break;
    }
}

void Widget::comboxParityBitCharged(int index)
{
    switch(index)
    {
        case 0:
            settings.Parity = PAR_NONE;
            break;
        case 1:
            settings.Parity = PAR_ODD;
            break;
        case 2:
            settings.Parity = PAR_EVEN;
            break;
        case 3:
            settings.Parity = PAR_MARK;
            break;
        case 4:
            settings.Parity = PAR_SPACE;
            break;
        default:
            settings.Parity = PAR_NONE;
            break;
    }
}

void Widget::comboxStopBitCharged(int index)
{
    switch(index)
    {
        case 0:
            settings.StopBits = STOP_1;
            break;
        case 1:
            settings.StopBits = STOP_1_5;
            break;
        case 2:
            settings.StopBits = STOP_2;
            break;
        default:
            settings.StopBits = STOP_1;
            break;
    }

}

void Widget::comboxFlowContCharged(int index)
{
    switch(index)
    {
        case 0:
            settings.FlowControl = FLOW_OFF;
            break;
        case 1:
            settings.FlowControl = FLOW_HARDWARE;
            break;
        case 2:
            settings.FlowControl = FLOW_XONXOFF;
            break;
        default:
            settings.FlowControl = FLOW_OFF;
            break;
    }
}


Widget::~Widget()
{

}

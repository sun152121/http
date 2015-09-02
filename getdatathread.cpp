#include "getdatathread.h"

getDataThread::getDataThread(QString url,int request_type,QString data)
{
//    request_url = QUrl(url);
    this->url = url;
    this->request_type = request_type;
    this->data = data;

//    nam = new QNetworkAccessManager(this);
//    QObject::connect(nam,SIGNAL(finished(QNetworkReply*)),this,SLOT(getDataFinishSlot(QNetworkReply*)));
}
getDataThread::~getDataThread()
{
    delete reply;
    delete nam;
}

void getDataThread::run()
{
    request_url = QUrl(url);
    nam = new QNetworkAccessManager(this);
	QObject::connect(nam,SIGNAL(finished(QNetworkReply*)),this,SLOT(getDataFinishSlot(QNetworkReply*)));

    if(request_type == 1)
    {
        //GET请求
        request.setUrl(request_url);
        reply = nam->get(request);
        qDebug("getDataThread run\n");
    }
    else
    {
        //POST请求
        request.setUrl(request_url);
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

        QByteArray postData(data.toStdString().c_str());

        reply = nam->post(request,postData);
    }

    this->exec();
}

void getDataThread::getDataFinishSlot(QNetworkReply *reply)
{
    qDebug("getDataFinishSlot\n");
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QString str = QString::fromUtf8(bytes);
        //ui->textEdit_2->setText(str);
        emit getDataThreadFinish(&str);

        qDebug("str[%s]\n",str.toStdString().c_str());
    }
}

#ifndef GETDATATHREAD_H
#define GETDATATHREAD_H

#include <QThread>
#include <QNetworkReply>
#include <QNetworkRequest>

class getDataThread : public QThread
{
    Q_OBJECT
public:
    getDataThread(QString url,int request_type,QString data="");
    ~getDataThread();

private:
    QString url;
    int request_type;
    QString data;
    QUrl request_url;
    QNetworkRequest request;
    QNetworkReply* reply;
    QNetworkAccessManager* nam;

protected:
    virtual void run();

signals:
     void getDataThreadFinish(QString* res);

public slots:
     void getDataFinishSlot(QNetworkReply *reply);
     //void replyFinished(QNetworkReply *reply);

};

#endif // GETDATATHREAD_H

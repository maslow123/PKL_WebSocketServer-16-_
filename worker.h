#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include <QWebSocketServer>
#include <QWebSocket>

class worker : public QObject
{
    Q_OBJECT
public:
    explicit worker(QObject *parent = 0);
    ~worker();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

Q_SIGNALS:
    void closed();
};

#endif // WORKER_H

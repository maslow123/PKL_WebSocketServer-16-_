#include "worker.h"

worker::worker(QObject *parent) : QObject(parent)
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("WebSocket Server"), QWebSocketServer::NonSecureMode, this);
    if (m_pWebSocketServer->listen(QHostAddress::Any, 134)) {
        connect(m_pWebSocketServer, SIGNAL(newConnection()),this, SLOT(onNewConnection()));
//        connect(m_pWebSocketServer, SIGNAL(closed()), this, SLOT(closed()));
    }
}

worker::~worker()
{
    if (m_pWebSocketServer->isListening()) {
        m_pWebSocketServer->close();
        qDeleteAll(m_clients.begin(), m_clients.end());
    }
}

void worker::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &worker::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &worker::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &worker::socketDisconnected);

    pSocket->ignoreSslErrors();
//    pSocket->sendTextMessage("Berhasil Connect cuy ..");

    m_clients << pSocket;
}

void worker::processTextMessage(QString message)
{
//    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
//    if (pClient) {pClient->sendTextMessage(message);}
    qDebug() <<message;
    for (int i = 0; i < m_clients.length(); i++) {
        m_clients.at(i)->sendTextMessage(message);
    }
}

void worker::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {pClient->sendBinaryMessage(message);}
}

void worker::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

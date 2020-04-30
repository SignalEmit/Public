#include "tcpserver.h"

namespace Tcp
{
	TcpServer::TcpServer(
		const QString &modelname,
		const QString &ip,
		const quint16 &port) :
		m_strModelName(modelname)
	{
		p_tcpSocketServer = new QTcpServer;
		if (!p_tcpSocketServer->listen(QHostAddress("0.0.0.0"), port))
		{
			Log(p_tcpSocketServer->errorString());
		}

		QObject::connect(p_tcpSocketServer, &QTcpServer::newConnection, [&]()
		{

			QString strWebSocketID = Tool::Tools::getID();
			Tcp::TcpSocket *tcpSocket = new Tcp::TcpSocket(strWebSocketID,
				p_tcpSocketServer->nextPendingConnection());

			//tcpsocket 枷锁 防止程序出错
			m_tcpSocketMapMutex.lock();
			m_tcpSocketMap[strWebSocketID] = tcpSocket;
			m_tcpSocketMapMutex.unlock();

			QObject::connect(tcpSocket, &Tcp::TcpSocket::receiveTextMessage, [&](const QString &id, const QString &message)
			{
				emit receiveTextMessage(id, message);
			});
		});

		p_checkSocketState = new QTimer;
		connect(p_checkSocketState, &QTimer::timeout, [&]()
		{
			this->run();
		});
		p_checkSocketState->start(300);

	}

	bool TcpServer::changeTcpSocketName(
		const QString &waitchangeid,
		const QString &changname
	)
	{
		m_tcpSocketMapMutex.lock();
		auto it = m_tcpSocketMap.find(waitchangeid);
		if (it != m_tcpSocketMap.end())
		{

			Tcp::TcpSocket *tcpSocket = it->second;
			tcpSocket->setID(changname);
			m_tcpSocketMap.erase(it);
			m_tcpSocketMap[changname] = tcpSocket;
			m_tcpSocketMapMutex.unlock();
			return true;

		}
		else
		{
			Log("YWebSocketServer::changeWebSocketName 未找到待改变的节点");
		}
		m_tcpSocketMapMutex.unlock();
		return false;
	}

	bool TcpServer::sendTextMessage(
		const QString &name,
		const QString &message
	)
	{
		m_tcpSocketMapMutex.lock();
		auto it = m_tcpSocketMap.find(name);
		if (it != m_tcpSocketMap.end())
		{
			it->second->sendTcpMessage(message);
			Log(tr("[%0]socket发送[%1]成功！！！").arg(name).arg(message));
		}
		else
		{
			Log("YWebSocketServer::sendTextMessage 未找到待改变的节点");
		}
		m_tcpSocketMapMutex.unlock();
		return true;
	}

	void TcpServer::run()
	{
		m_tcpSocketMapMutex.lock();
		auto it = m_tcpSocketMap.begin();
		while (it != m_tcpSocketMap.end())
		{
			Tcp::TcpSocket *tcpSocket = it->second;
			if (tcpSocket->state() == QAbstractSocket::ClosingState || tcpSocket->state() == QAbstractSocket::UnconnectedState)
			{
				tcpSocket->getTcpSocket()->close();
				m_tcpSocketMap.erase(it++);
				delete tcpSocket;						//整个删除这个节点
			}
			else
			{
				it++;
			}
		}
		m_tcpSocketMapMutex.unlock();
	}

	// 向所有的websocket发送消息
	bool TcpServer::sendTextToAll(
		const QString &message
	)
	{
		m_tcpSocketMapMutex.lock();
		for (auto it = m_tcpSocketMap.begin(); it != m_tcpSocketMap.end(); it++)
		{
			quint64  nSendSize = it->second->sendTcpMessage(message);
			Log(tr("向所有的websocket发送消息！！！大小[%0]").arg(nSendSize));
		}
		m_tcpSocketMapMutex.unlock();
		return true;
	}

	TcpServer::~TcpServer()
	{
		p_checkSocketState->stop();
		delete p_checkSocketState;
		//this->terminate();
		m_tcpSocketMapMutex.lock();
		m_tcpSocketMap.clear();
		m_tcpSocketMapMutex.unlock();
	}

	Tcp::TcpSocket *TcpServer::getTcpSocket(const QString &strID)
	{
		auto it = m_tcpSocketMap.find(strID);
		if (it != m_tcpSocketMap.end())
		{
			return it->second;
		}
		return  nullptr;
	}
}

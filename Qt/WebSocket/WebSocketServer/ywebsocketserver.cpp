#include "ywebsocketserver.h"
namespace WebSocketServer
{
	YWebSocketServer::YWebSocketServer(
		const QString &modelname, 
		const QString &ip, 
		const quint16 &port) :
		m_strModelName(modelname)
	{
		p_WebSocketServer = new QWebSocketServer(modelname, QWebSocketServer::NonSecureMode);
		p_WebSocketServer->listen(QHostAddress(ip), port);
		QObject::connect(p_WebSocketServer, &QWebSocketServer::newConnection, [&]()
		{
			
			QString strWebSocketID = Tool::Tools::getID();
			WebSocket::YWebSocket *websocket = new WebSocket::YWebSocket(strWebSocketID, 
			p_WebSocketServer->nextPendingConnection());

			//websocket 枷锁 防止程序出错
			m_WebSocketMapMutex.lock();
			m_WebSocketMap[strWebSocketID] = websocket;
			m_WebSocketMapMutex.unlock();

			QObject::connect(websocket, &WebSocket::YWebSocket::receiveTextMessage, [&](const QString &id, const QString &message)
			{
				emit receiveTextMessage(id, message);
			});
		});

	}

	bool YWebSocketServer::changeWebSocketName(
		const QString &waitchangeid, 
		const QString &changname
	)
	{
		m_WebSocketMapMutex.lock();
		auto it = m_WebSocketMap.find(waitchangeid);
		if (it != m_WebSocketMap.end())
		{
			
			WebSocket::YWebSocket *websocket = it->second;
			websocket->setID(changname);
			m_WebSocketMap.erase(it);
			m_WebSocketMap[changname] = websocket;
			m_WebSocketMapMutex.unlock();
			return true;

		}
		else
		{
			Log("YWebSocketServer::changeWebSocketName 未找到待改变的节点");
		}
		m_WebSocketMapMutex.unlock();
		return false;
	}

	bool YWebSocketServer::sendTextMessage(
		const QString &name, 
		const QString &message
	)
	{
		m_WebSocketMapMutex.lock();
		auto it = m_WebSocketMap.find(name);
		if (it != m_WebSocketMap.end())
		{
			it->second->sendTextMessage(message);
			Log(tr("[%0]socket发送[%1]成功！！！").arg(name).arg(message));
		}
		else
		{
			Log("YWebSocketServer::sendTextMessage 未找到待改变的节点");
		}
		m_WebSocketMapMutex.unlock();
		return true;
	}

	void YWebSocketServer::run()
	{
		while (!p_threadsemaphore.tryAcquire(1, 500))
		{
			m_WebSocketMapMutex.lock();
			auto it = m_WebSocketMap.begin();
			while (it != m_WebSocketMap.end())
			{
				WebSocket::YWebSocket *websocket = it->second;
				if (websocket->state() == QAbstractSocket::ClosingState || websocket->state() == QAbstractSocket::UnconnectedState)
				{
					websocket->getWebSocket()->close();
					m_WebSocketMap.erase(it++);
					delete websocket;						//整个删除这个节点
				}
				else
				{
					it++;
				}
			}
			m_WebSocketMapMutex.unlock();
		}
	}

	// 向所有的websocket发送消息
	bool YWebSocketServer::sendTextToAll(
		const QString &message
	)
	{
		m_WebSocketMapMutex.lock();
		for (auto it = m_WebSocketMap.begin(); it != m_WebSocketMap.end(); it++)
		{
			it->second->sendTextMessage(message);
			//Log("向所有的websocket发送消息！！！");
		}
		m_WebSocketMapMutex.unlock();
		return true;
	}

	YWebSocketServer::~YWebSocketServer() 
	{
		this->terminate();
		m_WebSocketMapMutex.lock();
		m_WebSocketMap.clear();
		m_WebSocketMapMutex.unlock();
	}

	WebSocket::YWebSocket *YWebSocketServer::getWebSocket(const QString &strID)
	{
		auto it = m_WebSocketMap.find(strID);
		if (it != m_WebSocketMap.end())
		{
			return it->second;
		}
		return  nullptr;
	}

}

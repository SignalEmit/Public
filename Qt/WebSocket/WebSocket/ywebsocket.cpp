#include "ywebsocket.h"
namespace WebSocket
{
	YWebSocket::YWebSocket(
		const QString &id, 
		QWebSocket *websocket
	) : m_strID(id)
	{
		p_WebSocket = websocket;
		connect(p_WebSocket, &QWebSocket::textMessageReceived, [&](const QString &message)
		{
			emit receiveTextMessage(m_strID, message);
		});

		connect(p_WebSocket, &QWebSocket::connected, [&]()
		{
			emit connectFinish();
		});

	}

	QString YWebSocket::getStatus()
	{
		if (p_WebSocket->state() == QAbstractSocket::ConnectedState)
		{
			return "连接正常 ";
		}
		else
		{
			return tr("状态未知code号为%0 ").arg(p_WebSocket->state());
		}
	}

	YWebSocket::YWebSocket(
		const QString &id, 
		const QString &url
	):m_strID(id),m_strUrl(url)
	{
		this->repeatedlyDeinit();
		this->repeatedlyInit();

	}

	bool YWebSocket::repeatedlyDeinit()
	{
		if (p_WebSocket != nullptr)
		{
			delete p_WebSocket;
			p_WebSocket = nullptr;
		}

		if (p_CheckStatusTimer != nullptr)
		{
			p_CheckStatusTimer->stop();
			delete p_CheckStatusTimer;
			p_CheckStatusTimer = nullptr;
		}
		return true;
	}

	bool YWebSocket::repeatedlyInit()
	{
		if (p_WebSocket == nullptr)
		{
			p_WebSocket = new QWebSocket;
			p_WebSocket->open(m_strUrl);
			connect(p_WebSocket, &QWebSocket::textMessageReceived, [&](const QString &message)
			{
				emit receiveTextMessage(m_strID, message);
			});

			connect(p_WebSocket, &QWebSocket::connected, [&]()
			{
				emit connectFinish();
			});
		}
		
		if (p_CheckStatusTimer == nullptr)
		{
			p_CheckStatusTimer = new QTimer;
			connect(p_CheckStatusTimer, &QTimer::timeout, [&]()
			{
				// 定时器关闭时重连
				if (p_WebSocket->state() == QAbstractSocket::ClosingState || p_WebSocket->state() == QAbstractSocket::UnconnectedState)
				{
					Log("websocket尝试重连 YWebSocket::YWebSocket");
					this->repeatedlyDeinit();
					this->repeatedlyInit();
				}
			});
			p_CheckStatusTimer->start(10 * 1000);							//	10s检测一次
		}
		return true;
	}

	QString YWebSocket::getID()
	{
		return m_strID;
	}

	QAbstractSocket::SocketState YWebSocket::state()
	{
		return p_WebSocket->state();
	}

	QWebSocket *YWebSocket::getWebSocket()
	{
		return p_WebSocket;
	}

	bool YWebSocket::sendTextMessage(const QString &message)
	{
		qint64 qint_asd = p_WebSocket->sendTextMessage(message);
		Log(tr("发送的数据量：%0").arg(qint_asd));
		return true;
	}

	bool YWebSocket::setID(const QString &strID)
	{
		m_strID = strID;
		return true;
	}

	YWebSocket::~YWebSocket() 
	{
		if (p_CheckStatusTimer != nullptr)
		{
			delete p_CheckStatusTimer;
			p_CheckStatusTimer = nullptr;
		}
		delete p_WebSocket;
	}

}


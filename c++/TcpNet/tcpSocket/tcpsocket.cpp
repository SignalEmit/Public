#include "tcpsocket.h"
const QString IP="127.0.0.1";
namespace Tcp
{
	// 本tcpsocket主要接收socketserver过来的数据
	TcpSocket::TcpSocket(
		const QString &id,
		QTcpSocket *tcpSocket
	):m_strID(id), m_blockSize(0)
	{
		p_tcpSocket = tcpSocket;
		connect(p_tcpSocket, &QTcpSocket::readyRead, [&]()
		{
			receiveTcpMessage();
		});
		connect(p_tcpSocket, &QTcpSocket::connected, [&]()
		{
			emit connectFinish();
		});
	}

	// 本tcpsocket主要是自己启动
	TcpSocket::TcpSocket(
		const QString &id,
		const QString &ip,
		const quint16 &port
	):m_strID(id), m_strIP(ip), m_nPort(port), m_blockSize(0)
	{
		this->repeatedlyDeinit();
		this->repeatedlyInit();
	}

	bool TcpSocket::repeatedlyDeinit()
	{
		if (p_tcpSocket != nullptr)
		{
			disconnect(p_tcpSocket, 0, 0, 0);
			delete p_tcpSocket;
			p_tcpSocket = nullptr;
		}

		if (p_CheckStatusTimer != nullptr)
		{
			p_CheckStatusTimer->stop();
			delete p_CheckStatusTimer;
			p_CheckStatusTimer = nullptr;
		}
		return true;
	}

	bool TcpSocket::repeatedlyInit()
	{
		if (p_tcpSocket == nullptr)
		{
			p_tcpSocket = new QTcpSocket;
			connect(p_tcpSocket, &QTcpSocket::readyRead, [&]()
			{
				receiveTcpMessage();
			});
			connect(p_tcpSocket, &QTcpSocket::connected, [&]()
			{
				emit connectFinish();
			});
			p_tcpSocket->abort();                             
			p_tcpSocket->connectToHost(QHostAddress(m_strIP), m_nPort);
		}

		if (p_CheckStatusTimer == nullptr)
		{
			p_CheckStatusTimer = new QTimer;
			connect(p_CheckStatusTimer, &QTimer::timeout, [&]()
			{
				// 强制拿数据
				Log(tr("缓冲区数据[%0]").arg(p_tcpSocket->bytesAvailable()));
				receiveTcpMessage();

				// 定时器关闭时重连
				if (p_tcpSocket->state() == QAbstractSocket::ClosingState || p_tcpSocket->state() == QAbstractSocket::UnconnectedState)
				{
					Log("tcpSocket尝试重连 TcpSocket::repeatedlyInit");
					this->repeatedlyDeinit();
					this->repeatedlyInit();
				}
			});
			p_CheckStatusTimer->start(300);							//	5s检测一次
		}
		return true;
	}

	// 获取id
	QString TcpSocket::getID()
	{
		return m_strID;
	}

	QString TcpSocket::getStatus()
	{
		if (p_tcpSocket->state() == QAbstractSocket::ConnectedState)
		{
			return "连接正常 ";
		}
		else
		{
			return tr("状态未知code号为%0 ").arg(p_tcpSocket->state());
		}
	}

	bool TcpSocket::setID(const QString &id)
	{
		m_strID = id;
		return true;
	}

	qint64 TcpSocket::sendTcpMessage(const QString &str)
	{
		QByteArray ByteArray; //用于暂存我们要发送的数据
		QDataStream out(&ByteArray, QIODevice::WriteOnly);
		out << (quint16)0;
		out << str.toUtf8();
		out.device()->seek(0);
		out << (quint16)(ByteArray.size() - sizeof(quint16));
		return p_tcpSocket->write(ByteArray);
	}


	// 获取缓冲区大小
	quint64 TcpSocket::getReadBufferSize()
	{
		return p_tcpSocket->readBufferSize();
	}

	void TcpSocket::receiveTcpMessage()
	{
		QDataStream in(p_tcpSocket);
		in.setVersion(QDataStream::Qt_5_9);

		if (m_blockSize == 0)
		{
			if (p_tcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
			in >> m_blockSize;
		}
		if (p_tcpSocket->bytesAvailable() < m_blockSize) return;
		if (p_tcpSocket->bytesAvailable() >= m_blockSize)
		{
			in >> strMessage;
			m_blockSize = 0;
			emit receiveTextMessage(m_strID, strMessage);
			QByteArray message;
			strMessage = message;
		}
		
	}

	QAbstractSocket::SocketState TcpSocket::state()
	{
		return p_tcpSocket->state();
	}

}

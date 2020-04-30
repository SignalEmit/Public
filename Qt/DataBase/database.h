#pragma once
#include <QSqlDatabase>
#include "Public\Log\log.h"
#include <QThread>
#include <QSemaphore>
#include <queue>
#include <QMutex>
#include <QSqlQuery>
#include <QFile>

namespace DataBase
{
	class DataBase : public QThread
	{
	public:
		DataBase(const QString &strTableName,const QString &createsql);
		~DataBase();
	public:
		// 插入SQL
		bool pushSql(const QString &sql);
		// 返回数库指针
		QSqlDatabase *getDataBase();
		// 事务提交
		bool pushBatch(const QString &sql);
		// 开启事务
		bool startBatchCommit();
		// 创建表
		bool creatTable(const QString &sql);
		// 返回事务队列长度
		size_t getQueueSize()
		{
			return q_BatchCommitQueue.size();
		}
		// 数据库打开 另外带数据锁
		bool open();
		// 数据库关闭,另外关闭锁
		bool close();
	protected:
		void run();
	private:
		int nID;
		QSqlDatabase p_db;
		QSemaphore *p_ThreadSemaphore;
		std::queue<QString> q_SqlQueue;
		std::queue<QString> q_BatchCommitQueue;
		QMutex m_Mutex;
	};

}

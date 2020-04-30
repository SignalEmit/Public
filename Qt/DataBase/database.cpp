#include "database.h"
namespace DataBase
{
	DataBase::DataBase(const QString &strTableName,const QString &createsql)
	{
		static int id = 0;

		if (QSqlDatabase::contains(QString::number(id)))
			p_db = QSqlDatabase::database(QString::number(id));
		else
			p_db = QSqlDatabase::addDatabase("QSQLITE", QString::number(id));

		nID = id;
		id++;

		QFile file(strTableName);
		if (!file.exists())
		{
			p_db.setDatabaseName(strTableName);
			if (!createsql.isEmpty())
			{
				this->pushSql(createsql);
			}
		}
		p_db.setDatabaseName(strTableName);
		p_ThreadSemaphore = new QSemaphore;
	}

	bool DataBase::creatTable(const QString &sql)
	{
		if (p_db.open())
		{
			QSqlQuery sqlexec(p_db);
			if (sqlexec.exec(sql))
			{
				Log("DataBase::creatTable执行成功！！！SQL [" + sql + "]执行成功");
			}
			else
			{
				Log("DataBase::creatTable()数据插入失败！！！");
			}

		}
		else
		{
			Log("DataBase::creatTable()数据插入失败！！！[数据库打开失败]");
		}
		p_db.close();

		return true;
	}

	bool DataBase::open()
	{
		m_Mutex.lock();
		p_db.open();
		return true;
	}

	bool DataBase::close()
	{
		p_db.close();
		m_Mutex.unlock();
		return true;
	}


	void DataBase::run()
	{
		while (!p_ThreadSemaphore->tryAcquire(1, 1))
		{
			// 上锁解锁
			m_Mutex.lock();
			while (!q_SqlQueue.empty())
			{
				if (p_db.open())
				{
					QString strSql = q_SqlQueue.front();
					q_SqlQueue.pop();
					QSqlQuery sqlexec(p_db); 
					if (sqlexec.exec(strSql))
					{
						Log("sql["+ strSql +"]执行成功");
						Log("数据库执行成功！！！");
					}
					else
					{
						Log("DataBase::run()数据插入失败！！！");
					}
					
				}
				else
				{
					Log("DataBase::run()数据插入失败！！！[数据库打开失败]");
				}
				p_db.close();
			}
			m_Mutex.unlock();
		}
	}

	bool DataBase::pushSql(const QString &sql)
	{
		Log(sql);
		m_Mutex.lock();
		q_SqlQueue.push(sql);
		m_Mutex.unlock();
		return true;
	}

	bool DataBase::pushBatch(const QString &sql)
	{
		m_Mutex.lock();
		q_BatchCommitQueue.push(sql);
		m_Mutex.unlock();
		return true;
	}

	bool DataBase::startBatchCommit()
	{
		if (q_BatchCommitQueue.empty())
		{
			return false;
		}
		m_Mutex.lock();
		if (p_db.open())
		{
			p_db.transaction();
			QSqlQuery query(p_db);
			while (!q_BatchCommitQueue.empty())
			{
				query.exec(q_BatchCommitQueue.front());
				q_BatchCommitQueue.pop();
			}
			if (p_db.commit())
			{
				Log("批量提交成功");
			}
			else
			{
				Log("批量提交失败");
			}
		}
		
		p_db.close();

		m_Mutex.unlock();

		return true;
	}

	QSqlDatabase *DataBase::getDataBase()
	{
		return &p_db;
	}

	DataBase::~DataBase()
	{
		this->terminate();
		while (!q_SqlQueue.empty())
		{
			q_SqlQueue.pop();
		}
		delete p_ThreadSemaphore;
	}

}

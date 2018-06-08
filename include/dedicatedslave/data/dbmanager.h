#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QHashIterator>
#include <dedicatedslave/data/models.h>

//struct dbstruct{
//    QString instName;
//};

class DbManager{
	public:
		/**
		 * @brief Destructor
		 *
		 * Close the db connection
		 */
		~DbManager();
		bool isOpen() const;
		DbManager(const QString& path);
		bool insertInst(const QString &name, const QString &, const int &);
		void printAllInst() const;
		bool createTable();
		void deleteAllInst();
		bool hasTable();
		bool dropTable();
		bool deleteInst(const QString& name);
		bool hasInstance(const QString& name) const;
		QHashIterator<QString, QStringList> deserializeData();
	private:
		QSqlDatabase dbdata;

};

#endif // DATABASEMANAGER_H

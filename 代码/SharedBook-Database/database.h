#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QHash>
#include <memory>

class QSqlRelationalTableModel;
class QSqlQuery;


class DataBase
{
public:
    static DataBase *getInstance();
    void showDataBase(QString tableName);
    void connectDataBase(QString tableName);

    QHash<QString,QString> findNetizenById(int id);
    QHash<QString,QString> findJottingById(int id);
    QHash<QString,QString> findMaterialById(int id);
    QHash<QString,QString> findCommentById(int id);

    QVector<QHash<QString, QString>> findNetizenJots(int n_id);
    QVector<QString> findRelationById(QString type,int n_id);
    QVector<QHash<QString, QString>> findCommentByJot_NetizenId(QString type,int id);
private:
    DataBase();
    virtual ~DataBase(){};
    static DataBase *dataBase;

    void initDataBase();

    QSqlRelationalTableModel *model;
    QSqlQuery *query;
};

#endif // DATABASE_H

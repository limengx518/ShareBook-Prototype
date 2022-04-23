#include "database.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QMultiMap>

DataBase* DataBase::dataBase=NULL;

DataBase::DataBase()       //链接数据库
{
    qDebug()<<QSqlDatabase::drivers();
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":shareBooks:");
    if(!db.open()){
        qDebug()<<"wrong: "<<db.lastError();
    }else{
        query=new QSqlQuery;
//        initDataBase();     //初始化数据库的数据，不重置表的话不需要去除注释

    }
}

DataBase *DataBase::getInstance()
{
    if(!dataBase){
        dataBase=new DataBase();
    }
    return dataBase;
}


//显示数据库
void DataBase::showDataBase(QString tableName)
{
    QTableView *view = new QTableView;
    view->setModel(model);
    view->setWindowTitle(tableName);
    view->show();
}

void DataBase::connectDataBase(QString tableName)
{
    model=new QSqlRelationalTableModel;
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    model->setRelation(3,QSqlRelation("Netizen","N_id",""));
//    model->setRelation(3,QSqlRelation("country","id","name"));
    model->select();
}


//从数据库中根据id找数据
QHash<QString,QString> DataBase::findNetizenById(int id)
{
    QHash<QString,QString> dbValues;
    QString id_S=QString::number(id);
    query->exec("select * from Netizen where N_id="+id_S);
    while(query->next()){
        dbValues.insert("id",query->value(0).toString());
        dbValues.insert("name",query->value(1).toString());
        dbValues.insert("aveter",query->value(2).toString());
        dbValues.insert("signal",query->value(3).toString());
    }
    return dbValues;
}

QHash<QString,QString> DataBase::findJottingById(int id)
{
    QHash<QString,QString> dbValues;
    QString id_S=QString::number(id);
    query->exec("select * from Jotting where J_id="+id_S);
    while(query->next()){
        dbValues.insert("id",query->value(0).toString());
        dbValues.insert("text",query->value(1).toString());
        dbValues.insert("date",query->value(2).toString());
        dbValues.insert("netizenId",query->value(3).toString());
        dbValues.insert("materialId",query->value(4).toString());
    }
    return dbValues;
}

QHash<QString, QString> DataBase::findMaterialById(int id)
{
    QHash<QString,QString> dbValues;
    QString id_S=QString::number(id);
    query->exec("select * from Material where M_id="+id_S);
    while(query->next()){
        dbValues.insert("id",query->value(0).toString());
        dbValues.insert("pictures",query->value(1).toString());
    }
    return dbValues;
}

QVector<QHash<QString, QString>> DataBase::findNetizenJots(int n_id)
{
    QVector<QHash<QString, QString>> values;
    QHash<QString,QString> dbValues;
    QString id_S=QString::number(n_id);
    query->exec("select * from Jotting where J_netizenId="+id_S);
    while(query->next()){
        dbValues.insert("id",query->value(0).toString());
        dbValues.insert("text",query->value(1).toString());
        dbValues.insert("date",query->value(2).toString());
        dbValues.insert("netizenId",query->value(3).toString());
        dbValues.insert("materialId",query->value(4).toString());
        values.append(dbValues);
        dbValues.clear();
    }
    return values;
}

QVector<QString> DataBase::findRelationById(QString type, int n_id)
{
    QVector<QString> values;
    QString id_S=QString::number(n_id);
    if(type=="interested"){
        query->exec("select R_netizenId from Relation where R_fansId="+id_S);
    }else{
        query->exec("select R_fansId from Relation where R_netizenId="+id_S);
    }
    while(query->next()){
        values.append(query->value(0).toString());
    }
    return values;
}

void DataBase::initDataBase()
{
//        query->exec("drop table Netizen");
//        query->exec("drop table Jotting");
//        query->exec("drop table Material");

    query->exec("create table Netizen(N_id integer not null primary key AUTOINCREMENT,N_name varchar(50),N_avater varchar(50),N_signal varchar(2000))");
    query->exec("insert into Netizen (N_name,N_avater,N_signal) values('张三','头像1','床前明月光')");
    query->exec("insert into Netizen (N_name,N_avater,N_signal) values('李四','头像2','疑是地上霜')");
    query->exec("insert into Netizen (N_name,N_avater,N_signal) values('王五','头像3','举头望明月')");
    query->exec("insert into Netizen (N_name,N_avater,N_signal) values('赵六','头像4','低头思故乡')");
    query->exec("insert into Netizen (N_name,N_avater,N_signal) values('周一','头像5','鹅鹅鹅，曲项向天歌')");

    query->exec("create table Jotting(J_id integer not null primary key AUTOINCREMENT,J_text varchar(10000),J_date varchar(100) not null,J_netizenId integer not null,J_materialId integer not null)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('假若决绝离开你','2021-09-08',1,1)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('花瓣展开三乐意地','2021-09-09',1,2)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('我已经渐渐习惯了这里','2021-09-10',1,3)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('不相信过去回不去','2021-09-11',1,4)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('想再去寻昨日回来','2021-09-12',2,5)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('剩下的却只有期待','2021-09-13',2,6)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('只留下遍地的花叶残败','2021-09-14',2,7)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('拾不起才突然发觉不甘心','2021-09-15',3,8)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('可否把走过的路在退回走一遍','2021-09-16',3,9)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('至少让这杯咖啡风味稍微变甜','2021-09-17',4,10)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('记得这种苦涩感你好像不太喜欢','2021-09-18',4,11)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('这样能否留点好感','2021-09-19',4,12)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('重新把熄灭成灰的篝火再点燃','2021-09-20',4,12)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('看一遍烟花绽放时会何其绚烂','2021-09-21',4,13)");
    query->exec("insert into Jotting (J_text,J_date,J_netizenId,J_materialId) values('散的怎么去点燃绚烂过后会变淡','2021-09-22',5,13)");

    query->exec("create table Material(M_id integer not null primary key AUTOINCREMENT,M_pictures varchar(50))");
    query->exec("insert into Material (M_pictures) values('pictures1')");
    query->exec("insert into Material (M_pictures) values('pictures2')");
    query->exec("insert into Material (M_pictures) values('pictures3')");
    query->exec("insert into Material (M_pictures) values('pictures4')");
    query->exec("insert into Material (M_pictures) values('pictures5')");
    query->exec("insert into Material (M_pictures) values('pictures6')");
    query->exec("insert into Material (M_pictures) values('pictures7')");
    query->exec("insert into Material (M_pictures) values('pictures8')");
    query->exec("insert into Material (M_pictures) values('pictures9')");
    query->exec("insert into Material (M_pictures) values('pictures10')");
    query->exec("insert into Material (M_pictures) values('pictures11')");
    query->exec("insert into Material (M_pictures) values('pictures12')");
    query->exec("insert into Material (M_pictures) values('pictures13')");
    query->exec("insert into Material (M_pictures) values('pictures14')");
    query->exec("insert into Material (M_pictures) values('pictures15')");

//    query->exec("create table Relation(R_netizenId integer not null,R_fansId integer)");
//    query->exec("insert into Relation values(1,2)");
//    query->exec("insert into Relation values(1,3)");
//    query->exec("insert into Relation values(2,3)");
//    query->exec("insert into Relation values(2,5)");
//    query->exec("insert into Relation values(3,4)");
//    query->exec("insert into Relation values(3,2)");
//    query->exec("insert into Relation values(4,5)");

//    query->exec("pragma foreign_keys = on");
}

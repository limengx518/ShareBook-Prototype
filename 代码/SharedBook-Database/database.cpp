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

QHash<QString, QString> DataBase::findCommentById(int id)
{
    QHash<QString,QString> dbValues;
    QString id_S=QString::number(id);
    query->exec("select * from Comment where C_id="+id_S);
    while(query->next()){
        dbValues.insert("id",query->value(0).toString());
        dbValues.insert("jottingId",query->value(1).toString());
        dbValues.insert("netizenId",query->value(2).toString());
        dbValues.insert("content",query->value(3).toString());
        dbValues.insert("time",query->value(4).toString());
        dbValues.insert("likeCount",query->value(5).toString());
    }
    return dbValues;
}

QVector<QHash<QString, QString>> DataBase::findNetizenJots(int n_id)
{
    QVector<QHash<QString, QString>> values;
    QHash<QString,QString> dbValues;
    QString id_S=QString::number(n_id);
    query->exec("select * from Jotting where N_id="+id_S);
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
        query->exec("select N_id from Relation where N_Fan_id="+id_S);
    }else{
        query->exec("select N_Fan_id from Relation where N_id="+id_S);
    }
    while(query->next()){
        values.append(query->value(0).toString());
    }
    return values;
}

QVector<QHash<QString, QString> > DataBase::findCommentByJot_NetizenId(QString type, int id)
{
    QVector<QHash<QString, QString>> values;
    QHash<QString,QString> dbValues;
    QString id_S=QString::number(id);
    if(type=="jotting"){
        query->exec("select * from Comment where J_id="+id_S);
    }else{
        query->exec("select * from Comment where N_id="+id_S);
    }
    while(query->next()){
        dbValues.insert("id",query->value(0).toString());
        dbValues.insert("jottingId",query->value(1).toString());
        dbValues.insert("netizenId",query->value(2).toString());
        dbValues.insert("content",query->value(3).toString());
        dbValues.insert("time",query->value(4).toString());
        dbValues.insert("likeCount",query->value(5).toString());
        values.append(dbValues);
        dbValues.clear();
    }
    return values;
}

void DataBase::initDataBase()
{
//        query->exec("drop table Netizen");
//        query->exec("drop table Jotting");
//        query->exec("drop table Material");
//        query->exec("drop table Relation");
//        query->exec("drop table Comment");

    query->exec("create table Netizen(N_id integer not null primary key AUTOINCREMENT,N_name varchar(50),N_avater varchar(50),N_signal varchar(2000))");
    query->exec("insert into Netizen (N_name,N_avater,N_signal) values('张三','头像1','床前明月光')");
    query->exec("insert into Netizen (N_name,N_avater,N_signal) values('李四','头像2','疑是地上霜')");
    query->exec("insert into Netizen (N_name,N_avater,N_signal) values('王五','头像3','举头望明月')");
    query->exec("insert into Netizen (N_name,N_avater,N_signal) values('赵六','头像4','低头思故乡')");

    query->exec("create table Jotting(J_id integer not null primary key AUTOINCREMENT,J_text varchar(10000),J_date varchar(100) not null,N_id integer not null,M_Id integer not null)");
    query->exec("insert into Jotting (J_text,J_date,N_id,M_Id) values('假若决绝离开你','2021-09-08',1,1)");
    query->exec("insert into Jotting (J_text,J_date,N_id,M_Id) values('花瓣展开三乐意地','2021-09-09',1,2)");
    query->exec("insert into Jotting (J_text,J_date,N_id,M_Id) values('我已经渐渐习惯了这里','2021-09-10',1,3)");
    query->exec("insert into Jotting (J_text,J_date,N_id,M_Id) values('不相信过去回不去','2021-09-11',2,4)");
    query->exec("insert into Jotting (J_text,J_date,N_id,M_Id) values('想再去寻昨日回来','2021-09-12',2,5)");
    query->exec("insert into Jotting (J_text,J_date,N_id,M_Id) values('剩下的却只有期待','2021-09-13',3,6)");
    query->exec("insert into Jotting (J_text,J_date,N_id,M_Id) values('只留下遍地的花叶残败','2021-09-14',3,7)");
    query->exec("insert into Jotting (J_text,J_date,N_id,M_Id) values('拾不起才突然发觉不甘心','2021-09-15',4,8)");


    query->exec("create table Material(M_id integer not null primary key AUTOINCREMENT ,M_content varchar(50))");
    query->exec("insert into Material (M_content) values('图片1,图片2,音频1')");
    query->exec("insert into Material (M_content) values('图片3,图片4,图片5')");
    query->exec("insert into Material (M_content) values('图片5,图片6,图片7,图片8,图片9')");
    query->exec("insert into Material (M_content) values('图片10,音频2')");
    query->exec("insert into Material (M_content) values('视频1')");
    query->exec("insert into Material (M_content) values('视频2')");
    query->exec("insert into Material (M_content) values('图片3,图片12,图片13')");
    query->exec("insert into Material (M_content) values('图片2，音频3')");

    query->exec("create table Relation(N_id integer not null,N_Fan_id integer)");
    query->exec("insert into Relation values(1,2)");
    query->exec("insert into Relation values(1,3)");
    query->exec("insert into Relation values(2,3)");
    query->exec("insert into Relation values(2,4)");
    query->exec("insert into Relation values(3,4)");
    query->exec("insert into Relation values(4,1)");

    query->exec("create table Comment(C_id integer not null primary key AUTOINCREMENT,J_id integer not null,N_id integer not null,C_content varchar(5000) not null,C_time varchar(50) not null,C_likeCount  int)");
    query->exec("insert into Comment (J_id,N_id,C_content,C_time,C_likeCount) values(1,1,'不错哟','2022-02-08',5)");
    query->exec("insert into Comment (J_id,N_id,C_content,C_time,C_likeCount) values(1,2,'非常棒，已安利！！！','2022-02-09',6)");
    query->exec("insert into Comment (J_id,N_id,C_content,C_time,C_likeCount) values(2,3,'绝绝子','2022-02-10',4)");
    query->exec("insert into Comment (J_id,N_id,C_content,C_time,C_likeCount) values(2,4,'棒棒哒','2022-02-11',5)");
    query->exec("insert into Comment (J_id,N_id,C_content,C_time,C_likeCount) values(3,2,'好听！','2022-02-12',2)");
    query->exec("insert into Comment (J_id,N_id,C_content,C_time,C_likeCount) values(4,3,'没有之前的好听！','2022-02-13',3)");
    query->exec("insert into Comment (J_id,N_id,C_content,C_time,C_likeCount) values(5,1,'什么时候有下一个？','2022-02-14',12)");
    query->exec("insert into Comment (J_id,N_id,C_content,C_time,C_likeCount) values(6,4,'加油呀','2022-02-15',5)");
    query->exec("insert into Comment (J_id,N_id,C_content,C_time,C_likeCount) values(7,2,'赞赞赞','2022-02-16',3)");
    query->exec("insert into Comment (J_id,N_id,C_content,C_time,C_likeCount) values(8,3,'牛牛牛!','2022-02-17',6)");

//    query->exec("pragma foreign_keys = on");
}

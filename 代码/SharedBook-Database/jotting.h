#ifndef JOTTING_H
#define JOTTING_H

#include <QString>
#include <QDebug>
#include <QVector>
#include "comment.h"
#include "commentbroker.h"

class MaterialBroker;
class Netizen;
class Material;
class JottingBroker;
class NetizenBroker;
class CommentBroker;

class Jotting
{
public:
    Jotting();
    Jotting(int id,QString time,QString text,Netizen *publisher=nullptr,Material *material=nullptr);
    Jotting(QString time,QString text,Netizen *publisher=nullptr,Material *material=nullptr);

    void getJotDig(NetizenBroker *nb,MaterialBroker *mb,JottingBroker * jb);
    void setMaterial(Material *material);

    void getTheJotDetail(NetizenBroker*nb,CommentBroker* cb);

    Netizen getPublisher();
    void setPublisher(Netizen *publisher);
    void setComment(QVector<Comment*> comments);

    int getID();
    void setId(int id);
    QString getText();
    QString getTime();


    void changeMaterial();
    void addNewComment(Comment* comment);
private:
    int m_id=0;
    QString m_time;
    QString m_text;

    Netizen *m_publisher;
    Material *m_material;
    QVector<Comment*> m_comments;
};

#endif // JOTTING_H

#ifndef MATERIAL_H
#define MATERIAL_H

#include <QString>
#include <QVector>
#include <QDebug>

class Jotting;

class Material
{
public:
    Material(){}
    Material(int id,QString pictures);
    void getMaterialDig();
    void setJotting(Jotting *jot);
    int getMaterialId();
private:
    Jotting *m_jotting;

    //QVector<QString> m_pictures;
    QString m_pictures;
    int m_materialid;
};

#endif // MATERIAL_H

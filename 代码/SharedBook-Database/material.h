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
    Material(int id,QString materials);

    void getMaterialDetail();
    void getMaterialDig();
    void setJotting(Jotting *jot);
    int getMaterialId();
private:
    Jotting *m_jotting;

//    QVector<QString> m_pictures;
    QString m_materials;
    int m_materialId;
};

#endif // MATERIAL_H

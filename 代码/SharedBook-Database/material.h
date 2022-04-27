#ifndef MATERIAL_H
#define MATERIAL_H

#include <QString>
#include <QVector>
#include <QDebug>

class Jotting;
class Picture;
class Audio;
class Video;

class Material
{
public:
    Material(){}
    Material(int id,QVector<Picture*> picture,Audio* audio=nullptr,Video* video=nullptr);
    Material(QVector<Picture*> picture,Audio* audio=nullptr,Video* video=nullptr);

    void getMaterialDetail();
    void getMaterialDig();
    void setJotting(Jotting *jot);
    int getMaterialId();
    void adapt();

    QVector<Picture *> getPictures();
    Audio * getAudio();
    Video * getVideo();
private:
    Jotting *m_jotting;

    QVector<Picture*> m_pictures;
    Audio* m_audio;
    Video* m_video;
//    QString m_materials;
    int m_materialId;
};

#endif // MATERIAL_H

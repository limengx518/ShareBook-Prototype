#ifndef JOTTINGSOCIALCONTROL_H
#define JOTTINGSOCIALCONTROL_H

#include <QVector>

class Netizen;
class Jotting;
class NetizenBroker;
class JottingBroker;
class CommentBroker;
class MaterialBroker;
class Material;


class JottingSocialControl
{
public:
    JottingSocialControl();
    void login(int id);
    void pushJottings();
    void checkOneJot(int index);
    Jotting *findJot(int index);
    void commentTheJot(QString content);
    void sendFollowRequest();



    void sendChooseMaterialReq();
    void chooseMaterialInterface();
    void sendNewJottingContents(QString content);
    void sendPreviewRequest();
    void sendAdaptMaterialReq();
    void sendPublishRequest();

//    bool checkMaterialRationality(QString path){};
//    QString chooseMaterial(){};
private:
    NetizenBroker *nb;
    JottingBroker *jb;
    CommentBroker *cb;
    MaterialBroker *mb;
    Netizen *m_netizen;

    //Jotting buffer storage in here
    QVector<Jotting* > m_jottings;
    Jotting* m_scanJotting;
    Jotting *m_previewJotting;

    Material *m_previewMaterial;
};

#endif // JOTTINGSOCIALCONTROL_H

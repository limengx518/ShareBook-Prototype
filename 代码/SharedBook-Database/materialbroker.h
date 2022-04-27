#ifndef MATERIALBROKER_H
#define MATERIALBROKER_H

#include "material.h"
#include <database.h>

class MaterialBroker
{
public:
    static MaterialBroker* getInstance(){
        if(materialBroker==nullptr){
            materialBroker=new MaterialBroker();
        }
        return materialBroker;
    }

    Material* findMaterialById(int id)const;//findJoNetizenById()
    Picture *findPictureById(int picture_id);
    Audio *findAudioById(int audio_id);
    Video *findVideoById(int video_id);

    Material* findJotMaterial(int jotting_id);
    void addNewJotMaterial(Material *material,int j_id) const;   //修改
private:
    MaterialBroker(){};
    static MaterialBroker *materialBroker;
    DataBase *db=DataBase::getInstance();
};

#endif // MATERIALBROKER_H

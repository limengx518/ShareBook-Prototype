#ifndef MATERIALBROKER_H
#define MATERIALBROKER_H

#include "broker.h"
#include "material.h"
#include "jotting.h"
#include <vector>

class MaterialBroker : public Broker
{
public:
    MaterialBroker();
    Material* findMaterialByID(int jottingId);
    void setMaterials(std::vector<Material> materials);
private:
    std::vector<Material> m_materials;
};

#endif // MATERIALBROKER_H

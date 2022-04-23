#include "materialbroker.h"

MaterialBroker::MaterialBroker()
{

}

Material *MaterialBroker::findMaterialByID(int jottingId)
{

}

void MaterialBroker::setMaterials(std::vector<Material> materials)
{
    this->m_materials = materials;
}

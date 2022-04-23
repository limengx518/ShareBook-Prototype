#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <vector>

class Jotting;

class Material
{
public:
    Material(int id,std::vector<std::string> pictures);
    void getMaterialDig();
    void setJotting(Jotting *jot);
    int getMaterialId();
private:
    Jotting *m_jotting;
    std::vector<std::string> m_pictures;
    int m_materialid;
};

#endif // MATERIAL_H

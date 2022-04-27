#include "picture.h"

Picture::Picture(int id, QString content)
{
    this->m_pictureId = id;
    this->m_content = content;
}

Picture::Picture(QString content)
{
    this->m_content = content;
}

QString Picture::getContent()
{
    return m_content;
}

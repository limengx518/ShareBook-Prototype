#include "video.h"

Video::Video(int id, QString content)
{
    this->m_content = content;
    this->m_videoId = id;
}

Video::Video(QString content)
{
    this->m_content = content;
}

QString Video::getContent()
{
    return m_content;
}

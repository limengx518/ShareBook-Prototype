#include "audio.h"

Audio::Audio(int id, QString content)
{
    this->m_audioId = id;
    this->m_content = content;
}

Audio::Audio(QString content)
{
    this->m_content = content;
}

QString Audio::getContent()
{
    return m_content;
}

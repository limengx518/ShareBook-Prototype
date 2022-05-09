#ifndef AUDIO_H
#define AUDIO_H

#include <QString>

class Audio
{
public:
    Audio(int id,QString content);
    Audio(QString content);
    QString getContent();
private:
    QString m_content;
    int m_audioId;
};

#endif // AUDIO_H

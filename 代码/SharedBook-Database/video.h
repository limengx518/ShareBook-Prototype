#ifndef VIDEO_H
#define VIDEO_H

#include <QString>

class Video
{
public:
    Video(int id,QString content);
    Video(QString content);
    QString getContent();
private:
    int m_videoId;
    QString m_content;
};

#endif // VIDEO_H

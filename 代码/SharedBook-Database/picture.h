#ifndef PICTURE_H
#define PICTURE_H

#include <QString>


class Picture
{
public:
    Picture(int id,QString content);

    Picture(QString content);
    QString getContent();
private:
    QString m_content;
    int m_pictureId;
};

#endif // PICTURE_H

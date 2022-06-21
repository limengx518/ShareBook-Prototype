#ifndef ROUNDIMAGE_H
#define ROUNDIMAGE_H

#include <QQuickPaintedItem>

class RoundImage:public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sourceChanged)
public:
    RoundImage(QQuickItem *parent=nullptr);
    QString getSource()const;
    void setSource(const QString &source);

    void paint(QPainter *painter);
signals:
    void sourceChanged(const QString source);
private:
    QString m_source;
};

#endif // ROUNDIMAGE_H

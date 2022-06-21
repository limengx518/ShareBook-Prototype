#include "roundimage.h"
#include <QPainter>
#include <QPainterPath>

RoundImage::RoundImage(QQuickItem *parent):
    QQuickPaintedItem(parent)
{
    m_source=QString();
}

QString RoundImage::getSource() const
{
    return m_source;
}

void RoundImage::setSource(const QString &source)
{
    m_source=source;
    emit sourceChanged(m_source);
}

void RoundImage::paint(QPainter *painter)
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing,true);
    QPixmap pixmap(m_source);
    QPainterPath path;
    path.addEllipse(0,0,width(),height());
    painter->setClipPath(path);
    painter->drawPixmap(QRect(0,0,static_cast<int>(width()),static_cast<int>(height())),pixmap);
    painter->restore();
}

#ifndef PERSONALUICONTROL_H
#define PERSONALUICONTROL_H

#include <QObject>
#include <nlohmann/json.hpp>
#include "netizen.h"

class PersonalUIControl:public QObject
{
    Q_OBJECT  
    Q_PROPERTY(QString netizenId READ getNetizenId WRITE setNetizenId NOTIFY netizenIdChanged)
    Q_PROPERTY(QString sign READ getSign WRITE setSign NOTIFY signChanged)
    Q_PROPERTY(QString netizenInfo READ getNetizenInfo WRITE setNetizenInfo NOTIFY netizenInfoChanged)
public:
    explicit PersonalUIControl(QObject *parent = nullptr);

    void setNetizenId(const QString &id);
    QString getNetizenId()const;

    void setSign(const QString &sign);
    QString getSign()const;

    void setNetizenInfo(const QString &netizenInfo);
    QString getNetizenInfo()const;

    Q_INVOKABLE void initData();
signals:
    void netizenIdChanged(const QString id);
    void signChanged(const QString sign);
    void netizenInfoChanged(const QString jottings);

//public slots:
//    void initData();

private:
//    nlohmann::json m_netizenInfo;

    QString m_id;
    QString m_sign;
    QString m_netizenInfo;

};

#endif // PERSONALUICONTROL_H

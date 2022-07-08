#include "personaluicontrol.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "netizenbroker.h"
#include "jottingsocialcontrol.h"

PersonalUIControl::PersonalUIControl(QObject *parent):
    QObject(parent)
{
    NetizenBroker * broker=NetizenBroker::getInstance();
    broker->initDataBase();

}

void PersonalUIControl::setNetizenId(const QString &id)
{
    m_id=id;
}

QString PersonalUIControl::getNetizenId() const
{
    return m_id;
}

void PersonalUIControl::setSign(const QString &sign)
{
    m_sign=sign;
    emit signChanged(m_sign);
}

QString PersonalUIControl::getSign() const
{
    return m_sign;
}

void PersonalUIControl::setNetizenInfo(const QString &netizenInfo)
{
    m_netizenInfo=netizenInfo;
    emit netizenInfoChanged(m_netizenInfo);
}

QString PersonalUIControl::getNetizenInfo() const
{
    return m_netizenInfo;
}

void PersonalUIControl::initData()
{

    nlohmann::json netizenInfo=JottingSocialControl::getInstance()->login("1");
//    m_nikeName="Sofia";
    m_sign="smile pasta pasta";
    m_netizenInfo=QString::fromStdString(netizenInfo.dump());
}


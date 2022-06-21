#include "personaluicontrol.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

PersonalUIControl::PersonalUIControl(QObject *parent):
    QObject(parent),m_nickName(""),m_sign("")
{

}

void PersonalUIControl::setNickName(const QString &nickName)
{
    m_nickName=nickName;
}

QString PersonalUIControl::getNickName() const
{
    return m_nickName;
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

void PersonalUIControl::setJottings(const QString &jottings)
{
    m_jottings=jottings;
    emit jottingsChanged(m_jottings);
}

QString PersonalUIControl::getJottings() const
{
    return m_jottings;
}

void PersonalUIControl::setInterest(const QString &interest)
{
    m_interest=interest;
    emit interestChanged(m_interest);
}

QString PersonalUIControl::getInterest() const
{
    return m_interest;
}

void PersonalUIControl::setFans(const QString &fans)
{
    m_fans=fans;
    emit fansChanged(m_fans);
}

QString PersonalUIControl::getFans() const
{
    return m_fans;
}

void PersonalUIControl::setJottingCount(const QString &jottingCount)
{
    m_jotting_count=jottingCount;
    emit jottingCountChanged(m_jotting_count);
}

QString PersonalUIControl::getJottingCount() const
{
    return m_jotting_count;
}

void PersonalUIControl::setInterestCount(const QString &interestCount)
{
    m_interest_count=interestCount;
    emit interestCountChanged(m_interest_count);
}

QString PersonalUIControl::getInterestCount() const
{
    return m_interest_count;
}

void PersonalUIControl::setFanCount(const QString &fanCount)
{
    m_fan_count=fanCount;
    emit fanCountChanged(m_fan_count);
}

QString PersonalUIControl::getFanCount() const
{
    return m_fan_count;
}

void PersonalUIControl::initData()
{
    m_nickName="Sofia";
    m_sign="smile pasta pasta";

    QJsonObject jot_json1;
    jot_json1.insert("content","We could leave the Christmas");
    jot_json1.insert("pic_path","pictures1");
    jot_json1.insert("file","qrc:/qml/qml/JotDetailPage.qml");
    QJsonObject jot_json2;
    jot_json2.insert("content","This is our place, we make the rules");
    jot_json2.insert("pic_path","pictures2");
    jot_json2.insert("file","qrc:/qml/qml/JotDetailPage.qml");
    QJsonObject jot_json3;
    jot_json3.insert("content","And there's a dazzling haze");
    jot_json3.insert("pic_path","pictures3");
    jot_json3.insert("file","qrc:/qml/qml/JotDetailPage.qml");
    QJsonArray jotting;
    jotting.append(QJsonValue(jot_json1));
    jotting.append(QJsonValue(jot_json2));
    jotting.append(QJsonValue(jot_json3));
    m_jotting_count=QString::number(jotting.count());
    QJsonDocument jot_doc(jotting);
    m_jottings=QString(jot_doc.toJson(QJsonDocument::Indented));

    QJsonObject interest_json1;
    interest_json1.insert("nickName","Alice");
    interest_json1.insert("file","qrc:/qml/qml/PersonalPage.qml");
    QJsonObject interest_json2;
    interest_json2.insert("nickName","Susan");
    interest_json2.insert("file","qrc:/qml/qml/PersonalPage.qml");
    QJsonObject interest_json3;
    interest_json3.insert("nickName","Mark");
    interest_json3.insert("file","qrc:/qml/qml/PersonalPage.qml");
    QJsonArray interest;
    interest.append(QJsonValue(interest_json1));
    interest.append(QJsonValue(interest_json2));
    interest.append(QJsonValue(interest_json3));
    m_interest_count=QString::number(interest.count());
    QJsonDocument interest_doc(interest);
    m_interest=QString(interest_doc.toJson(QJsonDocument::Indented));

    QJsonObject fan_json1;
    fan_json1.insert("nickName","Alice");
    fan_json1.insert("file","qrc:/qml/qml/PersonalPage.qml");
    QJsonObject fan_json2;
    fan_json2.insert("nickName","Joey");
    fan_json2.insert("file","qrc:/qml/qml/PersonalPage.qml");
    QJsonObject fan_json3;
    fan_json3.insert("nickName","Lay");
    fan_json3.insert("file","qrc:/qml/qml/PersonalPage.qml");
    QJsonArray fans;
    fans.append(QJsonValue(fan_json1));
    fans.append(QJsonValue(fan_json2));
    fans.append(QJsonValue(fan_json3));
    m_fan_count=QString::number(fans.count());
    QJsonDocument fan_doc(fans);
    m_fans=QString(fan_doc.toJson(QJsonDocument::Indented));
}


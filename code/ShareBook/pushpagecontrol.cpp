#include "pushpagecontrol.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

PushPageControl::PushPageControl(QObject *parent):
    QObject(parent)
{

}

void PushPageControl::pushRecommendJottings()
{
    json jot_json1;
    jot_json1["avatar"]="qrc:/images/images/avatar.png";
    jot_json1["nickName"]="JongHan";
    jot_json1["content"]="We could leave the Christmas";
    json picPath1;
    picPath1["path"]="qrc:/images/images/avatar.png";
    jot_json1["picPath"]={picPath1,picPath1,picPath1};

    json jot_json2;
    jot_json2["avatar"]="qrc:/images/images/avatar.png";
    jot_json2["nickName"]="Josua";
    jot_json2["content"]="This is our place, we make the rules";
    json picPath2;
    picPath2["path"]="qrc:/images/images/avatar.png";
    jot_json2["picPath"]={picPath2,picPath2};

    json jot_json3;
    jot_json3["avatar"]="qrc:/images/images/avatar.png";
    jot_json3["nickName"]="S.coups";
    jot_json3["content"]="Hot Hot fighting!";
    json picPath3;
    picPath3["path"]="qrc:/images/images/avatar.png";
    jot_json3["picPath"]={picPath3,picPath3,picPath3};

    json jottings;
    jottings["jottings"]={jot_json1,jot_json2,jot_json3};

    m_recommendJottings=QString::fromStdString(jottings.dump());
}

void PushPageControl::pushConcernedJottings()
{   
    json jot_json1;
    jot_json1["avatar"]="qrc:/images/images/avatar.png";
    jot_json1["nickName"]="Baby";
    jot_json1["content"]="We could leave the Christmas";
    json picPath1;
    picPath1["path"]="qrc:/images/images/avatar.png";
    jot_json1["picPath"]={picPath1,picPath1,picPath1};

    json jot_json2;
    jot_json2["avatar"]="qrc:/images/images/avatar.png";
    jot_json2["nickName"]="Angel";
    jot_json2["content"]="This is our place, we make the rules";
    json picPath2;
    picPath2["path"]="qrc:/images/images/avatar.png";
    jot_json2["picPath"]={picPath2,picPath2,picPath2};

    json jottings;
    jottings["jottings"]={jot_json1,jot_json2};

    m_concernedJottings=QString::fromStdString(jottings.dump());
}

void PushPageControl::pushLocalJottings()
{   
    json jot_json1;
    jot_json1["avatar"]="qrc:/images/images/avatar.png";
    jot_json1["nickName"]="Baby";
    jot_json1["content"]="We could leave the Christmas";
    json picPath1;
    picPath1["path"]="qrc:/images/images/avatar.png";
    jot_json1["picPath"]={picPath1,picPath1,picPath1};

    json jot_json2;
    jot_json2["avatar"]="qrc:/images/images/avatar.png";
    jot_json2["nickName"]="Angel";
    jot_json2["content"]="This is our place, we make the rules";
    json picPath2;
    picPath2["path"]="qrc:/images/images/avatar.png";
    jot_json2["picPath"]={picPath2,picPath2,picPath2};

    json jottings;
    jottings["jottings"]={jot_json1,jot_json2};


    m_localJottings=QString::fromStdString(jottings.dump());
}

void PushPageControl::receiveOneJotting(QString jotting_id)
{
    json jotting;
    jotting["avatar"]="qrc:/images/images/avatar.png";
    jotting["netizenName"]="NULL";
    jotting["content"]="Hello";
    jotting["likeCount"]="0";
    jotting["collectCount"]="0";
    jotting["commentCount"]="0";
    jotting["time"]="0000-00-00 00:00";

    json picPath;
    picPath["path"]="qrc:/images/images/avatar.png";
    jotting["picPath"]={picPath,picPath,picPath};

    json commend_1;
    commend_1["netizenName"]="Joey";
    commend_1["pic"]="qrc:/images/images/avatar.png";
    commend_1["content"]="very good!";
    commend_1["time"]="2022-06-01 22:12";
    json commend_2;
    commend_2["netizenName"]="Kacy";
    commend_2["pic"]="qrc:/images/images/avatar.png";
    commend_2["content"]="I like it!";
    commend_2["time"]="2022-06-01 14:12";
    jotting["commend"]={commend_1,commend_2};

    m_jotting=QString::fromStdString(jotting.dump());
}

void PushPageControl::setRecommendJottings(const QString &recommendJottings)
{
    m_recommendJottings=recommendJottings;
}

QString PushPageControl::getRecommendJottings() const
{
    return m_recommendJottings;
}

void PushPageControl::setConcernedJottings(const QString &concernedJottings)
{
    m_concernedJottings=concernedJottings;
}

QString PushPageControl::getConcernedJottings() const
{
    return m_concernedJottings;
}

void PushPageControl::setLocalJottings(const QString &localJottings)
{
    m_localJottings=localJottings;
}

QString PushPageControl::getLocalJottings() const
{
    return m_localJottings;
}

void PushPageControl::setJotting(const QString &jotting)
{
    m_jotting=jotting;
}

QString PushPageControl::getJotting() const
{
    return m_jotting;
}


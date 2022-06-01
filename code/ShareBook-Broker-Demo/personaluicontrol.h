#ifndef PERSONALUICONTROL_H
#define PERSONALUICONTROL_H

#include <QObject>

class PersonalUIControl:public QObject
{
    Q_OBJECT  
    Q_PROPERTY(QString nikeName READ getNikeName WRITE setNikeName NOTIFY nikeNameChanged)
    Q_PROPERTY(QString sign READ getSign WRITE setSign NOTIFY signChanged)
    Q_PROPERTY(QString jottings READ getJottings WRITE setJottings NOTIFY jottingsChanged)
    Q_PROPERTY(QString interest READ getInterest WRITE setInterest NOTIFY interestChanged)
    Q_PROPERTY(QString fans READ getFans WRITE setFans NOTIFY fansChanged)
    Q_PROPERTY(QString jottingCount READ getJottingCount WRITE setJottingCount NOTIFY jottingCountChanged)
    Q_PROPERTY(QString interestCount READ getInterestCount WRITE setInterestCount NOTIFY interestCountChanged)
    Q_PROPERTY(QString fanCount READ getFanCount WRITE setFanCount NOTIFY fanCountChanged)
public:
    explicit PersonalUIControl(QObject *parent = nullptr);

    void setNikeName(const QString &nikeName);
    QString getNikeName()const;

    void setSign(const QString &sign);
    QString getSign()const;

    void setJottings(const QString &jottings);
    QString getJottings()const;

    void setInterest(const QString &interest);
    QString getInterest()const;

    void setFans(const QString &fans);
    QString getFans()const;

    void setJottingCount(const QString &jottingCount);
    QString getJottingCount()const;

    void setInterestCount(const QString &interestCount);
    QString getInterestCount()const;

    void setFanCount(const QString &fanCount);
    QString getFanCount()const;

    Q_INVOKABLE void initData();
signals:
    void nikeNameChanged(const QString nikeName);
    void signChanged(const QString sign);
    void jottingsChanged(const QString jottings);
    void interestChanged(const QString interest);
    void fansChanged(const QString fans);
    void jottingCountChanged(const QString jottingCount);
    void interestCountChanged(const QString interestCount);
    void fanCountChanged(const QString fansCount);

//public slots:
//    void initData();

private:
    QString m_nikeName;
    QString m_sign;
    QString m_jottings;
    QString m_interest;
    QString m_fans;
    QString m_jotting_count;
    QString m_interest_count;
    QString m_fan_count;
};

#endif // PERSONALUICONTROL_H

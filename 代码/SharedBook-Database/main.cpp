#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "database.h"
#include "jottingsocialcontrol.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QTranslator translator;
//    const QStringList uiLanguages = QLocale::system().uiLanguages();
//    for (const QString &locale : uiLanguages) {
//        const QString baseName = "SharedBook-Database_" + QLocale(locale).name();
//        if (translator.load(":/i18n/" + baseName)) {
//            a.installTranslator(&translator);
//            break;
//        }
//    }

    JottingSocialControl *jsc = new JottingSocialControl();
    int account = 3;

    jsc->login(account);

    jsc->pushJottings();

    jsc->checkOneJot(2);
//    jsc->commentTheJot("呵呵呵");

//    jsc->sendChooseMaterialReq();
//    jsc->sendNewJottingContents("我与乘风归去，又恐琼楼玉宇");
//    jsc->sendPreviewRequest();
//    jsc->sendAdaptMaterialReq();
//    jsc->sendPublishRequest();


    DataBase *db=DataBase::getInstance();
//    db->connectDataBase("Netizen");
//    db->connectDataBase("Comment");
    db->connectDataBase("Relation");
//    db->connectDataBase("Jotting");
//    db->showDataBase("Netizen");
//    db->showDataBase("Comment");
    db->showDataBase("Relation");
//    db->showDataBase("Jotting");
    return a.exec();
}

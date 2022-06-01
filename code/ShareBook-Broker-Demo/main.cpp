#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "personaluicontrol.h"
#include "roundimage.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<PersonalUIControl>("UIControl",1,0,"PersonalUIControl");
    qmlRegisterType<RoundImage>("UIControl",1,0,"RoundImage");

    QQmlApplicationEngine engine;

    const QUrl url(u"qrc:/ShareBook/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}

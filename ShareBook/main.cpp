#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "imageprovider.h"
#include "personaluicontrol.h"
#include "roundimage.h"
#include "pushpagecontrol.h"
#include "publishpagecontrol.h"

ImageProvider *imageProvider = nullptr;
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    qmlRegisterType<PersonalUIControl>("UIControl",1,0,"PersonalUIControl");
    qmlRegisterType<RoundImage>("UIControl",1,0,"RoundImage");
    qmlRegisterType<PushPageControl>("UIControl",1,0,"PushPageControl");
    qmlRegisterType<PublishPageControl>("UIControl",1,0,"PublishPageControl");


    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ShareBook/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    imageProvider = new ImageProvider();

    engine.addImageProvider("photos",imageProvider);

    engine.load(url);

    return app.exec();
}

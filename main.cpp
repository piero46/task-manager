#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "authmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    AuthManager auth;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("auth", &auth);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load("qrc:/Avto.qml");

    return app.exec();
}

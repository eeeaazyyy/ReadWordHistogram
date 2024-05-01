#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringLiteral>
#include <QThread>


#include "controlbuttons.h"
#include "itemhistogram.h"
#include "texthandler.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QThread threadTHandler;
    ControlButtons ControlButs;
    TextHandler THandler;
    ItemHistogram Histogram;

    THandler.moveToThread(&threadTHandler);

    qmlRegisterType<ControlButtons>("io.qt.examples.backend", 1, 0, "ControlButton");
    qmlRegisterType<ItemHistogram>("io.qt.examples.backend", 1, 0, "Histogram");
    qmlRegisterType<TextHandler>("io.qt.examples.backend", 1, 0, "TextHandler");

    engine.rootContext()->setContextObject(&ControlButs);
    engine.rootContext()->setContextObject(&THandler);
    engine.rootContext()->setContextObject(&Histogram);



    const QUrl url(u"qrc:/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [&](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);

            // Поиск объекта ControlButtons после его загрузки
            QObject* controlButtonsObject = engine.rootObjects().first()->findChild<QObject*>("contBut");
            QObject* HistObj = engine.rootObjects().first()->findChild<QObject*>("Hist");

            if (controlButtonsObject && HistObj) {
                ControlButtons* ConButs = (ControlButtons*)controlButtonsObject;
                ItemHistogram* hist = (ItemHistogram*)HistObj;
                // Подключите сигнал к слоту в объекте THandler
                QObject::connect(ConButs, &ControlButtons::signalStart, &THandler, &TextHandler::start);
                QObject::connect(ConButs, &ControlButtons::signalSendFile, [&](QString fileName) { threadTHandler.start(QThread::NormalPriority); THandler.setSourceFile(fileName); });
                QObject::connect(ConButs, &ControlButtons::signalPause, &THandler, &TextHandler::pause, Qt::DirectConnection);
                QObject::connect(ConButs, &ControlButtons::signalResume, &THandler, &TextHandler::resume, Qt::DirectConnection);
                QObject::connect(ConButs, &ControlButtons::signalCancel, &THandler, &TextHandler::reset, Qt::DirectConnection);

                QObject::connect(ConButs, &ControlButtons::signalCancel, hist, &ItemHistogram::slotClearHistogram);
                QObject::connect(&THandler, &TextHandler::addItem, hist, &ItemHistogram::slotFillItemsHistogram);
                QObject::connect(&THandler, &TextHandler::progressChanged, ConButs, &ControlButtons::getPercentFromTotalBytes);
                QObject::connect(&THandler, &TextHandler::reseted, hist, &ItemHistogram::slotClearHistogram, Qt::DirectConnection);
                QObject::connect(&THandler, &TextHandler::reseted, [&]()
                    { if (threadTHandler.isRunning())
                {
                    
                    threadTHandler.quit();
                    threadTHandler.wait(); // Ожидание завершения потока
                }
                    else {
                   
                }
                    });
                QObject::connect(&THandler, &TextHandler::finished, &threadTHandler, &QThread::quit);

            }
            else {
                qDebug() << "ControlButtons object not found.";
            }

        }, Qt::QueuedConnection);
    //threadTHandler.start(QThread::NormalPriority);
    engine.load(url);

    return app.exec();
}
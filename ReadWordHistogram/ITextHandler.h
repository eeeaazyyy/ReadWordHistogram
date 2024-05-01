#ifndef ITEXTHANDLER_H
#define ITEXTHANDLER_H
#include <QObject>
#include <QFile>

class ITextHandler : public QObject
{
    Q_OBJECT
public:

    ITextHandler(QObject* parent) : QObject(parent){};
    virtual ~ITextHandler(){};

public:
    void reset(){};
public slots:
    //virtual void setSourceFile( QString& _srcFileName) = 0;
    virtual void start()  = 0;
    virtual void pause()  = 0;
    virtual void resume() = 0;
    virtual void resetFile(QFile& file) = 0;
signals:
    void finished();
};


#endif // ITEXTHANDLER_H

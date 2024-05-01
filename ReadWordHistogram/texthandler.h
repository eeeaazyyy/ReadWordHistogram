#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include <QObject>
#include "ITextHandler.h"



class TextHandler : public ITextHandler
{
    Q_OBJECT

public:
    TextHandler(QObject* parent = nullptr);
    ~TextHandler();
public:

    enum textHandlerState
    {
        isReset   = -1,
        isPaused  =  0,
        isResume  =  1,
        isStarted =  2

    };
public:



    int getState();
    int state;

public slots:
    void start() override;
    void pause() override;
    void resume() override;
    void resetFile(QFile& file) override;
    void setSourceFile( QString _srcFileName);
    void reset();
private:
    QString sourceFile;
signals:
    void progressChanged(qint64 bytesRead, qint64 totalBytes);
    void addItem(QVector<QPair<QString, int>> wordVector);
    void reseted();
};

#endif // TEXTHANDLER_H

#include "texthandler.h"
#include <QFile>
#include <QDebug>
#include <QRegularExpression>
#include <QThread>

TextHandler::TextHandler(QObject *parent) : ITextHandler(parent)
{
    state = 2;
    //connect(this, &TextHandler::reseted, this, &TextHandler::resetFile);
}

TextHandler::~TextHandler()
{

}

int TextHandler::getState()
{
    return state;
}

void TextHandler::setSourceFile( QString _srcFileName)
{
    sourceFile = _srcFileName;
    qDebug()<<"TextHandler setSourceFile "<< sourceFile;
}

void TextHandler::reset()
{
    state = textHandlerState::isReset;
    //emit finished();
}

void TextHandler::start()
{
    qDebug() << "TextHandler: start";
    //int nowState = getState();
    state = textHandlerState::isStarted;
    QFile file(sourceFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file for reading: " << file.errorString();
        return;
    }

    //connect(this, &TextHandler::reseted, this, &TextHandler::resetFile);

    qint64 totalBytes = file.size();
    qint64 bytesRead = 0;

    QByteArray buffer;
    QVector<QPair<QString, int>> wordVector{};
    QMap<QString, int> wordCounts;

    QRegularExpression regExp("[\\\\\\w'а-яА-ЯЁ-ё]+");


    while (!file.atEnd())
    {

        if(getState() == textHandlerState::isReset){
            qDebug()<<"get state is reset";
            file.close();
            emit finished();
            emit reset();
            QThread::currentThread()->quit();
        }

        if (getState() == textHandlerState::isPaused)
        {
            qDebug()<<"Is Paused";
            // Ожидаем некоторое время перед следующей проверкой
            QThread::currentThread()->msleep(100);
            //QThread::msleep(100);
            continue;
        }
        qDebug()<<"STATE "<< getState();
        buffer = file.readLine(100); // Чтение файла по частям
        bytesRead += buffer.size();


        QString str = QString::fromUtf8(buffer);
        QRegularExpressionMatchIterator i = regExp.globalMatch(str);

        while (i.hasNext())
        {
            emit progressChanged(bytesRead, totalBytes);

            QString word = i.next().captured().toLower();
            wordCounts[word]++;

            int value = wordCounts.value(word);

            QPair<QString, int> pair = qMakePair(word, value);
            auto it = std::find_if( wordVector.begin(), wordVector.end(),
                                    [word](const QPair<QString, int>& element){ return element.first == word;} );

            if(it != wordVector.end())
            {
                it->second = value;
            }
            else
            {
                wordVector.append(pair);
            }

            emit addItem(wordVector);
            //qDebug()<<"Add item "<< word;
        }

    }

    file.close();
    emit finished();
    qDebug()<<"emit finished";
}


void TextHandler::pause()
{

    state = textHandlerState::isPaused;
    qDebug()<<"Slot pause ; State = "<<state;
}

void TextHandler::resume()
{
    state = textHandlerState::isResume;
}


void TextHandler::resetFile(QFile &file)
{
    qDebug()<<"Slot reset";
    state = textHandlerState::isReset;
    file.close();
    emit finished();
}

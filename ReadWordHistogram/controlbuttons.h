#ifndef CONTROLBUTTONS_H
#define CONTROLBUTTONS_H


#include <QObject>


#include "itemhistogram.h"
class ControlButtons : public QObject
{

    Q_PROPERTY(int progressBarValue READ progressBarValue WRITE setProgressBValue NOTIFY progressBValueChanged)
    Q_OBJECT
    //QML_NAMED_ELEMENT(ConBut)
public:
    ControlButtons(QObject *parent = nullptr);
    ~ControlButtons();
public:
    enum stateType{
        INVALID = -1,
        ISPAUSE = 0,
        ISRUNNIN = 1
    };
    const int progressBarValue();

    ItemHistogram HistogramClass;
private:
    int m_progressValue;
    void setProgressBValue(int _value);
    QString fileName;

private:


public slots:
    void getPercentFromTotalBytes(qint64 _readBytes, qint64 _totalBytes);
    void slotSetFileName(const QUrl& _urlFile);
    void slotButStart();
    void slotButPauseResume(ControlButtons::stateType _stateType);
    void slotButCancel();
signals:
    void signalStart();
    void signalSendFile( QString _fileName);
    void signalPause();
    void signalResume();
    void signalCancel();
    void progressBValueChanged();

};

#endif // CONTROLBUTTONS_H

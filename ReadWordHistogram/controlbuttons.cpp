#include "controlbuttons.h"
#include <QUrl>
#include <QDebug>

ControlButtons::ControlButtons(QObject *parent)
    : QObject{parent}
{

}

ControlButtons::~ControlButtons()
{

}

const int ControlButtons::progressBarValue()
{
    return m_progressValue;
}

void ControlButtons::getPercentFromTotalBytes(qint64 _readBytes, qint64 _totalBytes)
{
    double value = static_cast<double>(_readBytes) / _totalBytes * 100;
    int percent = qRound(value);
    setProgressBValue(percent);
}

void ControlButtons::setProgressBValue(int _value)
{
    //qDebug()<<"setProgressBValue";
    if (m_progressValue == _value)
        return;

    m_progressValue = _value;
    emit progressBValueChanged();
}

void ControlButtons::slotSetFileName(const QUrl& _urlFile)
{

    if(!_urlFile.isLocalFile()){
            return;
    }
    fileName = _urlFile.toLocalFile();
    emit signalSendFile(fileName);
   

}

void ControlButtons::slotButStart()
{
    
    emit signalStart();


}

void ControlButtons::slotButPauseResume(ControlButtons::stateType _stateType)
{
    switch (_stateType) {
    case 0:
        emit signalPause();
        break;
    case 1:
        emit signalResume();
        break;
    default:
        qDebug()<<"Invalid state type: " << _stateType;
        break;
    }
}

void ControlButtons::slotButCancel()
{
    setProgressBValue(0);
    emit signalCancel();
}

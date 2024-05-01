#ifndef IHISTOGRAM_H
#define IHISTOGRAM_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QPainter>

class IHistogram : public QQuickPaintedItem
{
    Q_OBJECT
public:
    IHistogram(QQuickItem* parent) : QQuickPaintedItem(parent){};
    virtual ~IHistogram(){};
public slots:
    virtual void slotFillItemsHistogram(QVector<QPair<QString, int> > _wordVector) = 0;
    virtual void slotClearHistogram() = 0;

};

#endif // IHISTOGRAM_H

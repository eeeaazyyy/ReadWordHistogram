#ifndef ITEMHISTOGRAM_H
#define ITEMHISTOGRAM_H

#include <QObject>
#include <QPainter>
#include "IHistogram.h"

class ItemHistogram : public IHistogram
{
    Q_OBJECT

public:
    ItemHistogram(QQuickItem *parent = nullptr);
    ~ItemHistogram();

    QString name = " first";

private:
    QVector<QPair<QString, int>> wordsVector;
public slots:
    void slotFillItemsHistogram(QVector<QPair<QString, int> > _wordVector) override;
    void slotClearHistogram() override;
protected:
    void paint(QPainter* painter) override;
};

#endif // ITEMHISTOGRAM_H

#include "itemhistogram.h"


ItemHistogram::ItemHistogram(QQuickItem* parent) : IHistogram(parent), wordsVector({})
{
    this->setFlag(QQuickItem::ItemHasContents, true);
}

ItemHistogram::~ItemHistogram()
{

}

void ItemHistogram::slotFillItemsHistogram(QVector<QPair<QString, int> > _wordVector)
{
    wordsVector = _wordVector;
    std::sort(wordsVector.begin(), wordsVector.end(),
              [](const QPair<QString, int> &a, const QPair<QString, int> &b)
    {
        return a.second > b.second;
    });
    update();
}

void ItemHistogram::slotClearHistogram()
{
    wordsVector.clear();
    wordsVector = {};
    update();
}

void ItemHistogram::paint(QPainter *painter)
{
    if(wordsVector.isEmpty())
    {
        return;
    }
    //qDebug()<<"wordsVector NO EMPTY";
    painter->setPen(Qt::black);
    painter->setBrush(Qt::blue);

    int count = (wordsVector.count() >= 15) ? 15 : wordsVector.count();
    int columnWidth = width() / count;

    int topOffset = 50;

    for (int i = 0; i < count; ++i) {
        int heightSize = wordsVector[0].second + 50;
        int height = wordsVector[i].second *  (this->height() - topOffset) / heightSize;
        painter->drawRect(i * columnWidth, this->height() - height, columnWidth, height);

        // Добавление текста со значением
        QString text = wordsVector[i].first;
        painter->drawText(i * columnWidth + columnWidth / 2 - 10, this->height() - height - 10, text);

        // Добавление текста с количеством совпадений
        QString countText = QString::number(wordsVector[i].second);
        painter->drawText(i * columnWidth + columnWidth / 2 - 10, this->height() - height/2 , countText);
    }

}

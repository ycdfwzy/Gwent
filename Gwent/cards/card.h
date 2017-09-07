#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QPixmap>
#include <QPainter>

class Card : public QObject
{
    Q_OBJECT
public:
    explicit Card(int id, QObject *parent = nullptr);

    QPixmap& card_picture();

signals:

public slots:

private:
    QString name;
    QString path;
    QString rule, type;
    int id, baseblood, boostblood, armor;
};

#endif // CARD_H

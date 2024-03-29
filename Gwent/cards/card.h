#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QPixmap>
#include <QPainter>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

class Card : public QObject
{
    Q_OBJECT
public:
    explicit Card(int id, QObject *parent = nullptr);
    Card(const Card &c);
    QString get_name() const;
    QString get_faction() const;
    QString get_picpath() const;
    QString get_color() const;
    QString get_rule() const;
    QString get_type() const;
    QString get_location() const;
    int get_id() const;
    int get_baseblood() const;
    int get_boostblood() const;
    int get_armor() const;
    void add_base(int);
    void add_boost(int);
    void add_armor(int);
    void set_ARMOR(bool);
    bool get_ARMOR();

signals:

public slots:

private:
    QString name, faction;
    QString picpath, color;
    QString rule, type;
    QString location;
    QString curlocation;
    int id, baseblood, boostblood, armor;
    bool ARMOR;
};

#endif // CARD_H

#include "card.h"
#include <QDebug>

Card::Card(int id, QObject *parent) : QObject(parent)
{
    this->id = id;
    boostblood = 0;
    armor = 0;

    QFile file(":/data/cardinfo");
    if (file.open(QFile::ReadOnly)){
        QString str = file.readAll();
        QJsonParseError error;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(str.toUtf8(), &error);
        if (error.error == QJsonParseError::NoError){
            if (!(jsonDocument.isNull() || jsonDocument.isEmpty())){
                if (jsonDocument.isObject()){
                    QJsonObject info = jsonDocument.object();

                    QJsonValue all = info.take(QString::number(id));
                    if (all.isObject()){
                        //qDebug() << "isObject";
                        QJsonObject tmp = all.toObject();
                        name = tmp.take("name_cn").toVariant().toString();
                        picpath = tmp.take("picpath").toVariant().toString();
                        rule = tmp.take("rule").toVariant().toString();
                        type = tmp.take("type").toVariant().toString();
                        color = tmp.take("color").toVariant().toString();
                        faction = tmp.take("faction").toVariant().toString();
                        baseblood = tmp.take("blood").toVariant().toInt();
                        if (baseblood > 0){
                            location = tmp.take("location").toVariant().toString();

                            ARMOR = false;
                        }
                        qDebug() << name << " " << baseblood;
                    }
                }
            }
        }
    }
/*
    switch (id) {
    case 16:    //刺骨冰霜
        name = "刺骨冰霜";
        break;
    case 8:    //刺骨冰霜
        break;
    case 18:   //蔽日浓雾
        break;
    case 41:   //倾盆大雨
        break;
    case 19:   //撕裂
        break;
    case 17:   //免疫增强
        break;
    case 10:  //指挥号角
        break;
    case 7:   //贝克尔的扭曲之镜
        break;
    case 101: //杰洛特：伊格尼法印
        break;
    case 183: //达冈
        break;
    case 57:  //小雾妖
        break;
    case 58:  //盖尔
        break;
    case 66:  //赛尔伊诺鹰身女妖
        break;
    case 75:  //鹰身女妖
        break;
    case 169: //林精
        break;
    case 188: //土元素
        break;
    case 181: //老巫妪：织婆
        break;
    case 182: //老巫妪：呢喃婆
        break;
    case 256: //老巫妪：煮婆
        break;
    case 225: //大狮鹫
        break;
    case 236: //尼斯里拉
        break;
    case 281: //卡兰希尔
        break;
    case 294: //畏惧者
        break;
    case 166: //暗影长者
        break;
    case 63:  //蟹蜘蛛
        break;
    case 167: //蜥蜴人战士
        break;
    case 171: //蟹蜘蛛巨兽
        break;
    default:
        break;
    }
*/
}

Card::Card(const Card &c){
    name = c.name;
    faction = c.name;
    picpath = c.picpath;
    color = c.color;
    rule = c.rule;
    type = c.type;
    id = c.id;
    baseblood = c.baseblood;
    boostblood = c.boostblood;
    armor = c.armor;
}

QString Card::get_name() const{return name;}
QString Card::get_faction() const{return faction;}
QString Card::get_picpath() const{return picpath;}
QString Card::get_color() const{return color;}
QString Card::get_rule() const{return rule;}
QString Card::get_type() const{return type;}
int Card::get_id() const{return id;}
int Card::get_baseblood() const{return baseblood;}
int Card::get_boostblood() const{return boostblood;}
int Card::get_armor() const{return armor;}
QString Card::get_location() const{return location;}
bool Card::get_ARMOR(){return ARMOR;}
void Card::set_ARMOR(bool f){ARMOR = f;}
void Card::add_armor(int dlt){
    if (dlt < 0 && ARMOR){
        set_ARMOR(false);
        return;
    }
    if (armor + dlt < 0){
        armor = 0;
        dlt += armor;
        add_boost(dlt);
        return;
    }
    armor += dlt;
}
void Card::add_boost(int dlt){
    if (boostblood + dlt < 0){
        dlt += boostblood;
        boostblood = 0;
        add_base(dlt);
        return;
    }
    boostblood += dlt;
}
void Card::add_base(int dlt){
    baseblood += dlt;
}

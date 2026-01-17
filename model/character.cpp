#include "character.h"

using namespace Model;


Character::Character(QObject *parent) :
    QObject(parent)
    , m_id(0) {}

Character *Character::fromJson(const QJsonObject &json, QObject *parent) {
    Character *c = new Character(parent);
    c->setId(json["id"].toInt());
    c->setName(json["name"].toString());
    c->setStatus(json["status"].toString());
    c->setSpecies(json["species"].toString());
    c->setImage(json["image"].toString());

    QJsonObject originObj = json["origin"].toObject();
    c->setOriginName(originObj["name"].toString());

    return c;
}

int Character::id() const noexcept {
    return m_id;
}

QString Character::name() const {
    return m_name;
}

QString Character::status() const {
    return m_status;
}

QString Character::species() const {
    return m_species;
}

QString Character::image() const {
    return m_image;
}

QString Character::originName() const {
    return m_originName;
}

void Character::setId(int id) {
    if (m_id != id) {
        m_id = id;
        emit idChanged();
    }
}

void Character::setName(const QString &name) {
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

void Character::setStatus(const QString &status) {
    if (m_status != status) {
        m_status = status;
        emit statusChanged();
    }
}

void Character::setSpecies(const QString &species) {
    if (m_species != species) {
        m_species = species;
        emit speciesChanged();
    }
}

void Character::setImage(const QString &image) {
    if (m_image != image) {
        m_image = image;
        emit imageChanged();
    }
}

void Character::setOriginName(const QString &origin) {
    if (m_originName != origin) {
        m_originName = origin;
        emit originNameChanged();
    }
}

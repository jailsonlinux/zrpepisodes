#include "episode.h"

using namespace Model;

/**
 * @brief Episode::Episode representa um episodio encontrado pela API
 * @param parent
 */
Episode::Episode(QObject *parent) :
    QObject(parent)
    , m_id(0) {}

/**
 * @brief Episode::fromJson Retorna um ponteiro para instancia de episodio a partir do retorno da API
 * @param json
 * @param parent
 * @return
 */
Episode *Episode::fromJson(const QJsonObject &json, QObject *parent) {
    Episode *ep = new Episode(parent);
    ep->setId(json["id"].toInt());
    ep->setName(json["name"].toString());
    ep->setAirDate(json["air_date"].toString());
    ep->setCode(json["episode"].toString());

    QStringList charList;
    QJsonArray charArray = json["characters"].toArray();
    for (const auto &val : charArray) {
        charList.append(val.toString());
    }
    ep->setCharacters(charList);

    return ep;
}

int Episode::id() const {
    return m_id;
}

QString Episode::name() const {
    return m_name;
}

QString Episode::airDate() const {
    return m_airDate;
}

QString Episode::code() const {
    return m_code;
}

QStringList Episode::characters() const {
    return m_characters;
}

void Episode::setId(int id) {
    if (m_id != id) {
        m_id = id;
        emit idChanged();
    }
}

void Episode::setName(const QString &name) {
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

void Episode::setAirDate(const QString &date) {
    if (m_airDate != date) {
        m_airDate = date;
        emit airDateChanged();
    }
}

void Episode::setCode(const QString &code) {
    if (m_code != code) {
        m_code = code;
        emit codeChanged();
    }
}

void Episode::setCharacters(const QStringList &list) {
    if (m_characters != list) {
        m_characters = list;
        emit charactersChanged();
    }
}


#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>

/**
 * @brief The Episode class representa a response do GET em:
 * https://rickandmortyapi.com/api/episode/28
 * {
  "id": 28,
  "name": "The Ricklantis Mixup",
  "air_date": "September 10, 2017",
  "episode": "S03E07",
  "characters": [
    "https://rickandmortyapi.com/api/character/1",
    "https://rickandmortyapi.com/api/character/2",
    // ...
  ],
  "url": "https://rickandmortyapi.com/api/episode/28",
  "created": "2017-11-10T12:56:36.618Z"
}
@author Jailson jotalinux2@gmail.com
@date 2026/01/17
 */
namespace Model {

class Episode : public QObject {
    Q_OBJECT
    // Para versão em QML
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString airDate READ airDate WRITE setAirDate NOTIFY airDateChanged)
    Q_PROPERTY(QString code READ code WRITE setCode NOTIFY codeChanged)
    Q_PROPERTY(QStringList characters READ characters WRITE setCharacters NOTIFY charactersChanged)

public:
    explicit Episode(QObject *parent = nullptr);

    static Episode* fromJson(const QJsonObject &json, QObject *parent = nullptr);

    int id() const;
    QString name() const;
    QString airDate() const;
    QString code() const;
    QStringList characters() const;

    void setId(int id);
    void setName(const QString &name);
    void setAirDate(const QString &date);
    void setCode(const QString &code);
    void setCharacters(const QStringList &list);

signals:
    void idChanged();
    void nameChanged();
    void airDateChanged();
    void codeChanged();
    void charactersChanged();

private:
    int m_id;
    QString m_name;
    QString m_airDate;
    QString m_code;
    QStringList m_characters;
};
}

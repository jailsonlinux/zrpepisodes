#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>

/**
 * @brief The Character class representa um personagem.
 * https://rickandmortyapi.com/api/character/2
{
  "id": 2,
  "name": "Morty Smith",
  "status": "Alive",
  "species": "Human",
  "type": "",
  "gender": "Male",
  "origin": {
    "name": "Earth",
    "url": "https://rickandmortyapi.com/api/location/1"
  },
  "location": {
    "name": "Earth",
    "url": "https://rickandmortyapi.com/api/location/20"
  },
  "image": "https://rickandmortyapi.com/api/character/avatar/2.jpeg",
  "episode": [
    "https://rickandmortyapi.com/api/episode/1",
    "https://rickandmortyapi.com/api/episode/2",
    // ...
  ],
  "url": "https://rickandmortyapi.com/api/character/2",
  "created": "2017-11-04T18:50:21.651Z"
}
 *
*@author Jailson jotalinux2@gmail.com
*@date 2026/01/17

 */

namespace Model {

/**
 * @brief The Character class representa um Personagem retornado pela API.
 */
class Character : public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString species READ species WRITE setSpecies NOTIFY speciesChanged)
    Q_PROPERTY(QString image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(QString originName READ originName WRITE setOriginName NOTIFY originNameChanged)

public:
    explicit Character(QObject *parent = nullptr);

    /**
     * @brief fromJson Parseia json de retorno para instancia de Character
     * @param json
     * @param parent
     * @return
     */
    static Character* fromJson(const QJsonObject &json, QObject *parent = nullptr);

    int id() const noexcept;
    QString name() const;
    QString status() const;
    QString species() const;
    QString image() const;
    QString originName() const;

    void setId(int id);
    void setName(const QString &name);
    void setStatus(const QString &status);
    void setSpecies(const QString &species);
    void setImage(const QString &image);
    void setOriginName(const QString &origin);

signals:
    void idChanged();
    void nameChanged();
    void statusChanged();
    void speciesChanged();
    void imageChanged();
    void originNameChanged();

private:
    int m_id;
    QString m_name;
    QString m_status;
    QString m_species;
    QString m_image;
    QString m_originName;
};
}
Q_DECLARE_METATYPE(Model::Character*)


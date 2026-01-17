#include "apiclient.h"
#include <memory>
#include "../model/episode.h"
#include "apiconfig.h"

using namespace ApiConstants;
using namespace Api;
using namespace Model;

ApiClient::ApiClient(QObject *parent) :
    QObject(parent)
    , network(new QNetworkAccessManager(this)) {}

void ApiClient::fetchEpisodeCharacters(const int episodeId) {
    QUrl url(ApiConstants::EpisodeEndpoint.arg(episodeId));
    QNetworkReply *reply = network->get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            emit errorOccurred(reply->errorString());
            return;
        }

        QJsonObject obj = QJsonDocument::fromJson(reply->readAll()).object();
        std::unique_ptr<Episode> currentEpisode(Episode::fromJson(obj, nullptr));
        processCharacters(currentEpisode->characters());
    });
}

void ApiClient::extractCharactersNames(const QStringList &urls) {
    const QStringList ids = extractCharactersIds(urls);

    if (ids.isEmpty()){
        return;
    }

    // Requisição otimizada com todos os ids de personagens de uma vez
    QUrl url(QString("https://rickandmortyapi.com/api/character/%1").arg(ids.join(",")));
    QNetworkReply *reply = network->get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();

        if (reply->error() != QNetworkReply::NoError) {
            emit errorOccurred(reply->errorString());
            return;
        }

        QStringList names = {};
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

        if (doc.isArray()) {
            const QJsonArray charactersArray = doc.array();
            for (const auto &val : charactersArray){
                names << val.toObject()["name"].toString();
            }
        } else if (doc.isObject()) {
            names << doc.object()["name"].toString();
        }

        names.sort(Qt::CaseInsensitive);
        emit charactersNamesReady(names);
    });
}


void ApiClient::processCharacters(const QStringList &urls) {

    const QStringList ids = extractCharactersIds(urls);

    if (ids.isEmpty()){
        return;
    }

    // Requisição otimizada com todos os ids de personagens de uma vez
    QUrl url(ApiConstants::CharacterEndpoint.arg(ids.join(",")));

    QNetworkReply *reply = network->get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();

        QList<Character*> characterObjects = {};
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

        if (doc.isArray()) {
            const QJsonArray charactersArray = doc.array();

            for (const auto &val : charactersArray) {
                characterObjects.append(Character::fromJson(val.toObject(), this));
            }
        } else {
            characterObjects.append(Character::fromJson(doc.object(), this));
        }

        std::sort(characterObjects.begin(), characterObjects.end(), [](Character* a, Character* b) {
            return a->name().localeAwareCompare(b->name()) < 0;
        });

        emit charactersReady(characterObjects);
    });

}

QStringList ApiClient::extractCharactersIds(const QStringList &urls) const noexcept
{
    QStringList ids;
    for (const QString &val : urls) {
        ids << val.section('/', -1);
    }

    return ids;
}

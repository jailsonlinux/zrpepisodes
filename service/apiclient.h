#pragma once

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>

#include "../model/character.h"

using namespace Model;

namespace Api {

/**
 * @brief The ApiClient class responsavel por fazer as requisições a API e parsear para objetos mapeados.
 * @author Jailson jotalinux2@gmail.com
 * @date 2026/01/17
 */
class ApiClient : public QObject {
    Q_OBJECT
public:
    /**
     * @brief ApiClient
     * @param parent
     *  Constructor
     */
    explicit ApiClient(QObject *parent = nullptr);

    /**
     * @brief fetchEpisodeCharacters
     * @param episodeId se refere ao id do episodio
     * Retorna os personagens do episodio solicitado.
     * Ao fim da requisicao com sucesso se tem a lista de urls de cada personagem para consulta.
     */
    void fetchEpisodeCharacters(const int episodeId);

    /**
     * @brief extractIds Extrai os ids de personagens das urls de pesquisa
     * @param urls
     * @return lista de ids extraida
     */
    QStringList extractCharactersIds(const QStringList &urls) const noexcept;

    /**
     * @brief extractCharacters
     * @param urls
     * Extrai os ids de personagens das urls de pesquisa, e retorna lista de nomes ordenado
     */
    void extractCharactersNames(const QStringList &urls);
    /**
     * @brief processCharacters
     * @param urls
     * Retorna lista de nomes ordenado
     */
    void processCharacters(const QStringList &urls);

signals:
    /**
     * @brief charactersReady
     * @param characterObjects
     * Sinaliza que a lista de personagens foi enviada
     */
    void charactersReady(QList<Character*> characterObjects);

    /**
     * @brief charactersNamesReady
     * @param characterNames
     * Sinaliza que lista com nomes dos personagens foi extraida e enviada ordenada.
     */
    void charactersNamesReady(QStringList characterNames);

    /**
     * @brief errorOccurred
     * @param error
     * Sinaliza que houve erro na resposta da requisição
     */
    void errorOccurred(QString error);

private:

    QNetworkAccessManager *network;
};
}

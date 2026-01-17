#include <QtTest>
#include <QSignalSpy>
#include "service/apiclient.h"
#include "model/character.h"

using namespace Api;
using namespace Model;

class TestApiClient : public QObject {
    Q_OBJECT

private slots:
    void initTestCase() {}

    void testExtractCharactersIds() {
        ApiClient client;
        QStringList urls = {
            "https://rickandmortyapi.com/api/character/1",
            "https://rickandmortyapi.com/api/character/42"
        };

        QStringList ids = client.extractCharactersIds(urls);

        QCOMPARE(ids.size(), 2);
        QCOMPARE(ids.at(0), QString("1"));
        QCOMPARE(ids.at(1), QString("42"));
    }

    void testFetchCharactersIntegration() {
        // Requisição REAL.

        ApiClient client;
        QSignalSpy spy(&client, &ApiClient::charactersReady);

        QStringList urls = {
            "https://rickandmortyapi.com/api/character/2", // Morty
            "https://rickandmortyapi.com/api/character/1"  // Rick
        };

        client.processCharacters(urls);

        QVERIFY(spy.wait(5000));

        QCOMPARE(spy.count(), 1);

        // Recupera a lista enviada pelo sinal
        QList<Character*> results = qvariant_cast<QList<Character*>>(spy.at(0).at(0));

        QCOMPARE(results.size(), 2);
        // Verifica ordenação alfabética
        QCOMPARE(results.at(0)->name(), QString("Morty Smith"));
        QCOMPARE(results.at(1)->name(), QString("Rick Sanchez"));
    }

    void testErrorHandling() {
        ApiClient client;
        QSignalSpy spyError(&client, &ApiClient::errorOccurred);

        // Simula uma URL inválida que resultará em erro de rede
        client.fetchEpisodeCharacters(999999); // ID inexistente

        QVERIFY(spyError.wait(5000));
        QCOMPARE(spyError.count(), 1);

        QString errorMsg = spyError.at(0).at(0).toString();
        QVERIFY(!errorMsg.isEmpty());
    }
};

QTEST_MAIN(TestApiClient)
#include "test_apiclient.moc"

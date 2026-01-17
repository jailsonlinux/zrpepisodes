#include <QtTest>
#include "model/character.h"
#include "model/episode.h"

using namespace Model;

class TestModels : public QObject {
    Q_OBJECT
private slots:
    void initTestCase() {}

    void testParsingCharacter() {
        QJsonObject json;
        json["id"] = 1;
        json["name"] = "Rick Sanchez";
        json["status"] = "Alive";

        auto *c = Model::Character::fromJson(json, this);

        QCOMPARE(c->id(), 1);
        QCOMPARE(c->name(), QString("Rick Sanchez"));
        QCOMPARE(c->status(), QString("Alive"));

        c->deleteLater();
    }

    void testParsingEpisode_data() {

        QTest::addColumn<QJsonObject>("jsonInput");
        QTest::addColumn<int>("expectedId");
        QTest::addColumn<QString>("expectedName");
        QTest::addColumn<int>("expectedCharCount");

        QJsonObject sampleJson;
        sampleJson["id"] = 28;
        sampleJson["name"] = "The Ricklantis Mixup";
        sampleJson["air_date"] = "September 10, 2017";
        sampleJson["episode"] = "S03E07";

        QJsonArray chars;
        chars.append("https://rickandmortyapi.com/api/character/1");
        chars.append("https://rickandmortyapi.com/api/character/2");
        sampleJson["characters"] = chars;


        QTest::newRow("Valid Episode 28") << sampleJson << 28 << "The Ricklantis Mixup" << 2;
    }

    void testParsingEpisode() {

        QFETCH(QJsonObject, jsonInput);
        QFETCH(int, expectedId);
        QFETCH(QString, expectedName);
        QFETCH(int, expectedCharCount);

        std::unique_ptr<Episode> ep(Episode::fromJson(jsonInput, this));

        QVERIFY(ep != nullptr);
        QCOMPARE(ep->id(), expectedId);
        QCOMPARE(ep->name(), expectedName);
        QCOMPARE(ep->characters().size(), expectedCharCount);

        if (expectedCharCount > 0) {
            QCOMPARE(ep->characters().at(0), jsonInput["characters"].toArray().at(0).toString());
        }
    }

    void cleanupTestCase() {}
};

QTEST_MAIN(TestModels)
#include "test_models.moc"

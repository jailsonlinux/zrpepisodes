#include "searchepisodes.h"
#include "./ui_searchepisodes.h"
#include "model/character.h"

SearchEpisodes::SearchEpisodes(QWidget *parent)
    : QMainWindow(parent)
    , apiClient(new ApiClient(this))
    , ui(new Ui::SearchEpisodes)
{
    ui->setupUi(this);
    connect(ui->btnSearch, &QPushButton::clicked, this, &SearchEpisodes::onSearchRequested);
    connect(apiClient, &ApiClient::charactersReady, this, &SearchEpisodes::onDisplayCharacters);
    connect(ui->lstResult, &QListWidget::itemClicked, this, &SearchEpisodes::onCharacterSelected);
    connect(apiClient, &ApiClient::errorOccurred, this, &SearchEpisodes::onErrorOcurred);

}

SearchEpisodes::~SearchEpisodes()
{
    delete ui;
}

void SearchEpisodes::onSearchRequested() {
    int id = ui->edtIdInput->text().toInt();
    if (id > 0) {
        ui->lstResult->clear();
        ui->btnSearch->setEnabled(false);
        apiClient->fetchEpisodeCharacters(id);
    }
}

void SearchEpisodes::onDisplayCharacters(const QList<Character*>& characterObjects) {
    ui->lstResult->clear();

    for (const Character* character : characterObjects) {
        QListWidgetItem *item = new QListWidgetItem(character->name(), ui->lstResult);
        item->setData(Qt::UserRole, QVariant::fromValue(character));
        ui->lstResult->addItem(item);
    }

    ui->btnSearch->setEnabled(true);
}

void SearchEpisodes::onCharacterSelected(QListWidgetItem *item)
{
    if (!item){
        return;
    }

    Character *character = item->data(Qt::UserRole).value<Character*>();
    if (character) {
        ui->lblCharacter->setText(formatCharacterLog(character));
        ui->lblCharacter->setTextFormat(Qt::RichText);
        ui->lblCharacter->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    }
}

void SearchEpisodes::onErrorOcurred(QString error)
{
    ui->lstResult->clear();
    ui->lblCharacter->clear();
    ui->lblCharacter->setText(error);
    ui->btnSearch->setEnabled(true);
}

QString SearchEpisodes::formatCharacterLog(Character* c) {
    if (!c) return "Nenhum personagem selecionado.";

    QString statusColor = (c->status().toLower() == "alive") ? "#27ae60" :
                              (c->status().toLower() == "dead") ? "#c0392b" : "#7f8c8d";

    return QString(
               "<div style='line-height: 150%;'>"
               "  <b style='font-size: 14px; color: #2c3e50;'>DETALHES DO PERSONAGEM</b><br>"
               "  <hr style='border: 0; border-top: 1px solid #bdc3c7;'>"
               "  <b>ID:</b> <span style='color: #2980b9;'>#%1</span><br>"
               "  <b>Nome:</b> <span style='font-size: 13px;'>%2</span><br>"
               "  <b>Status:</b> <span style='color: %3; font-weight: bold;'>%4</span><br>"
               "  <b>Espécie:</b> %5"
               "</div>"
               ).arg(c->id())
        .arg(c->name())
        .arg(statusColor)
        .arg(c->status().toUpper())
        .arg(c->species());
}

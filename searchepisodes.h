#pragma once

#include <QMainWindow>
#include <QList>
#include <QListWidgetItem>

#include "service/apiclient.h"
#include "model/character.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class SearchEpisodes;
}
QT_END_NAMESPACE

using namespace Api;
using namespace Model;

/**
 * @brief The SearchEpisodes class Tela principal de busca
 * @author Jailson jotalinux2@gmail.com
 * @date 2026/01/17
 */
class SearchEpisodes : public QMainWindow
{
    Q_OBJECT

public:
    SearchEpisodes(QWidget *parent = nullptr);
    ~SearchEpisodes();

private slots:
    /**
     * @brief onSearchRequested Ao clicar no botao usa ApiClient para executar a busca
     *
     */
    void onSearchRequested();

    /**
     * @brief onDisplayCharacters Ao retornar personagens pesquisados
     * @param characterObjects
     */
    void onDisplayCharacters(const QList<Character*>& characterObjects);

    /**
     * @brief onCharacterSelected Ao selecionar um item, exibe informações sobre ele.
     * @param item
     */
    void onCharacterSelected(QListWidgetItem *item);

    /**
     * @brief onErrorOcurred em caso de erro, exibe a mensagem.
     * @param error
     */
    void onErrorOcurred(QString error);

private:
    /**
     * @brief formatCharacterLog Exemplo de formatação em html, e css na label ui
     * @param c
     * @return
     */
    QString formatCharacterLog(Character* c);
private:
    ApiClient *apiClient;
    Ui::SearchEpisodes *ui;
};

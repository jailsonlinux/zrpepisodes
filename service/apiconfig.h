#pragma once
/**
 * Centraliza as uris da API neste namespace
 * @author Jailson jotalinux2@gmail.com
 * @date 2026/01/17
 */

namespace ApiConstants {
    const QString BaseUrl = "https://rickandmortyapi.com/api";
    const QString EpisodeEndpoint = BaseUrl + "/episode/%1";
    const QString CharacterEndpoint = BaseUrl + "/character/%1";
}

// SPDX-License-Identifier: GPL-3.0-or-later

#include "gui/LookupUrl.h"

#include <QRegularExpression>
#include <QUrlQuery>

LookupUrl LookupUrl::parse(const QUrl &url) {
    LookupUrl result;
    if (!url.isValid() || url.scheme() != "tagaini" || !url.userInfo().isEmpty() ||
        url.port() != -1 || url.hasFragment())
        return result;

    if (url.host() == "search" && url.path().isEmpty()) {
        const auto items = QUrlQuery(url).queryItems(QUrl::FullyDecoded);
        if (items.size() != 1 || items.first().first != "q" ||
            items.first().second.trimmed().isEmpty())
            return result;
        result.type = Search;
        result.text = items.first().second;
    } else if (url.host() == "word" && !url.hasQuery()) {
        static const QRegularExpression path("\\A/([0-9]+)\\z");
        const auto match = path.match(url.path());
        if (!match.hasMatch())
            return result;
        bool ok;
        const quint32 id = match.captured(1).toUInt(&ok);
        if (!ok || id == 0)
            return result;
        result.type = Word;
        result.entryId = id;
    }
    return result;
}

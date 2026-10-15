// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef __GUI_LOOKUP_URL_H
#define __GUI_LOOKUP_URL_H

#include <QString>
#include <QUrl>

/// External lookup routes, independent of the dictionary and window lifetime.
struct LookupUrl {
    enum Type { Invalid, Search, Word };
    Type type = Invalid;
    QString text;
    quint32 entryId = 0;

    static LookupUrl parse(const QUrl &url);
};

#endif

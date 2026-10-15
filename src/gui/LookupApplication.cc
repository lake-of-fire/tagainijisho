// SPDX-License-Identifier: GPL-3.0-or-later

#include "gui/LookupApplication.h"
#include "gui/LookupUrl.h"

#include <QFileOpenEvent>

bool LookupApplication::event(QEvent *event) {
    if (event->type() == QEvent::FileOpen) {
        const QUrl url = static_cast<QFileOpenEvent *>(event)->url();
        if (LookupUrl::parse(url).type != LookupUrl::Invalid) {
            if (_lookupReady)
                emit lookupRequested(url);
            else
                // Only the most recent lookup matters before the UI is ready.
                _pendingLookup = url;
            event->accept();
            return true;
        }
    }
    return QApplication::event(event);
}

void LookupApplication::setLookupReady() {
    _lookupReady = true;
    const QUrl pending = _pendingLookup;
    _pendingLookup.clear();
    if (!pending.isEmpty())
        emit lookupRequested(pending);
}

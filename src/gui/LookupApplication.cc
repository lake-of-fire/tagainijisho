// SPDX-License-Identifier: GPL-3.0-or-later

#include "gui/LookupApplication.h"
#include "gui/LookupUrl.h"

#include <QFileOpenEvent>

bool LookupApplication::event(QEvent *event) {
    if (event->type() == QEvent::FileOpen) {
        const QUrl url = static_cast<QFileOpenEvent *>(event)->url();
        if (LookupUrl::parse(url).type != LookupUrl::Invalid) {
            // Keep the most recent request during startup or a modal lookup dialog.
            _pendingLookup = url;
            deliverPendingLookup();
            event->accept();
            return true;
        }
    }
    return QApplication::event(event);
}

void LookupApplication::setLookupReady() {
    _lookupReady = true;
    deliverPendingLookup();
}

void LookupApplication::deliverPendingLookup() {
    if (!_lookupReady || _handlingLookup)
        return;
    // A missing-entry dialog runs a nested event loop. Defer URLs received there
    // until the current lookup returns, rather than nesting dialogs/handlers.
    _handlingLookup = true;
    while (!_pendingLookup.isEmpty()) {
        const QUrl pending = _pendingLookup;
        _pendingLookup.clear();
        emit lookupRequested(pending);
    }
    _handlingLookup = false;
}

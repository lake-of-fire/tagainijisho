// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef __GUI_LOOKUP_APPLICATION_H
#define __GUI_LOOKUP_APPLICATION_H

#include <QApplication>
#include <QUrl>

/// Receives macOS URL events even while startup dialogs are running.
class LookupApplication : public QApplication {
    Q_OBJECT
  private:
    bool _lookupReady = false;
    bool _handlingLookup = false;
    QUrl _pendingLookup;

    void deliverPendingLookup();

  protected:
    bool event(QEvent *event) override;

  public:
    LookupApplication(int &argc, char **argv) : QApplication(argc, argv) {}
    void setLookupReady();

  signals:
    void lookupRequested(const QUrl &url);
};

#endif

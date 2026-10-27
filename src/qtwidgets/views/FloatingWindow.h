/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_FLOATINGWINDOW_QTWIDGETS_H
#define KD_FLOATINGWINDOW_QTWIDGETS_H

#pragma once

#include "View.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QMainWindow;
QT_END_NAMESPACE

namespace KDDockWidgets::Core {
class FloatingWindow;
class Group;
}

namespace KDDockWidgets::QtWidgets {


class DOCKS_EXPORT FloatingWindow : public View<QWidget>
{
    Q_OBJECT
public:
    explicit FloatingWindow(Core::FloatingWindow *controller,
                            QMainWindow *parent = nullptr,
                            Qt::WindowFlags windowFlags = {});

    ~FloatingWindow() override;

    Core::FloatingWindow *floatingWindow() const;

protected:
    void paintEvent(QPaintEvent *) override;
    bool event(QEvent *ev) override;
    bool eventFilter(QObject *o, QEvent *ev) override;
    void init() final;
#if defined(Q_OS_WIN)
    bool nativeEvent(const QByteArray &eventType, void *message,
                     Qt5Qt6Compat::qintptr *result) override;
#endif

    /// @brief Sets the margins around the title bar and the drop area: 4 logical pixels by
    /// default, along which the window is resized when it has no native frame. Called at init()
    /// and when the window moves to another screen. Override it to lay the window out
    /// differently, for example to paint a frame of your own; leave the window at least the
    /// default margins where a frameless window is to be resized from its edges.
    virtual void updateMargins();

Q_SIGNALS:
    void numGroupsChanged();

private:
    class Private;
    Private *const d;

    Q_DISABLE_COPY(FloatingWindow)
};

}

#endif

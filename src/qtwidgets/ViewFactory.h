/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_VIEWFACTORY_QTWIDGETS_H
#define KDDOCKWIDGETS_VIEWFACTORY_QTWIDGETS_H

#include "kddockwidgets/core/ViewFactory.h"

#include <QMap>

#include <utility>

// clazy:excludeall=ctor-missing-parent-argument

/**
 * @file
 * @brief A factory class for allowing the user to customize some internal widgets.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

QT_BEGIN_NAMESPACE
class QAbstractButton;
QT_END_NAMESPACE


namespace KDDockWidgets {

class DropIndicatorOverlay;

namespace Core {
class DockWidget;
class DropArea;
class Separator;
class TabBar;
class SideBar;
class FloatingWindow;
class MainWindow;
}

namespace QtWidgets {

/**
 * @brief The default ViewFactory for QtWidgets frontend.
 */
class DOCKS_EXPORT ViewFactory : public Core::ViewFactory
{
    Q_OBJECT
public:
    ViewFactory() = default;
    ~ViewFactory() override;

    Core::View *createDockWidget(const QString &uniqueName, DockWidgetOptions = {},
                                 LayoutSaverOptions = {}, Qt::WindowFlags = {}) const override;

    Core::View *createGroup(Core::Group *, Core::View *parent) const override;
    Core::View *createTitleBar(Core::TitleBar *, Core::View *parent) const override;
    Core::View *createStack(Core::Stack *, Core::View *parent) const override;
    Core::View *createTabBar(Core::TabBar *tabBar, Core::View *parent) const override;
    Core::View *createSeparator(Core::Separator *, Core::View *parent = nullptr) const override;
    Core::View *createFloatingWindow(Core::FloatingWindow *,
                                     Core::MainWindow *parent = nullptr,
                                     Qt::WindowFlags windowFlags = {}) const override;
    Core::View *createRubberBand(Core::View *parent) const override;
    Core::View *createSideBar(Core::SideBar *, Core::View *parent) const override;
    Core::View *createDropArea(Core::DropArea *, Core::View *parent) const override;
    Core::View *createMDILayout(Core::MDILayout *, Core::View *parent) const override;
    QIcon iconForButtonType(TitleBarButtonType type, qreal dpr) const override;
    void clearIconCache();
    virtual QAbstractButton *createTitleBarButton(QWidget *parent, TitleBarButtonType) const;

    /// @brief Returns the object name for a title bar button acting on @p dockWidget
    ///
    /// Title bar buttons are named after their type by createTitleBarButton(): "closeButton",
    /// "floatButton", "minimizeButton", "maximizeButton" and "autoHideButton". As there's one set
    /// of buttons per title bar, those names aren't unique. Override this to name the buttons
    /// after the dock widget they act on instead, for UI tests or automation tools that look
    /// widgets up by object name.
    ///
    /// This also applies to the buttons shown next to the tabs with
    /// Config::Flag_ShowButtonsOnTabBarIfTitleBarHidden.
    ///
    /// Called whenever @p dockWidget changes, for example when the current tab changes.
    /// @param type the button's type. The maximize button always passes TitleBarButtonType::Maximize
    /// and the auto-hide button TitleBarButtonType::AutoHide, whatever state they're showing.
    /// @param dockWidget the dock widget whose title the title bar is showing, that is, the
    /// current tab's. nullptr if there's none, as for the title bar of a floating window with
    /// nested groups.
    /// @return the new object name, or an empty string to leave the name as it is.
    /// The default implementation returns an empty string.
    virtual QString titleBarButtonObjectName(TitleBarButtonType type,
                                             Core::DockWidget *dockWidget) const;

    Core::ClassicIndicatorWindowViewInterface *
    createClassicIndicatorWindow(Core::ClassicDropIndicatorOverlay *, Core::View *parent) const override;
    Core::View *createSegmentedDropIndicatorOverlayView(Core::SegmentedDropIndicatorOverlay *controller,
                                                        Core::View *parent) const override;

    KDDockWidgets::Core::Action *createAction(Core::DockWidget *, const char *debugName) const override;

private:
    Q_DISABLE_COPY(ViewFactory)
    mutable QMap<std::pair<TitleBarButtonType, qreal>, QIcon> m_cachedIcons;
};

}

}

#endif

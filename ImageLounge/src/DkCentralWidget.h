/*******************************************************************************************************
 DkCentralWidget.cpp
 Created on:	14.11.2014
 
 nomacs is a fast and small image viewer with the capability of synchronizing multiple instances
 
 Copyright (C) 2011-2013 Markus Diem <markus@nomacs.org>
 Copyright (C) 2011-2013 Stefan Fiel <stefan@nomacs.org>
 Copyright (C) 2011-2013 Florian Kleber <florian@nomacs.org>

 This file is part of nomacs.

 nomacs is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 nomacs is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 *******************************************************************************************************/

#pragma once

#include <QWidget>
#include <QStackedLayout>

#include "DkSettings.h"
#include "DkImageContainer.h"

namespace nmc {

class DkTabInfo {
	
public:

	enum {
		tab_single_image,
		tab_thumb_preview,
		tab_recent_files,
		tab_empty,

		tab_end
	};

	DkTabInfo(const QSharedPointer<DkImageContainerT> imgC = QSharedPointer<DkImageContainerT>(), int idx = -1);

	bool operator==(const DkTabInfo& o) const;

	QFileInfo getFileInfo() const;
	void setFileInfo(const QFileInfo& fileInfo);

	QSharedPointer<DkImageContainerT> getImage() const;
	void setImage(QSharedPointer<DkImageContainerT> imgC);

	int getTabIdx() const;
	void setTabIdx(int idx);
	
	void loadSettings(const QSettings& settings);
	void saveSettings(QSettings& settings) const;

	QIcon getIcon();
	QString getTabText() const;

	int getMode() const;
	void setMode(int mode);

protected:
	QSharedPointer<DkImageContainerT> imgC;
	int tabIdx;
	int tabMode;
};

class DkViewPort;
class DkThumbScrollWidget;

class DllExport DkCentralWidget : public QWidget {
	Q_OBJECT

public:
	DkCentralWidget(DkViewPort* viewport, QWidget* parent = 0);
	~DkCentralWidget();

	DkViewPort* getViewPort() const;
	DkThumbScrollWidget* getThumbScrollWidget() const;

	void clearAllTabs();
	void updateTabs();
	void updateTab(DkTabInfo& tabInfo);
	QVector<DkTabInfo> getTabs() const;
	void saveSettings(bool clearTabs = false);
	int currentViewMode() const;

signals:
	void loadFileSignal(QFileInfo);
	void statusInfoSignal(QString, int);

public slots:
	void imageLoaded(QSharedPointer<DkImageContainerT> img);
	void currentTabChanged(int idx);
	void tabCloseRequested(int idx);
	void tabMoved(int from, int to);
	void addTab(QSharedPointer<DkImageContainerT> imgC = QSharedPointer<DkImageContainerT>(), int tabIdx = -1);
	void addTab(const QFileInfo& fileInfo, int idx = -1);
	void addTab(const DkTabInfo& tabInfo);
	void removeTab(int tabIdx = -1);
	void nextTab() const;
	void previousTab() const;
	void showThumbView(bool show = true);
	void showViewPort(bool show = true);
	void showTabs(bool show = true);

protected:
	DkViewPort* viewport;
	DkThumbScrollWidget* thumbScrollWidget;

	QTabBar* tabbar;
	QVector<DkTabInfo> tabInfos;

	QVector<QWidget*> widgets;
	QStackedLayout* viewLayout;

	void createLayout();
	void loadSettings();
	void updateTabIdx();
	void switchWidget(int widget);
	void switchWidget(QWidget* widget = 0);

	enum {
		viewport_widget,
		thumbs_widget,

		widget_end
	};
};


}
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
	QWidget *centralwidget;
	QGridLayout *gridLayout;
	QTabWidget *tabWidget;
	QWidget *tab;
	QGridLayout *gridLayout_2;
	QTreeWidget *HardwareTreeWidget;
	QWidget *tab_2;
	QStatusBar *statusbar;

	void setupUi(QMainWindow *MainWindow)
	{
		if (MainWindow->objectName().isEmpty())
			MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
		MainWindow->resize(640, 480);
		centralwidget = new QWidget(MainWindow);
		centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
		gridLayout = new QGridLayout(centralwidget);
		gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
		tabWidget = new QTabWidget(centralwidget);
		tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
		tab = new QWidget();
		tab->setObjectName(QString::fromUtf8("tab"));
		gridLayout_2 = new QGridLayout(tab);
		gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
		HardwareTreeWidget = new QTreeWidget(tab);
		HardwareTreeWidget->setObjectName(QString::fromUtf8("HardwareTreeWidget"));
		HardwareTreeWidget->setUniformRowHeights(true);
		HardwareTreeWidget->setSortingEnabled(true);
		HardwareTreeWidget->setAnimated(true);
		HardwareTreeWidget->setColumnCount(5);
		HardwareTreeWidget->header()->setProperty("showSortIndicator", QVariant(true));

		gridLayout_2->addWidget(HardwareTreeWidget, 0, 0, 1, 1);

		tabWidget->addTab(tab, QString());
		tab_2 = new QWidget();
		tab_2->setObjectName(QString::fromUtf8("tab_2"));
		tabWidget->addTab(tab_2, QString());

		gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

		MainWindow->setCentralWidget(centralwidget);
		statusbar = new QStatusBar(MainWindow);
		statusbar->setObjectName(QString::fromUtf8("statusbar"));
		MainWindow->setStatusBar(statusbar);

		retranslateUi(MainWindow);

		tabWidget->setCurrentIndex(0);


		QMetaObject::connectSlotsByName(MainWindow);
	} // setupUi

	void retranslateUi(QMainWindow *MainWindow)
	{
		MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
		QTreeWidgetItem *___qtreewidgetitem = HardwareTreeWidget->headerItem();
		___qtreewidgetitem->setText(4, QCoreApplication::translate("MainWindow", "Name", nullptr));
		___qtreewidgetitem->setText(3, QCoreApplication::translate("MainWindow", "Function", nullptr));
		___qtreewidgetitem->setText(2, QCoreApplication::translate("MainWindow", "Device", nullptr));
		___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "Bus", nullptr));
		___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Domain", nullptr));
		tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "PCI Hardware", nullptr));
		tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "System Info", nullptr));
	} // retranslateUi

};

namespace Ui {
class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#include "pci_device_tree_data.h"

class MainWindow : public QMainWindow {
public:
	MainWindow(QWidget* p = nullptr);
private:
	PCIDeviceTreeData* m_PCIDeviceTreeData;
	Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H


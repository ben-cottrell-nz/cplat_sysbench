//
// Created by ben on 21/02/22.
//
#include "mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget* p)
		:ui(new Ui::MainWindow), QMainWindow(p)
{
	ui->setupUi(this);
	m_PCIDeviceTreeData = new PCIDeviceTreeData(this);
	setStyleSheet(
			"QWidget { color: #cfcfcf; background-color: #2d2d2d; }");
	setWindowTitle("cplat-sysbench");
	ui->HardwareTreeWidget
			->addTopLevelItems(m_PCIDeviceTreeData->m_List);
}
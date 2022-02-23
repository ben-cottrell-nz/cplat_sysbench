//
// Created by ben on 21/02/22.
//
#include "mainwindow.h"
#include <QString>
extern "C" {
#include "../libpciutils/pci.h"
}

MainWindow::MainWindow(QWidget* p)
		:ui(new Ui::MainWindow), QMainWindow(p)
{
	ui->setupUi(this);
	setStyleSheet("QWidget { color: #cfcfcf; background-color: #2d2d2d; }");
	setWindowTitle("cplat-sysbench");
	m_HardwarePCIList += new QTreeWidgetItem({"Root"},
			QTreeWidgetItem::UserType);
	PopulateHardwareTree();
	ui->HardwareTreeWidget->addTopLevelItems(m_HardwarePCIList);
}
void MainWindow::PopulateHardwareTree()
{
	struct pci_dev* dev;
	m_pciacc = pci_alloc();
	pci_init(m_pciacc);
	pci_scan_bus(m_pciacc);
	uint32_t c;
	char namebuf[1024], * name;
	for (dev = m_pciacc->devices; dev!=nullptr; dev = dev->next) {
		pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);    /* Fill in header info we need */
		c = pci_read_byte(dev, PCI_INTERRUPT_PIN);
		name = pci_lookup_name(m_pciacc, namebuf, sizeof(namebuf), PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id);
		m_HardwarePCIList[0]->insertChild(0,
				new QTreeWidgetItem({name}));
	}
	pci_cleanup(m_pciacc);
}
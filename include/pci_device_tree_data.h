//
// Created by ben on 24/02/22.
//

#ifndef CPLAT_SYSBENCH_PCIDEVICESTREEVIEWITEMS_H
#define CPLAT_SYSBENCH_PCIDEVICESTREEVIEWITEMS_H

#include <QTreeWidgetItem>
#include <QObject>

class PCIDeviceTreeData : public QObject {
public:
	PCIDeviceTreeData(QObject*);
	~PCIDeviceTreeData();
	QList<QTreeWidgetItem*> m_List;
private:
	struct pci_access* m_pciacc;

};

#endif //CPLAT_SYSBENCH_PCIDEVICESTREEVIEWITEMS_H

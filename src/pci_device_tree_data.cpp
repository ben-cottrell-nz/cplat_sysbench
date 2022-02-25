//
// Created by ben on 24/02/22.
//


#include "pci_device_tree_data.h"
extern "C" {
#include "../libpciutils/pci.h"
}
PCIDeviceTreeData::PCIDeviceTreeData(QObject* p)
		:QObject(p)
{
	struct pci_dev* dev;
	m_pciacc = pci_alloc();
	pci_init(m_pciacc);
	pci_scan_bus(m_pciacc);
	uint32_t c;
	char namebuf[1024], * name;
	QList<pci_dev*> devList;
	for (dev = m_pciacc->devices;
		 dev!=nullptr;
		 dev = dev->next) {
		pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES
				| PCI_FILL_CLASS
				| PCI_FILL_PARENT);    /* Fill in header info we need */
		dev->parent;
		c = pci_read_byte(dev, PCI_INTERRUPT_PIN);
		devList += dev;
	}
	std::sort(devList.begin(), devList.end(),
			[&](pci_dev* first, pci_dev* second) {
			  if (first->domain<second->domain)
				  return false;
			  if (first->domain>second->domain)
				  return true;
			  if (first->bus<second->bus)
				  return false;
			  if (first->bus>second->bus)
				  return true;
			  if (first->dev<second->dev)
				  return false;
			  if (first->dev>second->dev)
				  return true;
			  if (first->func<second->func)
				  return false;
			  if (first->func>second->func)
				  return true;
			  return false;
			});
	for (auto d = 0;
		 d<devList.size();
		 d++) {
		pci_dev* dev = devList[d];
		name = pci_lookup_name(m_pciacc, namebuf,
				sizeof(namebuf), PCI_LOOKUP_DEVICE,
				dev->vendor_id, dev->device_id);
		auto busChildren = std::count_if(devList.begin(),
				devList
		.end(),	[&]
		(pci_dev* first){
			return first->bus == dev->bus;
		});
		if (busChildren > 0) {
			auto* busRootItem = new QTreeWidgetItem(
					{QString("%1").arg(dev->domain),
					 QString("%1").arg(dev->bus),
					 QString("%1").arg(dev->dev),
					 QString("%1").arg(dev->func),
					 QString("%1").arg(name)});
			busRootItem->setExpanded(true);

			for (auto o = 0; d+o < devList
			.size() && devList[d+o]->bus ==
			dev->bus; o++) {
				auto* childBusItem = new QTreeWidgetItem(
						{QString("%1").arg(dev->domain),
						 QString("%1").arg(dev->bus),
						 QString("%1").arg(dev->dev),
						 QString("%1").arg(dev->func),
						 QString("%1").arg(name)});
				childBusItem->setExpanded(true);
				busRootItem->insertChild
				(busRootItem->childCount(),
				childBusItem);
			}
			m_List += busRootItem;
		}

	}
}
PCIDeviceTreeData::~PCIDeviceTreeData()
{
	pci_cleanup(m_pciacc);
}

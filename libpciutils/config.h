#ifndef PCI_CONFIG_H
#define PCI_CONFIG_H
#define PCI_ARCH_X86_64

#if defined(PCI_ARCH_X86_64) || defined(PCI_ARCH_I386)
#define PCI_HAVE_PM_INTEL_CONF
#endif
#ifdef LINUX
#define PCI_OS_LINUX
#define PCI_HAVE_HWDB
#define PCI_HAVE_PM_LINUX_SYSFS
#define PCI_HAVE_PM_LINUX_PROC
#define PCI_HAVE_LINUX_BYTEORDER_H
#define PCI_PATH_PROC_BUS_PCI "/proc/bus/pci"
#define PCI_PATH_SYS_BUS_PCI "/sys/bus/pci"
#define PCI_HAVE_64BIT_ADDRESS
#endif
#define PCI_IDS "pci.ids"
#endif /* PCI_CONFIG_H */

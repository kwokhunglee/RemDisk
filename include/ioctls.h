
#ifndef __REMBUS_IOCTLS_H__
#define __REMBUS_IOCTLS_H__


#include "general-types.h"


#define IOCTL_REMBUS_DISK_CREATE					CTL_CODE(FILE_DEVICE_UNKNOWN, 0x01, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_REMBUS_DISK_START						CTL_CODE(FILE_DEVICE_UNKNOWN, 0x02, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_REMBUS_DISK_STOP						CTL_CODE(FILE_DEVICE_UNKNOWN, 0x03, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_REMBUS_DISK_REMOVE					CTL_CODE(FILE_DEVICE_UNKNOWN, 0x04, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_REMBUS_DISK_SET_SETTINGS				CTL_CODE(FILE_DEVICE_UNKNOWN, 0x05, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_REMBUS_DISK_GET_SETTINGS				CTL_CODE(FILE_DEVICE_UNKNOWN, 0x06, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_REMBUS_DISK_ENUMERATE					CTL_CODE(FILE_DEVICE_UNKNOWN, 0x07, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_REMBUS_DISK_SAVE						CTL_CODE(FILE_DEVICE_UNKNOWN, 0x08, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_REMBUS_DISK_LOAD						CTL_CODE(FILE_DEVICE_UNKNOWN, 0x09, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_REMBUS_DISK_PASSWORD_CHANGE			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0a, METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_REMBUS_INFO							CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0b, METHOD_BUFFERED, FILE_ANY_ACCESS)


typedef struct _IOCTL_REMBUS_DISK_CREATE_INPUT {
	ULONG DiskNumber;
	EREMDiskType Type;
	ULONG Flags;
	HANDLE FileHandle;
	LARGE_INTEGER ImageSize;
	UCHAR Password[128];
} IOCTL_REMBUS_DISK_CREATE_INPUT, *PIOCTL_REMBUS_DISK_CREATE_INPUT;

typedef struct _IOCTL_REMBUS_DISK_START_INPUT{
	ULONG DiskNumber;
} IOCTL_REMBUS_DISK_START_INPUT, *PIOCTL_REMBUS_DISK_START_INPUT;

typedef struct _IOCTL_REMBUS_DISK_LOAD_INPUT {
	ULONG DiskNumber;
	HANDLE FileHandle;
} IOCTL_REMBUS_DISK_LOAD_INPUT, *PIOCTL_REMBUS_DISK_LOAD_INPUT;

typedef struct _IOCTL_REMBUS_DISK_SAVE_INPUT {
	ULONG DiskNumber;
	HANDLE FileHandle;
} IOCTL_REMBUS_DISK_SAVE_INPUT, *PIOCTL_REMBUS_DISK_SAVE_INPUT;

typedef struct _IOCTL_REMBUS_DISK_REMOVE_INPUT {
	ULONG DiskNumber;
} IOCTL_REMBUS_DISK_REMOVE_INPUT, *PIOCTL_REMBUS_DISK_REMOVE_INPUT;

typedef struct _IOCTL_REMBUS_DISK_STOP_INPUT {
	ULONG DiskNumber;
} IOCTL_REMBUS_DISK_STOP_INPUT, *PIOCTL_REMBUS_DISK_STOP_INPUT;


typedef struct _REMDISK_INFORMATION_ENTRY {
	ULONG NextEntryOffset;
	ULONG DiskNumber;
	LARGE_INTEGER DiskSize;
	ULONG ParentDiskNumber;
	ULONG Flags;
	EREmDiskInfoState State;
	EREMDiskType Type;
	ULONG FileNameOffset;
	ULONG FileNameLength;
} REMDISK_INFORMATION_ENTRY, *PREMDISK_INFORMATION_ENTRY;


typedef struct _IOCTL_REMBUS_DISK_GET_SETTINGS_INPUT {
	ULONG DiskNumber;
} IOCTL_REMBUS_DISK_GET_SETTINGS_INPUT, *PIOCTL_REMBUS_DISK_GET_SETTINGS_INPUT;


typedef struct _IOCTL_REMBUS_DISK_GET_SETTINGS_OUTPUT {
	REMDISK_INFORMATION_ENTRY Entry;
} IOCTL_REMBUS_DISK_GET_SETTINGS_OUTPUT, *PIOCTL_REMBUS_DISK_GET_SETTINGS_OUTPUT;


typedef struct _IOCTL_REMBUS_DISK_ENUMERATE_OUTPUT {
	ULONG Count;
	REMDISK_INFORMATION_ENTRY Entry;
} IOCTL_REMBUS_DISK_ENUMERATE_OUTPUT, *PIOCTL_REMBUS_DISK_ENUMERATE_OUTPUT;


typedef enum _EREMDiskSettingsClass {
	rdscWritable,
	rdscReadOnly,
	rdscAllocate,
	rdscDeallocate,
	rdscDiskNumber,
	rdscSaveOnRemoval,
	rdscSectorSize,
	rdscMaxTransferSize,
	rdscCopyOnWrite,
	rdscXEXEncryption,
	rdscEncrypt,
	rdscDecrypt,
} EREMDiskSettingsClass, *PEREMDiskSettingsClass;


typedef struct _IOCTL_REMBUS_DISK_SET_SETTINGS_INPUT {
	ULONG DiskNumber;
	EREMDiskSettingsClass Type;
	union {
		ULONG NewDiskNumber;
		ULONG SectorSize;
		ULONG MaxTransferLength;
		struct {
			ULONG ParentDiskNumber;
		} CopyOnWrite;
		struct {
			ULONG FileNameOffset;
			ULONG FileNameLength;
		} SaveOnRemoval;
		struct {
			UCHAR Password[128];
			UCHAR OldPassword[128];
		} XEXEncryption;
	} Data;
} IOCTL_REMBUS_DISK_SET_SETTINGS_INPUT, *PIOCTL_REMBUS_DISK_SET_SETTINGS_INPUT;


typedef enum _ERemDiskPasswordChangeType {
	rdpcSet,
	rdpcChange,
	rdpcClear,
	rdpcSetEncryptedFooter,
} ERemDiskPasswordChangeType, *PERemDiskPasswordChangeType;

typedef struct _IOCTL_REMBUS_DISK_PASSWORD_CHANGE_INPUT{
	ULONG DiskNumber;
	ERemDiskPasswordChangeType ChangeType;
	UCHAR Password[128];
	UCHAR OldPassword[128];
} IOCTL_REMBUS_DISK_PASSWORD_CHANGE_INPUT, *PIOCTL_REMBUS_DISK_PASSWORD_CHANGE_INPUT;

typedef struct _IOCTL_REMBUS_INFO_OUTPUT{
	REM_DRIVERS_INFO DriversInfo;
} IOCTL_REMBUS_INFO_OUTPUT, *PIOCTL_REMBUS_INFO_OUTPUT;



#endif 
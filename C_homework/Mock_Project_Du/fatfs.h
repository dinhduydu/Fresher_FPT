/**
 * @file fatfs.h
 * @author Dinh Duy Du (DuDD@fsoft.com.vn)
 * @brief This file contains all the functions prototypes for the FAT file system
 * @brief FatFs is a lightweight software library for microcontrollers and embedded systems that implements FAT/exFAT file system support.
 * @brief FatFs is used in low-power Embedded systems where memory is limited, since the library takes up little space in RAM and program code. 
 * @brief In the minimum version, the working code takes from 2 to 10 kB of RAM
 * @version 0.1
 * @date 2022-08-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __UINT_H_
#define __UINT_H_
#include <stdint.h>
#include <stdbool.h>
#endif /* __UINT_H_ */

#ifndef __FATFS_H_
#define __FATFS_H_
/*****************************************************************************
 * Macro and function like macro definitions
 **************************************************************************/
#define FATFS_BOOT_SECTOR 0U                                                      /* Define sector of boot sector which is alway 0 */
#define FATFS_CONVERT_TO_16_BIT(x,y) (uint16_t)(((uint8_t)(x)<< (8U)) | ((uint8_t)(y)))     /* Define macro function to convert 1 byte to 2 byte(8 bit - 16 bit) */
#define FATFS_CONVERT_TO_32_BIT(x,y) (uint32_t)(((uint16_t)(x)<< (16U)) | ((uint16_t)(y)))  /* Define macro function to convert 2 byte to 4 byte(16 bit - 32 bit */
#define FATFS_PHYSICAL_SECTOR_NUMBER(x) (uint32_t)(33U+((uint32_t)x)-2U)

/*******************************************************************************
* Structype Types
******************************************************************************/

/* Struct stores byte information of entry in Root Directory*/
typedef struct directory_entry_struct
{
	uint8_t DIR_FileName[11];										/* The short file name of directory, offset: 0x00 - 0x07 */
	uint8_t DIR_Extension[3];										/* The extention of file name, offset: 0x08 - 0x0A */
	/* If folder, we use file name with 11 element instead file name with 8 element*/
	uint8_t DIR_Attribute;											/* The status of attribute of directory entry, offset: 0x0B */
	uint8_t DIR_NTRes;											/* Reserved for Windows, offset: 0x0C */
	uint16_t DIR_FstClusHI;										/* High word of this entry's first cluster number, offset: 0x14 - 0x15 */
	uint16_t DIR_WrtTime;										/* Save the last modified of directory (time): 0x16 - 0x17 */
	uint16_t DIR_WrtDate;										/* Save the last modified of directory (date): 0x18 - 0x19 */
	uint16_t DIR_FstClusLO;										/* Low word of this entry's first cluster number, offset: 0x1A - 0x1B */
	uint32_t DIR_FileSize;											/* The file size of directory, offset: 0x1C - 0x1F */
	uint8_t FATDirecStruct[32];									/* The buffer to store all data of entry directory 
																	The FAT directory is a "file" composed of a linear list of 32-bytes structures */
} fatfs_directory_entry_struct;

/* Struct stores byte information of Boot Sector and BIOS Parameter Block */
typedef struct BPB_struct
{
	/* This is struct stores byte information of BPB */
    uint16_t BPB_BytsPerSec;             						/* The byte per sector in FAT, offset: 0x0B - 0x0C */
    uint8_t BPB_SecPerClus;           							/* The sector per cluster in FAT, offset: 0x0D */
	uint16_t BPB_RsvdSectCnt;									/* The number or reserved sector, offset: 0x0E - 0x0F */
    uint8_t BPB_NumFATs;                						/* The Number of FAT, offset: 0x10 */
	uint16_t BPB_RootEntCnt;                                    /* This field contains the count of 32-byte directory entries in the root directory, (rootEntCnt*32) % (byte per cluster) = 0, offset: 0x11 - 0x12*/
    uint16_t BPB_TotSec16;										/* Count of sectors on 4 region of the volumme. 
																	If this field = 0x1000, this field must be 0, goto totSec32 instead, offset 0x13 - 0x14 */
	uint16_t BPB_FATSz16;										/* Count of sectors occupied bye ONE FAT. 
																	In FAT32 volume, this field must be 0,  offset 0x16 - 0x17 */
    uint32_t BPB_TotSec32;          							/* This field is the new 32-bit total count of sectors on the volume. 
																	This count includes the count of all sectors in all four regions of the volume, offset: 0x20 - 0x23*/
	/* Here is the structure for FAT32 starting at offset 0x24 of the boot sector */
	uint32_t BPB_FATSz32;										/* This field is only exist in FAT32
																	count of sector occupied bye ONE FAT. */
	/* This is struct stores byte information of Boot Sector */
	uint8_t BS_OEMName[8];										/* Indication of what system formatted the volume, offset: 0x03 - 0x0A */
	uint32_t BS_VolID;                  						/* Volume serial number, offset: 0x27 - 0x2A */
	uint32_t BPB_RootClus;										/* Only in FAT32 media */
	uint32_t BS_VolID_32;										/* Volume serial number, offset: 0x43 - 0x47 */
} fatfs_BPB_infor_struct;

/* Linked list struct - stores all folders */
typedef struct entry_list
{
	fatfs_directory_entry_struct entry;									/* The entry of directory */
	struct entry_list *next;									/* Pointer to next entry(node), dynamic linked list */
} fatfs_entry_list_struct;

/* Struct stores byte information realated to FAT table or sector of Root Directory and Data Area*/
typedef struct data_fatfs_struct
{
    uint8_t* FATTable_info;             /* The storage area of FAT table when reading floppy disk*/
    uint32_t sectorOfDataArea;          /* The sector of Data Area*/
    uint32_t endOfFile;                 /* The end of file, FAT12 and FAT16: 0xFFF*/
}fatfs_data_struct;

/* Struct stores calculate byte */
typedef struct calculate_fatfs_struct
{
	uint32_t RootDirSectors;			/* The count of sectors occupied by the root directory */
	uint32_t FirstDataSector;			/* The start of the data region, the first sector of cluster 2 */
	uint32_t DataSec;					/* Total sector of data area */
	uint32_t CountofCluster;			/* Count of data cluster starting at cluster 2 */
	uint32_t FATOffset;
	uint32_t ThisFATSecNum;				/* The sector number of the FAT sector that contains the entry for cluster N in the first FAT */
	uint32_t ThisFATEntOffset;
	uint32_t FAT12ClusEntryVal;	
	uint32_t FAT16ClusEntryVal;
	uint32_t FAt32ClusEntryVAl;
	uint32_t FATSz;
	uint32_t TotSec;
	uint8_t FATType;
	uint32_t StartRootDir;
}fatfs_calculate_struct;

typedef struct _data_fatfs_struct
{
    uint8_t lastModifDateAndTime[30];                                           /* The buffer stores date of time follow format: "month/day/year hour:minute*/
    uint8_t typeOfDataOrFolder[200];                                            /* The buffer stores type of file or folder after format */
    uint8_t fileName[12];                                                       /* The buffer stores file name after format*/
} fatfs_type_file_folder_struct;

/******************************************************************************
 * Enum Type
 ******************************************************************************/

/* Define enum type of FAT type */
typedef enum fat_type
{
	FAT12 = 12,
	FAT16 = 16,
	FAT32 = 32,
} fatfs_fattype_enum;


typedef enum fat_check
{
	FATFS_CORRECT = 0,
	FATFS_ERROR_TYPE = -1,
	FATFS_ERROR_FAT_TABLE = -2
}

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/**
 * @brief Initialize information of Root Directory and  Boot Sector
 * 
 * @param filePath pointer of file
 * @param bootInfor  double pointers
 * @param headDir Head Directory of linked list
 * @return true 
 * @return false 
 */
bool fatfs_init(const uint8_t * filePath, fatfs_boot_sector_infor_struct** const bootInfor, fatfs_entry_list_struct** headDir);

/**
 * @brief Read directory
 * 
 * @param firstCluster First cluster need to access directory
 * @param headDir Double pointers of Head Directory to store linked list
 * @return true 
 * @return false 
 */
bool fatfs_readDirectory(const uint32_t firstCluster, fatfs_entry_list_struct** headDir);

/**
 * @brief Read information of file
 * 
 * @param firstCluster First cluster need to access directory
 * @param bufferFileTemp Double pointers of buffer file to store linked list
 * @param headDir Pointer of head directory of linked list directory
 * @return uint32_t - number bytes of file
 * @retval numberOfByte
 */
uint32_t fatfs_readFile(const uint32_t firstCluster, uint8_t** bufferFileTemp, fatfs_entry_list_struct* headDir);

/**
 * @brief deInitialize all pointer point to data memory
 * 
 */
void fatfs_close(void);



#endif/* __FATFS_H_*/


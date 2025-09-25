#include <stdlib.h>
#include <string.h>
#include "HAL.h"
#include "fatfs.h"
/*******************************************************************************
* Static variables
******************************************************************************/

static fatfs_BPB_infor_struct s_BPB_info;                    /* Declare static variable to store information of boot sector (BPB inside but majority) */
static fatfs_entry_list_struct *s_rootDirList = NULL;        /* Declare static variable to store information of root Directory */
static fatfs_entry_list_struct *s_subDirList = NULL;         /* Declare static variable to store information of sub directory */
static fatfs_data_struct s_fatfsdata;                        /* Declare static variable to store different value relating FAT or roof/sub directory */
static fatfs_calculate_struct s_fatfscal;                    /* Declare static variable to store different value relating FAT or roof/sub directory */
/*******************************************************************************
* Add static API prototype in C file inside :
* Prototypes
******************************************************************************/

/**
 * @brief Reading entry of directory - 32bytes/entry
 * 
 * @param buff buffer
 * @param entryNumber ordinal number of entry
 * @return pointer to point value of buffer
 */
static uint8_t *fatfs_readEntryOfDirectory(uint8_t *buffTemp, uint8_t entryNumber);

/**
 * @brief Adding node of folder in tail of linked list
 * 
 * @param headDir Pointer to point head of linked list
 * @param entryDir entry directory, entry folder (entry_struct)
 * @return return pointer point head
 */
static fatfs_entry_list_struct *fatfs_addTailDirList(fatfs_entry_list_struct *headDir, fatfs_directory_entry_struct entryDir);

/**
 * @brief Create node of folder in linked list
 * 
 * @param entryDir Entry directoryentry folder (entry_struct)
 * @return Linked list folder
 */
static fatfs_entry_list_struct *fatfs_createNodeOfFolder(fatfs_directory_entry_struct entryDir);

/**
 * @brief Read root directory
 * 
 * @param firstCluster First cluster in root directory
 * @param headDir Double pointers point to head directory
 * @return true 
 * @return false 
 */
static bool fatfs_readRootDirectory(uint32_t StartRootDir, fatfs_entry_list_struct **headDir);

/**
 * @brief Read information of FAT table
 * 
 * @param FATTable_info Pointer of FAT information
 * @return true 
 * @return false 
 */
static bool fatfs_readFATTable(uint8_t **FATTable_info);

/**
 * @brief Get next cluster in FAT table
 * 
 * @param FATTable_info Pointer of FAT information
 * @param currentCluster Current cluster
 * @return uint32_t 
 * @retval next cluster
 */
static uint32_t fatfs_getNextCluster(uint8_t *FATTable_info, uint32_t currentCluster);

/**
 * @brief Check property of entry
 * 
 * @param entryDir Variable of entry directory
 * @param headDir Double pointers point head directory
 * @return true 
 * @return false 
 */
static bool fatfs_checkPropertyOfEntry(fatfs_directory_entry_struct entryDir, fatfs_entry_list_struct **headDir);

/**
 * @brief Calculate data structure
 * 
 */
static void fatfs_dataStruct(void);

/**
 * @brief calculate FAT type
 * 
 */
static void fatfs_typeDeter(void);

/************************************************************************************************
* Code
************************************************************************************************/

bool fatfs_open(uint8_t *filePath)
{
    bool retVal = true;
    if (kmc_open_img_file(filePath) == false)
    {
        retVal = false;
    }
    return retVal;
}

bool fatfs_init(fatfs_BPB_infor_struct **BPB_info, fatfs_entry_list_struct **headDir, fatfs_calculate_struct **cal)
{
    uint8_t tempBuffer[SIZE_OF_SECTOR];
    uint8_t retVal = true;
    uint8_t index = 0U;         /* Declare variable to store OEM Name */
    uint8_t jdex = 0U;          /* Declare variable to store OEM Name */
    kmc_read_sector(FATFS_BOOT_SECTOR, tempBuffer); /* Start read Boot Sector */
    for (index = 3U; index < 11U; index++)
    {
        s_BPB_info.BS_OEMName[jdex] = tempBuffer[index];
        jdex++;
    }
    s_BPB_info.BPB_BytsPerSec = FATFS_CONVERT_TO_16_BIT(tempBuffer[12], tempBuffer[11]);
    s_BPB_info.BPB_SecPerClus = tempBuffer[13];
    s_BPB_info.BPB_RsvdSectCnt = FATFS_CONVERT_TO_16_BIT(tempBuffer[15], tempBuffer[14]);
    s_BPB_info.BPB_NumFATs = tempBuffer[16];
    s_BPB_info.BPB_RootEntCnt = FATFS_CONVERT_TO_16_BIT(tempBuffer[18], tempBuffer[17]);
    s_BPB_info.BPB_TotSec16 = FATFS_CONVERT_TO_16_BIT(tempBuffer[20], tempBuffer[19]);
    s_BPB_info.BPB_FATSz16 = FATFS_CONVERT_TO_16_BIT(tempBuffer[23], tempBuffer[22]);  
    s_BPB_info.BPB_TotSec32 = FATFS_CONVERT_TO_32_BIT((FATFS_CONVERT_TO_16_BIT(tempBuffer[35], tempBuffer[34])),(FATFS_CONVERT_TO_16_BIT(tempBuffer[33], tempBuffer[32])));
    s_BPB_info.BS_VolID = FATFS_CONVERT_TO_32_BIT((FATFS_CONVERT_TO_16_BIT(tempBuffer[42], tempBuffer[41])),(FATFS_CONVERT_TO_16_BIT(tempBuffer[40], tempBuffer[39])));
    s_BPB_info.BPB_FATSz32 = FATFS_CONVERT_TO_32_BIT((FATFS_CONVERT_TO_16_BIT(tempBuffer[39], tempBuffer[38])),(FATFS_CONVERT_TO_16_BIT(tempBuffer[37], tempBuffer[36])));
    s_BPB_info.BPB_RootClus = FATFS_CONVERT_TO_32_BIT((FATFS_CONVERT_TO_16_BIT(tempBuffer[47], tempBuffer[46])),(FATFS_CONVERT_TO_16_BIT(tempBuffer[45], tempBuffer[34])));
    s_BPB_info.BS_VolID_32 = FATFS_CONVERT_TO_32_BIT((FATFS_CONVERT_TO_16_BIT(tempBuffer[70], tempBuffer[69])),(FATFS_CONVERT_TO_16_BIT(tempBuffer[68], tempBuffer[67])));
    kmc_update_sector_size(s_BPB_info.BPB_BytsPerSec);
    fatfs_dataStruct();
    fatfs_typeDeter();
    /* Read FAT table and store in s_FATTable_info*/
    if (fatfs_readFATTable(&s_fatfsdata.FATTable_info) == true)
    {
        if (s_fatfscal.FATType == FAT12)
        {
            /* Assign value end of file is 0x0FFF*/
            s_fatfsdata.endOfFile = (uint32_t)0x0FFFU;
        }
        else if (s_fatfscal.FATType == FAT16)
        {
            /* Assign value end of file is 0xFFFF*/
            s_fatfsdata.endOfFile = (uint32_t)0xFFFFU;
        }
        else if (s_fatfscal.FATType == FAT32)
        {
            /* Assign value end of file is 0x0FFF*/
            s_fatfsdata.endOfFile = (uint32_t)0x0FFFFFFFU;
        }
        else 
        {
            retVal = false;
        }
    }
    else 
    {
        retVal = false;
    }
    fatfs_readRootDirectory(s_fatfscal.StartRootDir, headDir);    
    *BPB_info = &s_BPB_info;
    *cal = &s_fatfscal;
    return retVal;
}

void fatfs_dataStruct(void)
{
    if (s_BPB_info.BPB_FATSz16 != 0)
    {
        s_fatfscal.FATSz = s_BPB_info.BPB_FATSz16;
    }
    else
    {
        s_fatfscal.FATSz = s_BPB_info.BPB_FATSz32;
    }
    /* Start root directory */
    s_fatfscal.StartRootDir = (uint32_t)s_BPB_info.BPB_RsvdSectCnt + (s_BPB_info.BPB_NumFATs * s_fatfscal.FATSz);
    /* Determine the count of sector occupied by the Root Directory, 32-byte is size of an entry */
    s_fatfscal.RootDirSectors = ((uint32_t)(s_BPB_info.BPB_RootEntCnt)*32U + (s_BPB_info.BPB_BytsPerSec - 1U))/(s_BPB_info.BPB_BytsPerSec);
    /* Calculate the start of data region with the first sector of cluster 2 */
    s_fatfscal.FirstDataSector = (uint32_t)s_BPB_info.BPB_RsvdSectCnt + (s_BPB_info.BPB_NumFATs * s_fatfscal.FATSz) + s_fatfscal.RootDirSectors;
}

void fatfs_typeDeter(void)
{
    if (s_BPB_info.BPB_TotSec16 != 0)
    {
        s_fatfscal.TotSec = s_BPB_info.BPB_TotSec16; 
    }
    else
    {
        s_fatfscal.TotSec = s_BPB_info.BPB_TotSec32;
    }
    /* Determine the count of sectors in the data region of the volume */
    s_fatfscal.DataSec = s_fatfscal.TotSec - (s_BPB_info.BPB_RsvdSectCnt + (s_BPB_info.BPB_NumFATs * s_fatfscal.FATSz) + s_fatfscal.RootDirSectors);
    /* Determine the count of cluster */
    s_fatfscal.CountofCluster = s_fatfscal.DataSec / s_BPB_info.BPB_SecPerClus;
    if (s_fatfscal.CountofCluster < 4085)
    {
        /* There is no such thing as a FAT12 volume that has more than 4084 clusters */
        s_fatfscal.FATType = FAT12;
    }
    else if (s_fatfscal.CountofCluster < 65525)
    {
        /* There is no such thing as a FAT16 volume that less than 4085 clusters or more than 65524 clusters */
        s_fatfscal.FATType = FAT16;
    }
    else
    {
        /* There is no such thing as a FAT32 volume that has less than 65525 clusters */
        s_fatfscal.FATType = FAT32;
    }
}

uint32_t fatfs_readFile(uint32_t firstCluster, uint8_t **bufferFileTemp, fatfs_entry_list_struct *headDir)
{
    uint32_t clusterSize = 0U; /* Declare variable size of cluster. In FAT12, size of cluster = size of sector = 512 byte */
    uint32_t nextCluster = 0U; /* Declare next cluster after checking element of FAT */
    uint32_t currentCluster = 0U; /* Declare current cluster */
    uint32_t physicalSector = 0U; /* Declare Physical Sector. In FAT12, it equal sector of Data Area + FATentry - 2 */
    uint32_t numberOfSector = 0U; /* Declare number of Entry which need to read in multi sector, It mean is sector per cluster */
    fatfs_entry_list_struct *pNode = NULL; /* Declare temporary pointer is pNode to check all node in linked list */
    fatfs_entry_list_struct *pNode1 = NULL; /* Declare temporary pointer is pNode1 to check first Cluster */    
    uint8_t entryNumber = 0U; /* Declare variable of entry number in directory entry */
    uint32_t sizeOfFile = 0U;  /* Declare variable of entry number in directory entry */
    uint32_t numberOfByte = 0U;
    /* Check first cluster == first cluster in root Directory?. If have assign pNode for linked list of rootDirectory.
     *If not assign pNode for linked list of Sub Directory */
    clusterSize = (uint32_t)((uint16_t)s_BPB_info.BPB_SecPerClus * s_BPB_info.BPB_BytsPerSec);
    /* Assign End of ClusterChain */
    pNode = headDir; /* Assign headDir fo pNode*/
    /* Brow the linked list of Folder and file in roof directory*/
    while (pNode != NULL)
    {
         if (pNode->entry.DIR_FstClusLO == firstCluster)
         {	
	        /* Assign next cluster by first Cluster of pNode*/
	        nextCluster = firstCluster;
	        /* if nextCluster == 0xFFF it will end of while loop
	         * if nextCluster != 0xFFF it will read multi sector with physical sector which have been calculated with number of Entry
	         * and store in bufferFolderTemp */
	        while (nextCluster != s_fatfsdata.endOfFile)
	        {
	            currentCluster = nextCluster; /* Assign the previous nextCluster for current cluster */
	            /* Calculate next cluster follow on FAT table */
	            nextCluster = fatfs_getNextCluster(s_fatfsdata.FATTable_info, currentCluster);
	            /* Count sector to need how many sector which need to read */
	            numberOfSector++;
	            int alpha = nextCluster - s_fatfsdata.endOfFile;
	        }
	        /* Size of byte in file to allocate for memory */
	        sizeOfFile = numberOfSector * clusterSize;
	        /* Allocate memory for temp buffer*/
	        *bufferFileTemp = (uint8_t*)malloc(sizeOfFile);
	        if (*bufferFileTemp != NULL)
	        {
	            /* Calculate start physical sector*/
	            physicalSector = s_fatfscal.FirstDataSector + (firstCluster - 2U);
	            /* Read multi sector from starting cluster to end of cluster*/
	            numberOfByte = kmc_read_multi_sector(physicalSector, numberOfSector, *bufferFileTemp);
	        }      
	    }
	    pNode = pNode->next;
    }
    /* Do not free memory pointed by bufferFileTemp because app class need data here to print */
    return numberOfByte;
}

bool fatfs_readDirectory(uint32_t firstCluster, fatfs_entry_list_struct **headDir)
{
    /* Declare variable size of cluster. In FAT12, size of cluster = size of sector = 512 byte */
    uint32_t clusterSize = (uint32_t)((uint16_t)s_BPB_info.BPB_SecPerClus * s_BPB_info.BPB_BytsPerSec);
    uint32_t nextCluster = 0U;                                      /* Declare next cluster after checking element of FAT */
    uint32_t currentCluster = firstCluster;                         /* Declare current cluster */
    uint8_t *bufferFolderTemp = NULL;                                /* Initialize buffer to store byte of entry sub directory */
    uint32_t physicalSector = 0U;                                   /* Declare Physical Sector, in FAT12 = sector of Data Area + FATentry - 2 */
    uint32_t numberOfSector = 1U;                                   /* Declare number of Entry which need to read in multi sector, It mean is sector per cluster*/
    fatfs_entry_list_struct *pNode = NULL;                          /* Declare temporary pointer is pNode to check all node in linked list */
    fatfs_entry_list_struct *pNode1 = NULL;                         /* Declare temporary pointer is pNode1 to check first Cluster */
    fatfs_directory_entry_struct entryDir;                                    /* Declare variable to store value of entry */
    uint8_t entryNumber = 0U;                                       /* Declare variable of entry number in directory entry */
    bool retVal = true;

    /* To delete if *head point into memory have data*/
    if (*headDir != NULL)
    {
        free(*headDir);
        *headDir = NULL;
    }
    /* if user select option in application, it will select with first is read directory and print, second is read subdirectory */
    pNode1 = s_rootDirList;
    while (pNode1 != NULL)
    {
        if (pNode1->entry.DIR_FstClusLO == firstCluster)
        {
            pNode = s_rootDirList;
            break;
        }
        else
        {
            pNode = s_subDirList;
        }
        pNode1 = pNode1->next;
    }
    /* Initialize buffer to store cluster in Data area corresponding with fat element */
    bufferFolderTemp = (uint8_t*)malloc(clusterSize);
    if (bufferFolderTemp != NULL && pNode !=NULL)
    {
        /* Brow the linked list of Folder and file in roof directory */
        while (pNode != NULL)
        {
            /* check this node is folder and first cluster in linked list == wanting first cluster? */
            if ((pNode->entry.DIR_Attribute == 0x10U) && (pNode->entry.DIR_FstClusLO == firstCluster))
            {
                nextCluster = currentCluster; /* Assign current cluster by first Cluster of pNode */
                /* if nextCluster == 0xFFF it will end of while loop
                 * if nextCluster != 0xFFF it will read multi sector with physical sector which have been calculated with number of Entry
                 * and store in bufferFolderTemp */
                while (nextCluster != s_fatfsdata.endOfFile)
                {
                    /* Assign the previous nextCluster for current cluster */
                    currentCluster = nextCluster;
                    /* Calculate value of physical sector follow the previous nexcluster*/
                    physicalSector = s_fatfscal.FirstDataSector + (currentCluster - 2U);
                    /* Read sector at physical sector*/
                    kmc_read_multi_sector(physicalSector, numberOfSector, bufferFolderTemp);
                    /* Calculate next cluster follow on FAT table*/
                    nextCluster = fatfs_getNextCluster(s_fatfsdata.FATTable_info, currentCluster);
                    /* Count sector to need how many sector which need to read*/
                    numberOfSector++;
                }
                /* Read each entry, with entry is 32 byte, so we have 16 total entry in sector */
                for (entryNumber = 0U; entryNumber < 16U; entryNumber++)
                {
                    /* Copy all byte in 1 entry into buffer entryDir.entryDirectory */
                    memcpy(entryDir.FATDirecStruct, fatfs_readEntryOfDirectory(bufferFolderTemp, entryNumber), 32U);
                    /* Store all properties of entry in linked list */
                    retVal = fatfs_checkPropertyOfEntry(entryDir, headDir);
                }
            }
            pNode = pNode->next;
        }
        retVal = true;
        free(bufferFolderTemp);
    }
    else
    {
        retVal = false;
    }
    /* Assign head Dir for pointer of Sub Directory*/
    s_subDirList = *headDir;

    return retVal;
}

static bool fatfs_readRootDirectory(uint32_t StartRootDir, fatfs_entry_list_struct **headDir)
{
    bool retVal = true;
    uint8_t entryNumber = 0U; /* Declare variable of entry number in directory entry */
    uint16_t rootDirByteSize = (s_BPB_info.BPB_BytsPerSec * (uint16_t)s_BPB_info.BPB_SecPerClus); /* Calculate size byte of root directory */
    fatfs_directory_entry_struct entryDir; /* Declare variable temp of head directory */
	uint8_t *bufferFolderTemp = (uint8_t*)malloc(rootDirByteSize); /* Allocate buffer of folder to store information of root Directory */ 
	/* Read multi sector, with sector per cluster is read by root sector */
    kmc_read_multi_sector(StartRootDir, s_BPB_info.BPB_SecPerClus, bufferFolderTemp);
    /* Read each entry, with entry is 32 byte, so we have (BytPerClus)/(BytPerEntry) = 512/32 = 16 entries in sector */
    for (entryNumber = 0U; entryNumber < 16U; entryNumber++)
    {
        /* Copy all byte in 1 entry number N (0 - 15) into buffer entryDir.FATDirecStruct */
        memcpy(entryDir.FATDirecStruct, fatfs_readEntryOfDirectory(bufferFolderTemp, entryNumber), 32U);
        /* Check properties of entries*/
        fatfs_checkPropertyOfEntry(entryDir, headDir);
    }
    /* Assign pointer head for static variable pointer of root Directory*/
    s_rootDirList = *headDir;
    free(bufferFolderTemp);
    return retVal;
}

static uint8_t *fatfs_readEntryOfDirectory(uint8_t *buffFolderTemp, uint8_t entryNumber)
{
    uint64_t index; /* Declare index */
    /* Loop to store 32 byte of entry directory at entryNumber into tempBuffer */
    for (index = ((uint64_t)entryNumber * 32U); index < ((uint64_t)entryNumber * 32U + 32U); index++)
    {
        s_fatfscal.tempBuffer[index - ((uint64_t)entryNumber * 32U)] = buffFolderTemp[index];
    }
    return s_fatfscal.tempBuffer;
}

static bool fatfs_checkPropertyOfEntry(fatfs_directory_entry_struct entryDir, fatfs_entry_list_struct **headDir)
{
    /* File name, a.k.a short file name */
    bool retVal = true;
    /* Assign value of byte at position 11 (0x0B) for attributes*/
    entryDir.DIR_Attribute = entryDir.FATDirecStruct[11];
    /* Check entry is long file name */
    if (entryDir.DIR_Attribute == 0x0FU)
    {
        retVal = false; /* Detected long file name */
    }
    /* Check first byte of entry, if it is a 0x00 it mean empty entry or 0xE5 it mean file/subdirectory has been deleted or dot entry*/
    else if (entryDir.FATDirecStruct[0] == 0x00 || entryDir.FATDirecStruct[0] == 0xE5U || entryDir.FATDirecStruct[0] == 0x2EU)
    {
        retVal = false;
    }
    else
    {
        /* Check entry is short file name with attriibutes is 0x01, 0x20. */
        if ((entryDir.DIR_Attribute == 0x00U) || (entryDir.DIR_Attribute == 0x20U))
        {
            memset(entryDir.DIR_FileName, 0U, sizeof(entryDir.DIR_FileName)); /* Clear old name */
            memcpy(entryDir.DIR_FileName, entryDir.FATDirecStruct, 8U); /* Coppy 8 first byte into file name, short file name is a 8 first byte */
            /* Copy 3 next byte in to extension*/
            memset(entryDir.DIR_Extension, 0U, sizeof(entryDir.DIR_Extension));
            memcpy(entryDir.DIR_Extension, entryDir.FATDirecStruct + 8, 3U);
        }
        /* Check entry is folder type*/
        else if (entryDir.DIR_Attribute = 0x10U)
        {
            memset(entryDir.DIR_FileName, 0, sizeof(entryDir.DIR_FileName));
            memcpy(entryDir.DIR_FileName, entryDir.FATDirecStruct, 11U);
        }
        /* Convert byte last modified time 16 bit */
        entryDir.DIR_FstClusHI = FATFS_CONVERT_TO_16_BIT(entryDir.FATDirecStruct[21], entryDir.FATDirecStruct[20]);
        entryDir.DIR_WrtTime = FATFS_CONVERT_TO_16_BIT(entryDir.FATDirecStruct[23], entryDir.FATDirecStruct[22]);
        entryDir.DIR_WrtDate = FATFS_CONVERT_TO_16_BIT(entryDir.FATDirecStruct[25], entryDir.FATDirecStruct[24]);
        entryDir.DIR_FstClusLO = FATFS_CONVERT_TO_16_BIT(entryDir.FATDirecStruct[27], entryDir.FATDirecStruct[26]);
        entryDir.DIR_FileSize = FATFS_CONVERT_TO_32_BIT((FATFS_CONVERT_TO_16_BIT(entryDir.FATDirecStruct[31], entryDir.FATDirecStruct[30])), (FATFS_CONVERT_TO_16_BIT(entryDir.FATDirecStruct[29], entryDir.FATDirecStruct[28])));
        *headDir = fatfs_addTailDirList(*headDir, entryDir); /* Add this data into last element of linked list*/
    }
    return retVal;
}

static fatfs_entry_list_struct *fatfs_createNodeOfFolder(fatfs_directory_entry_struct entryDir)
{
    /* Allocate memory for pointer temp*/
    fatfs_entry_list_struct *tempNode = (fatfs_entry_list_struct*)malloc(sizeof(struct entry_list));
    if (tempNode != NULL)
    {
        tempNode->entry = entryDir;
        tempNode->next = NULL;
    }
    else
    {
        exit(1); /* Can't allocate memory anymore */
    }
    return tempNode;
}

static fatfs_entry_list_struct *fatfs_addTailDirList(fatfs_entry_list_struct *headDir, fatfs_directory_entry_struct entryDir)
{
    fatfs_entry_list_struct *temp = NULL;
    fatfs_entry_list_struct *pNode = NULL;
    temp = fatfs_createNodeOfFolder(entryDir);
    /* If list is empty then create first element in list */
    if (headDir == NULL)
    {
        headDir = temp;
    }
    else
    {
        pNode = headDir;
        while (pNode->next != NULL)
        {
            pNode = pNode->next;
        }
        pNode->next = temp;   
    }
    return headDir;
}

static bool fatfs_readFATTable(uint8_t **FATTable_info)
{
    bool retVal = true;
    /* Assign Size of FAT Table, with FAT12 = 512*9   */
    uint16_t FATTableSize = 0U;
    /* Definit vairable of index starting of FAT Table*/
    uint32_t startFATIndex = (uint32_t)s_BPB_info.BPB_RsvdSectCnt;
    int32_t numberOfByte = 0U; /* Declare variable to read number of byte in FAT Table and read 9 sector of FAT Table*/
    uint8_t sectorPerFAT = 0U;
    if ((s_fatfscal.FATType = FAT12 )||(s_fatfscal.FATType = FAT16))
    {
        sectorPerFAT = s_BPB_info.BPB_FATSz16;
    }
    else
    {
        sectorPerFAT = s_BPB_info.BPB_FATSz32;
    }
    FATTableSize = (s_BPB_info.BPB_BytsPerSec * s_BPB_info.BPB_FATSz16);
    *FATTable_info = (uint8_t*)malloc(FATTableSize);
    numberOfByte = kmc_read_multi_sector(startFATIndex, sectorPerFAT, *FATTable_info);
    /* Check if number of Byte equal with calculated number of byte in FAT(512*9)*/
    if (numberOfByte == (s_BPB_info.BPB_BytsPerSec * s_BPB_info.BPB_FATSz16))
    {
        retVal = true;
    }
    else
    {
        retVal = false;
    }
    return retVal;
}

static uint32_t fatfs_getNextCluster(uint8_t* FATTable_info, uint32_t currentCluster)
{
    /* Declare a variable return next value index of current cluster*/
    uint32_t retVal = 0U;
    /* Checking this is a FAT 12 type or FAT16 or FAT32*/
    if (s_fatfscal.FATType == FAT12)
    {
        /* Find position in FAT equal with current cluster, because each element is 1.5 byte in FAT*/
        s_fatfscal.FATOffset = (currentCluster * 3U) / 2U;
        /* If current Clust is odd number, it will change */
        if (currentCluster % 2U != 0)
        {
            retVal = (uint32_t)(FATFS_CONVERT_TO_16_BIT(FATTable_info[s_fatfscal.FATOffset + 1U], FATTable_info[s_fatfscal.FATOffset]) >> 4U);
        }
        /* If current Clust is even number, it will change */
        else
        {
            retVal = (uint32_t)(FATFS_CONVERT_TO_16_BIT(FATTable_info[s_fatfscal.FATOffset + 1U], FATTable_info[s_fatfscal.FATOffset]) & 0x0FFF);
        }
    }
    else if (s_fatfscal.FATType == FAT16)
    {
        s_fatfscal.FATOffset = currentCluster *2;
        retVal = (uint32_t)(FATFS_CONVERT_TO_16_BIT(FATTable_info[s_fatfscal.FATOffset + 1U], FATTable_info[s_fatfscal.FATOffset]));
    }
    else if (s_fatfscal.FATType == FAT32)
    {
        s_fatfscal.FATOffset = currentCluster *4;
        retVal = (uint32_t)FATFS_CONVERT_TO_32_BIT(FATFS_CONVERT_TO_16_BIT(FATTable_info[s_fatfscal.FATOffset + 3U], FATTable_info[s_fatfscal.FATOffset + 2U]),FATFS_CONVERT_TO_16_BIT(FATTable_info[s_fatfscal.FATOffset + 1U], FATTable_info[s_fatfscal.FATOffset])) & 0x0FFFFFF;
    }
    else
    {
        retVal = false; /* Wrong formatted */
    }
    return retVal;
}

bool fatfs_close(void)
{
    /*Free linked list of FAT Table */
    free(s_fatfsdata.FATTable_info);
    /* Free linked list of root Directory */
    free(s_rootDirList);
    /* Free linked list of Sub Directory */
    free(s_subDirList);
    kmc_close_img_file();
}

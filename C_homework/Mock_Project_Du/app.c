#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "app.h"
#include <ctype.h>
/*******************************************************************************
* Variables
******************************************************************************/

/* Declare variable of Boot Sector information*/
static fatfs_BPB_infor_struct * s_BPB_Infor = NULL;                      /* Pointer of Boot sector to mange memory which store value of information of boot sector */
static fatfs_calculate_struct *s_cal_infor = NULL;
static uint8_t s_FilePath[45] = { 0 };                                            /* Array to store path of file which is inputed by user */
static fatfs_entry_list_struct* s_entrySubDir = NULL;                           /* Pointer of head node in linked list of first SubDir */
static fatfs_entry_list_struct* s_entrySubDir1 = NULL;                          /* Pointer of head node second in linked list SubDir */
static fatfs_entry_list_struct* s_entrySubDir2 = NULL;                          /* Pointer of head node third in linked list SubDir */
static fatfs_entry_list_struct* s_entryRootDir = NULL;                          /* Pointer of root head node in linked list directory */
// static int8_t g_optionOfUser = 0;                                               /* Variable to store option from user */
static uint8_t s_FileOrFolderType = 0U;                                         /* Variable to check type is folder or file */
// static int8_t s_userOption = 0;                                                 /* To count total of all option in root Directory */
static int8_t s_userOption1 = 0;                                                /* To count total of all option in Sub Directory */
/*******************************************************************************
* Add static API prototype in C file inside :
* Prototypes
******************************************************************************/



/**
 * @brief Checking valid input from fatfs
 * 
 * @param inputBuff Pointer of buffer which stored data
 * @param checkErrorInput Variable to check error
 * @return true 
 * @return false 
 */
static bool app_checkValidInput(int8_t* inputBuff, const int8_t checkErrorInput);

/**
 * @brief Get data input from user
 * 
 * @param checkErrorInput Folder need to check/ Value of total number of folder need check
 * @return int8_t value from user if successfully and 99 if failed
 */
static int8_t app_readFirstChar(const int8_t checkErrorInput);

/**
 * @brief Printing all file or folder
 * 
 * @param list Linked list of father sub directory
 * @param option Option
 * @param Type Check type, if type == 1, this is a folder, else this is a file
 * @param listSub Linked list of son sub directory
 */
static void app_createMenu(fatfs_entry_list_struct* const list,const int8_t option, uint8_t* Type, fatfs_entry_list_struct** listSub);

/**
 * @brief Printing output information of Root Directory; Head node of sub dir
 * 
 */
static int8_t app_inforOfRootDir(void);

/**
 * @brief Printing information of sub directory
 * 
 * @param listSub head node of sub dir
 */
static void app_inforOfSubDir(fatfs_entry_list_struct *listSub);

/**
 * @brief Foramating all data which read from fatfs (attribute)
 * 
 * @param entryDir Pointer of head note in list
 */
void app_formartData(fatfs_directory_entry_struct *entryDir);

/*******************************************************************************
 * Code
 ******************************************************************************/

void app_formartData(fatfs_directory_entry_struct *entryDir)
{
    /* Declare variable of hour, minute, year, month, day */
    uint8_t hour = 0U;
    uint8_t minute = 0U;
    uint16_t year = 0U;
    uint8_t month = 0U;
    uint8_t day = 0U;
    /* Format Data Time */
    hour = (uint8_t)(entryDir->DIR_WrtTime >> 11U);
    minute = (uint8_t)((entryDir->DIR_WrtTime >> 5U) & 0x3FU);
    year = (entryDir->DIR_WrtDate >> 9U) + 1980U;
    month = (uint8_t)((entryDir->DIR_WrtDate >> 5U) & 0x0FU);
    day = (uint8_t)(entryDir->DIR_WrtDate & 0x1FU);
    memset(s_dataDisk.lastModifDateAndTime, 0, strlen(s_dataDisk.lastModifDateAndTime));
    snprintf(s_dataDisk.lastModifDateAndTime, 30, "%d/%d/%d %d:%d", month, day, year, hour, minute);
    /* Format Type of File or Directory*/
    /** This is for file: 
     * 0x01: Read only
     * 0x10 : Folder
     * 0x20: Archive
     * 0x0F: Long file name   
    */
    if (entryDir->DIR_Attribute == 0x01U || entryDir->DIR_Attribute == 0x20U)
    {
        if (strstr(entryDir->DIR_Extension, "TXT") != NULL)
        {
            memset(s_dataDisk.typeOfDataOrFolder, 0, strlen(s_dataDisk.typeOfDataOrFolder));
            memcpy(s_dataDisk.typeOfDataOrFolder, "Text Document", strlen("Text Document"));
        }
        else if (strstr(entryDir->DIR_Extension, "DOC") != NULL)
        {
            memset(s_dataDisk.typeOfDataOrFolder, 0, strlen(s_dataDisk.typeOfDataOrFolder));
            memcpy(s_dataDisk.typeOfDataOrFolder, "Microsoft Word", strlen("Microsoft Word"));
        }
        else if (strstr(entryDir->DIR_Extension, "PDF") != NULL)
        {
            memset(s_dataDisk.typeOfDataOrFolder, 0, strlen(s_dataDisk.typeOfDataOrFolder));
            memcpy(s_dataDisk.typeOfDataOrFolder, "PDF", strlen("PDF Document"));
        }
        else if (strstr(entryDir->DIR_Extension, "PNG") != NULL)
        {
            memset(s_dataDisk.typeOfDataOrFolder, 0, strlen(s_dataDisk.typeOfDataOrFolder));
            memcpy(s_dataDisk.typeOfDataOrFolder, "PNG File", strlen("PNG File"));
        }
        else
        {
            memset(s_dataDisk.typeOfDataOrFolder, 0, strlen(s_dataDisk.typeOfDataOrFolder));
            memcpy(s_dataDisk.typeOfDataOrFolder, "Unknow", strlen("Unknow"));
        }
    }
    /* This is for directory - folder */
    else if (entryDir->attribute == 0x10U)
    {
        memset(s_dataDisk.typeOfDataOrFolder, 0, strlen(s_dataDisk.typeOfDataOrFolder));
        memcpy(s_dataDisk.typeOfDataOrFolder, "Folder", strlen("Folder"));
    }
    /* Format File Name*/
    memcpy(s_dataDisk.fileName, entryDir->DIR_FileName, 8);
}

bool app_init(void)
{
    uint8_t i = 0U;
    bool retVal = true;
    printf("\n\t<>Please put your path file: ");
    gets(s_FilePath);
    /* Reading from fatfs init to read infor of boot sector and root directory*/
    retVal = fatfs_open(s_FilePath);
    if (true != retVal)
    {
        printf("\n\tERROR: Can not open file\r\n");
    }
    /* Printing value of boot sector*/
    else
    {
        fatfs_init(&s_bootInfor, &s_entryRootDir);
    	system("cls");
        printf("\n\t\t\t\t*********************Boot Sector Information********************\n\n");
        printf("\n\t- OEM Name: %c", s_BPB_Infor->BS_OEMName);
        printf("\n\t- FAT Type: FAT%d", s_cal_infor->FATType);
        printf("\n\t- Byte Per Sector: %d byte", s_BPB_Infor->BPB_BytsPerSec);
        printf("\n\t- Sector Per Cluster: %d byte", s_BPB_Infor->BPB_SecPerClus);
        printf("\n\t- Number of reserved sectors: %d byte", s_BPB_Infor->BPB_RsvdSectCnt);
        printf("\n\t- Number of FAT on disk: %d", s_BPB_Infor->BPB_NumFATs);
        printf("\n\t- Maximum number of root directory entries: %d", s_BPB_Infor->BPB_RootEntCnt);
        if ((s_cal_infor->FATType = FAT12)||(s_cal_infor->FATType = FAT12))
        {
            printf("\n\t- Sectors per FAT: %d", s_BPB_Infor->BPB_FATSz16);
            printf("\n\t- Total sector count: %d sectors", s_BPB_Infor->BPB_TotSec16);
            printf("\n\t- VolumeID: %d", s_BPB_Infor->BS_VolID);
        }
        else
        {
            printf("\n\t- Sectors per FAT: %d", s_BPB_Infor->BPB_FATSz32);
            printf("\n\t- Total sector count: %d sectors", s_BPB_Infor->BPB_TotSec32);
            printf("\n\t- VolumeID: %d", s_BPB_Infor->BS_VolID_32);
        }
    }
    return retVal;
}

void app_createMenuOption(void)
{
    int8_t userOption;
    int8_t optionOfUser;
    /* Print infor of Root Directory*/
    userOption = app_inforOfRootDir();
    /* Waiting user input*/
    optionOfUser = app_readFirstChar(s_userOption);
    /* if user input valid value, user will input again*/
    while (optionOfUser == 99U)
    {
        optionOfUser = app_readFirstChar(s_userOption);
    }
    /* if user input right*/
    while(optionOfUser > 0)
    {
        /* Print file of foler, those which user want to choose, then assign s_entrySubDir with head of Sub Dir Linked List
        * with father sub is a rootDir and son Sub is s_entrySubDir */
        app_createMenuOnRootDir(s_entryRootDir, g_optionOfUser, &s_FileOrFolderType, &s_entrySubDir);
        /* if node in list is folder, user need to option in new folder
        * if not, this is a file, just print and user need to option in current folder- at that time this is a root dir */
        if (s_FileOrFolderType == 1)
        {
            g_optionOfUser = app_IO_readFirstChar(s_userOption1);
            /* User choose one otion in new dir, if value == 0 it will back father folder*/
            while (g_optionOfUser != 0)
            {
                /* Print infor of file of folder in next SubDir and assign for next son SubDir */
                app_createMenuOnRootDir(s_entrySubDir, g_optionOfUser, &s_FileOrFolderType, &s_entrySubDir1);
                /* If sub folder have file, user will choose option , but if folder empty, user jsut back current father Dir*/
                if ((s_FileOrFolderType == 1) && (s_userOption1) != 0)
                {
                    g_optionOfUser = app_IO_readFirstChar(s_userOption1);
                    while (g_optionOfUser != 0)
                    {
                        app_createMenuOnRootDir(s_entrySubDir1, g_optionOfUser, &s_FileOrFolderType, &s_entrySubDir2);
                        if (s_FileOrFolderType == 1)
                        {
                            g_optionOfUser = app_IO_readFirstChar(s_userOption1);
                            while (g_optionOfUser != 0)
                            {
                                g_optionOfUser = app_IO_readFirstChar(s_userOption1);
                            }
                        }
                        app_IO_inforOfSubDir(s_entrySubDir1);
                        s_userOption1 = 1;
                        g_optionOfUser = app_IO_readFirstChar(s_userOption1);
                    }
                     s_userOption1 = 3;
                    app_IO_inforOfSubDir(s_entrySubDir);
                }
                g_optionOfUser = app_IO_readFirstChar(s_userOption1);
            }
            app_IO_inforOfRootDir();
        }
        g_optionOfUser = app_IO_readFirstChar(s_userOption);
        /* If user choose 0, it will exit program*/
        if (g_optionOfUser == 0)
        {
            printf("\n\t<>Exit program");
        }
        /* if user input wrong value, user need to input again*/
        while (g_optionOfUser == 99)
        {
            g_optionOfUser = app_IO_readFirstChar(s_userOption);
        }
    }
}

static int8_t app_inforOfRootDir(void)
{
    fatfs_entry_list_struct* pNode = NULL;
    int8_t userOptionTemp = 1;
    printf("\n\n\t\t\t\t                    Root Directory                    \n\n");
    printf("\t\t%-16s %-20s %-20s %-20s %s\n", "Option", "Name", "Date modified", "Type", "Size");
    for (pNode = s_entryRootDir; pNode != NULL; pNode = pNode->next)
    {
        app_formartData(&pNode->entry);
        printf("\t\t%-16d %-20s %-20s %-20s %d\n", userOptionTemp, (uint8_t*)s_dataDisk.fileName, (uint8_t*)s_dataDisk.lastModifDateAndTime, (uint8_t*)s_dataDisk.typeOfDataOrFolder, pNode->entry.DIR_FileSize);
        userOptionTemp++;
    }
    printf("\n\tNOTICE: Choose 0 to exit program");
    return userOptionTemp;
}

static void app_createMenuOnRootDir(fatfs_entry_list_struct *list, int8_t option, uint8_t *Type, fatfs_entry_list_struct **listSub)
{
    int8_t checkNode = 1; /* Declare variable checkNode is a index to find right node in linked list */
    int8_t position = option; /* Declare variable position in linked, it is assigned by option from user */
    fatfs_entry_list_struct* pNode = list; /* Declare pointer pNode to brow all node in linked lit */ /* Assign pNode for head node of father sub */
    static uint8_t check = 0U; /* Declare variable to check folder which have initialize before */
    uint32_t index = 0U;
    uint8_t* bufferFileTemp = NULL;
    int8_t userOptionTemp = 0;
    /* Brow all node in linked to find right position*/
    while (pNode != NULL && checkNode != position)
    {
        pNode = pNode->next;
        checkNode++;
    }
    if (pNode != NULL)
    {
        /* If node is a file*/
        if (pNode->entry.attribute == 0x01U || pNode->entry.attribute == 0x20U)
        {
        /* initialize buffer to store data, and size is a fileSize of node in linked list*/
            bufferFileTemp = (uint8_t*)malloc((pNode->entry.DIR_FileSize));
            fatfs_readFile(pNode->entry.firstCluster, &bufferFileTemp, list);
            for (index = 0; index < pNode->entry.fileSize; index++)
            {
                printf("%c", bufferFileTemp[index]);
            }
            *Type = 0U; /* Assign type = 0 if this is a file */
            free(bufferFileTemp);
        }
        /* if node is a folder*/
        else if (0x10U == pNode->entry.attribute )
        {
            /* read directory with first cluster, and store son folder into list sub*/
            fatfs_readDirectory(pNode->entry.firstCluster, listSub);
            printf("\n\n\t\t%70s", "*********************Sub Directory********************\n\n");
            for (pNode = *listSub; pNode != NULL; pNode = pNode->next)
            {
                app_formartData(&pNode->entry);
                printf("\t\t%-16d %-30s %-30s %-30s %d\n", (userOptionTemp + 1), (int8_t*)s_dataDisk.fileName, (int8_t*)s_dataDisk.lastModifDateAndTime, (int8_t*)s_dataDisk.typeOfDataOrFolder, pNode->entry.DIR_FileSize);
                userOptionTemp++; /* Count total file and folder in sub directory*/
            }
            *Type = 1U; /* Assign type = 1 if this is a folder */
            check++;
            s_userOption1 = userOptionTemp;
            printf("\n\tNOTICE: Choose 0 to back root directory");
        }
    }
    else 
    {
        printf("\n\tCan't find that position\n");
    }
}



static void app_inforOfSubDir(fatfs_entry_list_struct* listSub)
{
    uint8_t i = 1U;
    fatfs_entry_list_struct *pNode = NULL;
    int8_t userOptionTemp = 0;

    printf("\n\n\t\t%96s", "*********************Sub Directory********************\n\n");
    printf("\t\t%-16s %-20s %-20s %-20s %s\n", "Option", "Name", "Date modified", "Type", "Size");
    /* Brow pNode into list sub to printf data of son folder*/
    for (pNode = listSub; pNode != NULL; pNode = pNode->next)
    {
        fatfs_formartData(&pNode->entry);
        printf("\t\t%-16d %-30s %-30s %-30s %d\n", (userOptionTemp + 1), (int8_t*)s_dataDisk.fileName, (int8_t*)s_dataDisk.lastModifDateAndTime, (int8_t*)s_dataDisk.typeOfDataOrFolder, pNode->entry.DIR_FileSize);
        /* Count total file or folder in son directory*/
        userOptionTemp++;
    }
}



static bool app_checkValidInput(int8_t *inputBuff, const int8_t checkErrorInput)
{
    bool retVal = true;
    uint8_t index = 0U;

    /* Check value input <0 or > total number file or folder or > 100*/
    if ((int8_t)atoi(inputBuff) < 0 || (int8_t)atoi(inputBuff) > checkErrorInput || (int8_t)atoi(inputBuff) > 100)
    {
        printf("\n\n\tERROR: Only enter value from 0 - %d!!", checkErrorInput);
        retVal = false;
    }
    /* Check value input have alphabet data */
    for(index = 0; index < strlen(inputBuff); index++)
    {
        if ((isalpha(inputBuff[index]) != 0) || inputBuff[index] == '.')
        {
            printf("\n\n\tERROR: Only enter integer Type!!");
            retVal = false;
            break;
        }
    }
    return retVal;
}

static int8_t app_readFirstChar(const int8_t checkErrorInput)
{
    int8_t inputBuff[2] = { 0 };
    int8_t retVal = 0;
    bool checkBool = false;
    printf("\n\n\t<>Choose one option: ");
    rewind(stdin);
    fgets(inputBuff, sizeof(inputBuff), stdin);
    checkBool = app_IO_checkValidInput(inputBuff, checkErrorInput);
    if (checkBool == true)
    {
        retVal = (int8_t)atoi(inputBuff);
    }
    else
    {
        retVal = 99;
    }
    return retVal;
}




void app_close(void)
{
    free(s_entrySubDir1);
    free(s_entrySubDir2);
    fatfs_close();
}





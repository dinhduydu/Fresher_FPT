/**
 * @file app.h
 * @author Dinh Duy Du (DuDD@fsoft.com.vn)
 * @brief 
 * @version 0.1
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __APP_H_
#define __APP_H_
#include "fatfs.h"
/*******************************************************************************
* Structure types
******************************************************************************/

typedef struct data_app_struct
{
    uint8_t lastModifDateAndTime[30];                                            /* The buffer stores date of time follow format: "month/day/year hour:minute*/
    uint8_t typeOfDataOrFolder[10];                                            /* The buffer stores type of file or folder after format */
    uint8_t fileName[12];                                                       /* The buffer stores file name after format*/
} app_type_file_folder_struct;

/*******************************************************************************
 * API
 ******************************************************************************/
 
/**
 * @brief Inputing from user
 * 
 * @return true 
 * @return false
 * @retval return true if successfully and failed if failed 
 */
bool app_init(void);

/**
 * @brief Creating menu for user 
 * 
 */
void app_createMenuOption(void);

/**
 * @brief close file
 * 
 * @return true if close success
 * @return false if closed
 */
bool app_close(void);

#endif/* _APP_H_ */


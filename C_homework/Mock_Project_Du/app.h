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
 * @brief 
 * 
 */
void app_close(void);;

#endif/* _APP_H_ */

#ifndef _MAIN_H_
#define _MAIN_H_

/******************************************************************************
 * Include
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

/******************************************************************************
 * Macro
 ******************************************************************************/

#define byte_sector 512
#define byte_entry 32
#define max_entry 16
#define sector_fat 9
#define sector_boot 1
#define check_sub_entry 11
#define start_cluster_ 26

void menu();
#endif 

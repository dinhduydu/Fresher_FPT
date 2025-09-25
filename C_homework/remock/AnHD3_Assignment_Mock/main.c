/******************************************************************************
 * Include
 ******************************************************************************/
#include "app.h"

/******************************************************************************
 * Code
 ******************************************************************************/

uint8_t buff[byte_sector];
uint8_t sub_buff[byte_sector];

void main(void) 
{
    bool retVal = true;
    /* check input of app*/
    retVal = app_init();
    /* if initialize faile, user need to input again*/
    while (retVal != true)
    {
        retVal = app_init();
    }
    /* option of user*/
    app_createMenuOption();
    /* deinitialize*/
    app_close();
}



int main(void)
{


    return 0;
}


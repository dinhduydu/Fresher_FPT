#include "app.h"

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

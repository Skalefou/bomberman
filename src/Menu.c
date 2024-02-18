#include "Menu.h"

extern int mode;

void Menu_DisplayMenu(){
    Graphics_DisplayMenu();
    if(mode == 2){
        Multiplayer_DisplayMenu();
    }
}

void Multiplayer_DisplayMenu(){
    Graphics_Menu_Multi_Display();
}
#include "Menu.h"

extern int mode;

void Menu_DisplayMenu(){
    Graphics_DisplayMenu();
    if(mode == 2){
        Multiplayer_DisplayMenu();
    }
    if(mode == 3){
        Display_JoinMenu();
    }
    if(mode == 4){
        Display_Lobby();
    }
}

void Multiplayer_DisplayMenu(){
    Graphics_Menu_Multi_Display();
}

void Display_Lobby(){
    Multiplayer_Lobby();
    TTF_Init();
    //const char* text = "Your text here";
    DisplayIP();
}

void Display_JoinMenu(){
    Multiplayer_Join();
}
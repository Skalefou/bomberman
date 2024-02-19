#include "Menu.h"

extern int mode;

void Menu_DisplayMenu(){
    Graphics_DisplayMenu();
    if(mode == 2){
        Multiplayer_DisplayMenu();
    }
    if(mode == 3){
        Display_JoinMenu();
        printf("Display_JoinMenu\n");
    }
    if(mode == 4){
        Display_Lobby();
        printf("Display_Lobby\n");
    }
}

void Multiplayer_DisplayMenu(){
    Graphics_Menu_Multi_Display();
}

void Display_Lobby(){
    Multiplayer_Lobby();
    //TTF_Init();
    //const char* text = "Your text here";
    //DisplayIP();
    printf("Display_Lobby\n");
}

void Display_JoinMenu(){
    Multiplayer_Join();
}
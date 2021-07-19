/*==========================================
        Retro Tennis 2
        - ZombieNW -

        Created using GRRLIB and DevKitPro
============================================*/
#include <grrlib.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <stdio.h>
#include <asndlib.h>
#include <mp3player.h>

//IR Pointers
#include "player1_hand_texture_png.h"
//Buttons
#include "button_png.h"
#include "button_highlighted_png.h"
#include "icon_button_png.h"
#include "icon_button_highlighted_png.h"
#include "triangle_button_png.h"
#include "triangle_button_highlighted_png.h"
#include "left_triangle_button_png.h"
#include "left_triangle_button_highlighted_png.h"
//Fonts
#include "Rubik_ttf.h"
#include "LCDSolid_ttf.h"
//Bgs/Decor
#include "options_background_png.h"
#include "pause_background_png.h"
#include "court_png.h"
#include "wii_warning_png.h"
#include "popup_png.h"
#include "logo_png.h"
//Objects
#include "ball_png.h"
#include "trophy_png.h"
#include "right_paddle_png.h"
#include "left_paddle_png.h"
//Sounds
#include "opening_mp3.h"
#include "optionsmusic_mp3.h"
#include "score_mp3.h"
#include "wallbounce_mp3.h"
#include "win_mp3.h"

//Variables
ir_t P1Mote; //Player 1 wiimote
GRRLIB_texImg *GFX_player1_hand_texture; //Player 1 IR Pointer
GRRLIB_texImg *GFX_button_texture; //Button
GRRLIB_texImg *GFX_button_highlighted_texture; //Button Highlighted
GRRLIB_texImg *GFX_icon_button_texture; //icon Button
GRRLIB_texImg *GFX_icon_button_highlighted_texture; //icon Button Highlighted
GRRLIB_texImg *GFX_options_background_texture;
GRRLIB_texImg *GFX_pause_background_texture;
GRRLIB_texImg *GFX_triangle_button_texture;
GRRLIB_texImg *GFX_triangle_button_highlighted_texture;
GRRLIB_texImg *GFX_left_triangle_button_texture;
GRRLIB_texImg *GFX_left_triangle_button_highlighted_texture;
GRRLIB_texImg *GFX_court_texture;
GRRLIB_texImg *GFX_wii_warning_texture;
GRRLIB_texImg *GFX_right_paddle_texture;
GRRLIB_texImg *GFX_left_paddle_texture;
GRRLIB_texImg *GFX_ball_texture;
GRRLIB_texImg *GFX_popup_texture;
GRRLIB_texImg *GFX_trophy_texture;
GRRLIB_texImg *GFX_logo_texture;

//Functions
void ExitGame(){
    GRRLIB_FreeTexture(GFX_player1_hand_texture);
    GRRLIB_FreeTexture(GFX_button_texture);
    GRRLIB_FreeTexture(GFX_button_highlighted_texture);
    GRRLIB_FreeTexture(GFX_icon_button_texture);
    GRRLIB_FreeTexture(GFX_icon_button_highlighted_texture);
    GRRLIB_FreeTexture(GFX_triangle_button_texture);
    GRRLIB_FreeTexture(GFX_triangle_button_highlighted_texture);
    GRRLIB_FreeTexture(GFX_left_triangle_button_texture);
    GRRLIB_FreeTexture(GFX_left_triangle_button_highlighted_texture);
    GRRLIB_FreeTexture(GFX_options_background_texture);
    GRRLIB_FreeTexture(GFX_pause_background_texture);
    GRRLIB_FreeTexture(GFX_court_texture);
    GRRLIB_FreeTexture(GFX_wii_warning_texture);
    GRRLIB_FreeTexture(GFX_right_paddle_texture);
    GRRLIB_FreeTexture(GFX_left_paddle_texture);
    GRRLIB_FreeTexture(GFX_ball_texture);
    GRRLIB_FreeTexture(GFX_popup_texture);
    GRRLIB_FreeTexture(GFX_trophy_texture);
    GRRLIB_FreeTexture(GFX_logo_texture);
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
    SYS_ResetSystem(SYS_RETURNTOMENU, 0, 0);//Power-Off System
}

int main(int argc, char **argv) {
    //Inits
    GRRLIB_Init();//Graphics/Video Init
    WPAD_Init();//Wiimote Init
	ASND_Init();// Initialise the audio subsystem
	MP3Player_Init();// Initialise the audio subsystem
    WPAD_SetIdleTimeout(75);//Timeout Wiimotes after 60 seconds
    WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);//Something?
    GRRLIB_ttfFont *RubikFont = GRRLIB_LoadTTF(Rubik_ttf, Rubik_ttf_size);//Font
    GRRLIB_ttfFont *LCDSolidFont = GRRLIB_LoadTTF(LCDSolid_ttf, LCDSolid_ttf_size);//Font

    //Variables
    int gamemode = 1;
    /*Gamemodes:
    0 = Splash Screen 1
    1 = Splash Screen 2
    2 = Main Menu
    3 = Gameplay Options Menu
    4 = Freeplay
    5 = Pause
    */
    u16 WinW = rmode->fbWidth; //Screen Width
    u16 WinH = rmode->efbHeight; //Screen Height
    GFX_player1_hand_texture = GRRLIB_LoadTexturePNG(player1_hand_texture_png);
    GFX_button_texture = GRRLIB_LoadTexturePNG(button_png);
    GFX_button_highlighted_texture = GRRLIB_LoadTexturePNG(button_highlighted_png);
    GFX_icon_button_texture = GRRLIB_LoadTexturePNG(icon_button_png);
    GFX_icon_button_highlighted_texture = GRRLIB_LoadTexturePNG(icon_button_highlighted_png);
    GFX_triangle_button_texture = GRRLIB_LoadTexturePNG(triangle_button_png);
    GFX_triangle_button_highlighted_texture = GRRLIB_LoadTexturePNG(triangle_button_highlighted_png);
    GFX_left_triangle_button_texture = GRRLIB_LoadTexturePNG(left_triangle_button_png);
    GFX_left_triangle_button_highlighted_texture = GRRLIB_LoadTexturePNG(left_triangle_button_highlighted_png);
    GFX_options_background_texture = GRRLIB_LoadTexturePNG(options_background_png);
    GFX_pause_background_texture = GRRLIB_LoadTexturePNG(pause_background_png);
    GFX_court_texture = GRRLIB_LoadTexturePNG(court_png);
    GFX_wii_warning_texture = GRRLIB_LoadTexturePNG(wii_warning_png);
    GFX_left_paddle_texture = GRRLIB_LoadTexturePNG(left_paddle_png);
    GFX_right_paddle_texture = GRRLIB_LoadTexturePNG(right_paddle_png);
    GFX_ball_texture = GRRLIB_LoadTexturePNG(ball_png);
    GFX_popup_texture = GRRLIB_LoadTexturePNG(popup_png);
    GFX_trophy_texture = GRRLIB_LoadTexturePNG(trophy_png);
    GFX_logo_texture = GRRLIB_LoadTexturePNG(logo_png);
    GRRLIB_SetMidHandle(GFX_player1_hand_texture, true);
    GRRLIB_SetMidHandle(GFX_options_background_texture, true);
    GRRLIB_SetMidHandle(GFX_pause_background_texture, true);
    GRRLIB_SetMidHandle(GFX_court_texture, true);
    GRRLIB_SetMidHandle(GFX_wii_warning_texture, true);
    GRRLIB_SetMidHandle(GFX_popup_texture, true);
    GRRLIB_SetMidHandle(GFX_trophy_texture, true);
    GRRLIB_SetMidHandle(GFX_logo_texture, true);
    int playerselectscreenchoice = 1;
    int number_of_players = 1;//players, starts at 1
    int player1ypos = 200; //player one position
    int player1xpos = 50; //this shouldn't change and is just for reference
    int player1width = 10; //this shouldn't change and is just for reference
    int player1height = 60; //this shouldn't change and is just for reference
    int player1score = 0; //player 1 score
    int player2ypos = 200; //player one position
    int player2xpos = 580; //this shouldn't change and is just for reference
    int player2width = 10; //this shouldn't change and is just for reference
    int player2height = 60; //this shouldn't change and is just for reference
    int player2score = 0; //player 2 score
    int overallspeed = 5; //speed of ball and paddles
    int court_bottom = 335;//court boundaries
    int court_top = 45;//court boundaries
    bool alwaystrue = true; //this is here only for formatting, go away
    int cpuselectscreenchoice = 2;
    /*Hardness:
    1 = Easy
    2 = Normal
    3 = Hard
    4 = Expert
    */
    s32 CPU_difficulty = 3; //This is the speed(in pixels) the CPU will move the bar.
    /*Hardness:
    2 = Easy
    3 = Normal
    4 = Hard
    5 = Expert
    */
    s32 ballX = 311; //Ball X position.
    s32 ballY = 190; //Ball Y position. 
    s32 ballspeedX =  rand() % 4 + 3; //Ball horitzontal speed. Changes when contacts borders or Bars.
    s32 ballspeedY = rand() % -3 + -3; //Ball vertical speed. Changes when contacts borders or Bars.
    int style = 1;
    // 1 = deluxe
    // 2 = arcade
    int gameplaymode = 1;
    // 1 = arcade
    // 2 = tennis
    u32 objectcolor = 0x000000FF;
    int pausestatus = 0;
    /*Pause Satuses
    0 = unpaused
    1 = normal pause
    2 = player 1 won
    3 = player 2 won
    4 = credits
    */
    //Ui stuff
    int pbypos = 180; //Y Position
    int pbxpos = 455; //X Position of top button
    int pbyoffset = 130; //Y Offset from top to bottom button
    float pbysize = 0.4; //y size
    float pbxsize = 0.35; //x size
    int pbytextoffset = 35;//Y offset for text
    int pbxtextoffset = 60;//x offset for text
    float pbx_hitbox_size = pbxsize * 512;
    float pby_hitbox_size = pbysize * 256;
    int selectorcooldown = 0;
    int wiiwarningcooldown = 200;

    MP3Player_PlayBuffer(opening_mp3, opening_mp3_size, NULL);

    while(1) {
        //Inits
        WPAD_ScanPads();  // Scan the Wiimotes
        WPAD_SetVRes(WPAD_CHAN_0, WinW, WinH); //Set the virtual resolution to the screen height/width from earlier
        WPAD_IR(WPAD_CHAN_0, &P1Mote); //Init IR Pointer
        u32 player1pressed = WPAD_ButtonsHeld(0);//player1 button down
        u32 player2pressed = WPAD_ButtonsHeld(1);//player2 button down
        //Variables
        int P1MX = P1Mote.sx - 150;// WiiMote IR Viewport Correction
        int P1MY = P1Mote.sy - 150;// WiiMote IR Viewport Correction
        //Selector Counter
        if(selectorcooldown > 0){
            selectorcooldown--;
        }
        //Functions
        void resetball(){
            ballX = 311; //Ball X position.
            ballY = 190; //Ball Y position.
            bool rl = true;
            if ((rand() % 2) + 1 ==  2){
                rl = false;
            }
            if (rl == true){
                ballspeedX =  rand() % 4 + 3; //rand Ball horitzontal speed
                ballspeedY = rand() % -3 + -2; //rand Ball vertical speed
            }
            else{
                ballspeedX = rand() % -4 + -5; //rand Ball horitzontal speed
                ballspeedY = rand() % 3 + 2; //rand Ball vertical speed
            }
        }
        //If players are hitting the ball
        bool player1hittingball(){
            if(ballX > player1xpos + player1width || player1xpos > ballX + 15){ //the 15 is ball width, i didn't wanna make more ints
                return false;
            }
            if(ballY > player1ypos + player1height || player1ypos > ballY + 15){ //the 15 is ball width, i didn't wanna make more ints
                return false;
            }
            MP3Player_PlayBuffer(wallbounce_mp3, wallbounce_mp3_size, NULL);
            return true;
        }
        bool player2hittingball(){
            if(ballX > player2xpos + player2width || player2xpos > ballX + 15){ //the 15 is ball width, i didn't wanna make more ints
                return false;
            }
            if(ballY > player2ypos + player2height || player2ypos > ballY + 15){ //the 15 is ball width, i didn't wanna make more ints
                return false;
            }
            MP3Player_PlayBuffer(wallbounce_mp3, wallbounce_mp3_size, NULL);
            return true;
        }
        if(gamemode == 1){
            if(wiiwarningcooldown > 0){
                GRRLIB_DrawImg(WinW / 2, WinH / 2, GFX_wii_warning_texture, 0, 0.76, 1, 0xFFFFFFFF);//Draw Trophy
                wiiwarningcooldown--;
            }
            else{
                gamemode = 2;
            }
        }
        if(gamemode == 2){ //Main Menu
            //Drawing/Rendering
            GRRLIB_SetBackgroundColour(0xE6, 0xED, 0xEC, 0xFF);//Background color
            GRRLIB_DrawImg(WinW / 2, 150, GFX_logo_texture, 0, 0.8, 0.8, 0xFFFFFFFF);//Draw Trophy

            if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME){
                ExitGame();
            }

            //Play Button
            if(GRRLIB_PtInRect(220, 330, 205, 105, P1MX, P1MY)){//If button is being hovered
                GRRLIB_DrawImg(220, 330, GFX_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button normally
                GRRLIB_PrintfTTF(295, 365, RubikFont, "Play", 24, 0x000000FF);
                if(player1pressed & WPAD_BUTTON_A && selectorcooldown == 0){
                    MP3Player_Stop();
                    MP3Player_PlayBuffer(optionsmusic_mp3, optionsmusic_mp3_size, NULL);
                    selectorcooldown = 10;
                    gamemode = 3;
                }
            }
            else{//If button is not hovered
                GRRLIB_DrawImg(220, 330, GFX_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                GRRLIB_PrintfTTF(295, 365, RubikFont, "Play", 24, 0x000000FF);
            }
            //Exit Button
            if(GRRLIB_PtInRect(430, 330, 205, 105, P1MX, P1MY)){//If button is being hovered
                GRRLIB_DrawImg(430, 330, GFX_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button normally
                GRRLIB_PrintfTTF(505, 365, RubikFont, "Exit", 24, 0x000000FF);
                if(player1pressed & WPAD_BUTTON_A && selectorcooldown == 0){
                    MP3Player_Stop();
                    ExitGame();
                }
            }
            else{//If button is not hovered
                GRRLIB_DrawImg(430, 330, GFX_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                GRRLIB_PrintfTTF(505, 365, RubikFont, "Exit", 24, 0x000000FF);
            }
            //Credits Button
            if(GRRLIB_PtInRect(10, 330, 205, 105, P1MX, P1MY)){//If button is being hovered
                GRRLIB_DrawImg(10, 330, GFX_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button normally
                GRRLIB_PrintfTTF(65, 365, RubikFont, "Credits", 24, 0x000000FF);
                if(player1pressed & WPAD_BUTTON_A && selectorcooldown == 0){
                    gamemode = 5;
                    pausestatus = 4;
                    selectorcooldown = 10;
                }
            }
            else{//If button is not hovered
                GRRLIB_DrawImg(10, 330, GFX_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                GRRLIB_PrintfTTF(65, 365, RubikFont, "Credits", 24, 0x000000FF);
            }
            if (P1Mote.state == 1) {//If wii pointer active, try to keep this the last thing rendered
                GRRLIB_DrawImg( P1MX, P1MY, GFX_player1_hand_texture, 0, 1, 1, 0xFFFFFFFF);//Draw Wii Pointer
            }
        }
        if(gamemode == 3){ //Options Menu
            //Drawing/Rendering
            GRRLIB_DrawImg(WinW / 2, WinH / 2, GFX_options_background_texture, 0, 0.8, 1, 0xFFFFFFFF);//Draw BG
            GRRLIB_PrintfTTF(135, 30, RubikFont, "Players:", 32, 0x000000FF); //Players Sign

            if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME && selectorcooldown == 0){
                gamemode = 2;
            }

            //PLAYER SELECTOR
            if(playerselectscreenchoice == 1){
                //1 player button
                if(GRRLIB_PtInRect(100, 80, 105, 105, P1MX, P1MY)){//If button is being hovered
                    GRRLIB_DrawImg(100, 80, GFX_icon_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                    GRRLIB_PrintfTTF(145, 115, RubikFont, "1", 24, 0x000000FF);
                    if(player1pressed & WPAD_BUTTON_A){
                        number_of_players = 1;
                        playerselectscreenchoice = 1;
                    }
                }
                else{//If button is not hovered
                    GRRLIB_DrawImg(100, 80, GFX_icon_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    GRRLIB_PrintfTTF(145, 115, RubikFont, "1", 24, 0x000000FF);
                }
                //2 player button
                if(GRRLIB_PtInRect(200, 80, 105, 105, P1MX, P1MY)){//If button is being hovered
                    GRRLIB_DrawImg(200, 80, GFX_icon_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                    GRRLIB_PrintfTTF(245, 115, RubikFont, "2", 24, 0x000000FF);
                    if(player1pressed & WPAD_BUTTON_A){
                        number_of_players = 2;
                        playerselectscreenchoice = 3;
                    }
                }
                else{//If button is not hovered
                    //GRRLIB_DrawImg(300, 100, GFX_icon_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    GRRLIB_PrintfTTF(245, 115, RubikFont, "2", 24, 0x000000FF);
                }
            }
            if(playerselectscreenchoice == 3){
                //1 player button
                if(GRRLIB_PtInRect(100, 80, 105, 105, P1MX, P1MY)){//If button is being hovered
                    GRRLIB_DrawImg(100, 80, GFX_icon_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                    GRRLIB_PrintfTTF(145, 115, RubikFont, "1", 24, 0x000000FF);
                    if(player1pressed & WPAD_BUTTON_A){
                        number_of_players = 1;
                        playerselectscreenchoice = 1;
                    }
                }
                else{//If button is not hovered
                    //GRRLIB_DrawImg(200, 100, GFX_icon_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    GRRLIB_PrintfTTF(145, 115, RubikFont, "1", 24, 0x000000FF);
                }
                //2 player button
                if(GRRLIB_PtInRect(200, 80, 105, 105, P1MX, P1MY)){//If button is being hovered
                    GRRLIB_DrawImg(200, 80, GFX_icon_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                    GRRLIB_PrintfTTF(245, 115, RubikFont, "2", 24, 0x000000FF);
                    if(player1pressed & WPAD_BUTTON_A){
                        number_of_players = 2;
                        playerselectscreenchoice = 3;
                    }
                }
                else{//If button is not hovered
                    GRRLIB_DrawImg(200, 80, GFX_icon_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    GRRLIB_PrintfTTF(245, 115, RubikFont, "2", 24, 0x000000FF);
                }
            }

            //CPU SELECTOR
            if(number_of_players == 1){
                GRRLIB_PrintfTTF(0, 375, RubikFont, "CPU:", 32, 0x000000FF); //Players Sign
                if(cpuselectscreenchoice == 1){
                    //text lmao
                    GRRLIB_PrintfTTF(220, 375, RubikFont, "Easy", 32, 0x000000FF); //Players Sign
                    //increase
                    if(GRRLIB_PtInRect(350, 350, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(350, 350, GFX_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                cpuselectscreenchoice = 2;
                                CPU_difficulty = 3;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(350, 350, GFX_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    }
                    //no decrease button since no lower difficulty lmao
                    GRRLIB_DrawImg(100, 350, GFX_left_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                }
                if(cpuselectscreenchoice == 2){
                    //text lmao
                    GRRLIB_PrintfTTF(220, 375, RubikFont, "Normal", 32, 0x000000FF); //Players Sign
                    //increase
                    if(GRRLIB_PtInRect(350, 350, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(350, 350, GFX_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                cpuselectscreenchoice = 3;
                                CPU_difficulty = 4;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(350, 350, GFX_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                        
                    }
                    //decrease
                    if(GRRLIB_PtInRect(100, 350, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(100, 350, GFX_left_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                cpuselectscreenchoice = 1;
                                CPU_difficulty = 2;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(100, 350, GFX_left_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    }
                }
                if(cpuselectscreenchoice == 3){
                    //text lmao
                    GRRLIB_PrintfTTF(220, 375, RubikFont, "Hard", 32, 0x000000FF); //Players Sign
                    //increase
                    if(GRRLIB_PtInRect(350, 350, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(350, 350, GFX_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                cpuselectscreenchoice = 4;
                                CPU_difficulty = 10;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(350, 350, GFX_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    }
                    //decrease
                    if(GRRLIB_PtInRect(100, 350, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(100, 350, GFX_left_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                cpuselectscreenchoice = 2;
                                CPU_difficulty = 3;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(100, 350, GFX_left_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    }
                }
                if(cpuselectscreenchoice == 4){
                    //text lmao
                    GRRLIB_PrintfTTF(220, 375, RubikFont, "Kaizo", 32, 0x000000FF); //Players Sign
                    //no increase since no more difficulties
                    GRRLIB_DrawImg(350, 350, GFX_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    //decrease
                    if(GRRLIB_PtInRect(100, 350, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(100, 350, GFX_left_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                cpuselectscreenchoice = 3;
                                CPU_difficulty = 4;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(100, 350, GFX_left_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    }
                }
            }

            //STYLE SELECTOR
            if(alwaystrue == true){//for formatting purposes only
                GRRLIB_PrintfTTF(0, 300, RubikFont, "Style:", 32, 0x000000FF); //Players Sign
                if(style == 1){
                    //text lmao
                    GRRLIB_PrintfTTF(220, 300, RubikFont, "Classic", 32, 0x000000FF); //Players Sign
                    //increase
                    if(GRRLIB_PtInRect(350, 275, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(350, 275, GFX_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                style = 2;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(350, 275, GFX_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    }
                    //no decrease button since no lower difficulty lmao
                    GRRLIB_DrawImg(100, 275, GFX_left_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                }
                if(style == 2){
                    //text lmao
                    GRRLIB_PrintfTTF(220, 300, RubikFont, "Deluxe", 32, 0x000000FF); //Players Sign
                    //increase is gone since only 2 options
                    GRRLIB_DrawImg(350, 275, GFX_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    //decrease
                    if(GRRLIB_PtInRect(100, 275, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(100, 275, GFX_left_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                style = 1;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(100, 275, GFX_left_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    }
                }
            }
            
            //GAMEPLAY SELECTOR
            if(alwaystrue == true){//for formatting purposes only
                GRRLIB_PrintfTTF(0, 225, RubikFont, "Game:", 32, 0x000000FF); //Players Sign
                if(gameplaymode == 1){
                    //text lmao
                    GRRLIB_PrintfTTF(220, 225, RubikFont, "Freeplay", 32, 0x000000FF); //Players Sign
                    //increase
                    if(GRRLIB_PtInRect(350, 200, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(350, 200, GFX_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                gameplaymode = 2;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(350, 200, GFX_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    }
                    //no decrease button since no lower difficulty lmao
                    GRRLIB_DrawImg(100, 200, GFX_left_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                }
                if(gameplaymode == 2){
                    //text lmao
                    GRRLIB_PrintfTTF(220, 225, RubikFont, "5 Point", 32, 0x000000FF); //Players Sign
                    //increase
                    if(GRRLIB_PtInRect(350, 200, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(350, 200, GFX_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                gameplaymode = 3;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(350, 200, GFX_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    }
                    //decrease
                    if(GRRLIB_PtInRect(100, 200, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(100, 200, GFX_left_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                gameplaymode = 1;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(100, 200, GFX_left_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    }
                }
                if(gameplaymode == 3){
                    //text lmao
                    GRRLIB_PrintfTTF(220, 225, RubikFont, "10 Point", 32, 0x000000FF); //Players Sign
                    //increase
                    if(GRRLIB_PtInRect(350, 200, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(350, 200, GFX_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                gameplaymode = 4;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(350, 200, GFX_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    }
                    //decrease
                    if(GRRLIB_PtInRect(100, 200, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(100, 200, GFX_left_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                gameplaymode = 2;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(100, 200, GFX_left_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    }
                }
                if(gameplaymode == 4){
                    //text lmao
                    GRRLIB_PrintfTTF(220, 225, RubikFont, "25 Point", 32, 0x000000FF); //Players Sign
                    //no more increase button
                    GRRLIB_DrawImg(350, 200, GFX_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    //decrease
                    if(GRRLIB_PtInRect(100, 200, 102, 102, P1MX, P1MY)){//If button is being hovered
                        GRRLIB_DrawImg(100, 200, GFX_left_triangle_button_highlighted_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button highlighted
                        if(player1pressed & WPAD_BUTTON_A){
                            if(selectorcooldown == 0){
                                gameplaymode = 3;
                                selectorcooldown = 10;
                            }
                        }
                    }
                    else{//If button is not hovered
                        GRRLIB_DrawImg(100, 200, GFX_left_triangle_button_texture, 0, 0.4, 0.4, 0xFFFFFFFF);//Draw the button not highlighted
                    }
                }
            }

            //Play Button
            if(GRRLIB_PtInRect(pbxpos, pbypos, pbx_hitbox_size, pby_hitbox_size, P1MX, P1MY)){//If button is being hovered
                GRRLIB_DrawImg(pbxpos, pbypos, GFX_button_highlighted_texture, 0, pbxsize, pbysize, 0xFFFFFFFF);//Draw the button normally
                GRRLIB_PrintfTTF(pbxpos + pbxtextoffset, pbypos + pbytextoffset, RubikFont, "Start", 24, 0x000000FF);
                if(player1pressed & WPAD_BUTTON_A){
                    gamemode = 4;
                    player1score = 0;
                    player2score = 0;
                    ballX = 311;
                    ballY = 190; 
                    player1ypos = 200;
                    player1xpos = 50;
                    player2ypos = 200;
                    player2xpos = 580;
                    MP3Player_Stop();
                    resetball();
                }
            }
            else{//If button is not hovered
                GRRLIB_DrawImg(pbxpos, pbypos, GFX_button_texture, 0, pbxsize, pbysize, 0xFFFFFFFF);//Draw the button highlighted
                GRRLIB_PrintfTTF(pbxpos + pbxtextoffset, pbypos + pbytextoffset, RubikFont, "Start", 24, 0x000000FF);
            }
            //Exit Button
            if(GRRLIB_PtInRect(pbxpos, pbypos + pbyoffset, pbx_hitbox_size, pby_hitbox_size, P1MX, P1MY)){//If button is being hovered
                GRRLIB_DrawImg(pbxpos, pbypos + pbyoffset, GFX_button_highlighted_texture, 0, pbxsize, pbysize, 0xFFFFFFFF);//Draw the button normally
                GRRLIB_PrintfTTF(pbxpos + pbxtextoffset, pbypos + pbyoffset + pbytextoffset, RubikFont, "Back", 24, 0x000000FF);
                if(player1pressed & WPAD_BUTTON_A && selectorcooldown == 0){
                    MP3Player_Stop();
                    selectorcooldown = 10;
                    gamemode = 2;
                }
            }
            else{//If button is not hovered
                GRRLIB_DrawImg(pbxpos, pbypos + pbyoffset, GFX_button_texture, 0, pbxsize, pbysize, 0xFFFFFFFF);//Draw the button highlighted
                GRRLIB_PrintfTTF(pbxpos + pbxtextoffset, pbypos + pbyoffset + pbytextoffset, RubikFont, "Back", 24, 0x000000FF);
            }

            if (P1Mote.state == 1) {//If wii pointer active, try to keep this the last thing rendered
                GRRLIB_DrawImg( P1MX, P1MY, GFX_player1_hand_texture, 0, 1, 1, 0xFFFFFFFF);//Draw Wii Pointer
            }
        }
        if(gamemode == 4){ //Free play
            //Non Changing Things
            if(alwaystrue == true){ //Formatting
                //Home Goes Back
                if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME && selectorcooldown == 0){
                    pausestatus = 1;
                    selectorcooldown = 10;
                    gamemode = 5;
                }
                if (WPAD_ButtonsDown(0) & WPAD_BUTTON_PLUS && selectorcooldown == 0){
                    pausestatus = 1;
                    selectorcooldown = 10;
                    gamemode = 5;
                }

                //Score Analyser
                if(gameplaymode == 2){
                    if(player1score == 5){
                        pausestatus = 2;
                        gamemode = 5;
                        MP3Player_Stop();
                        MP3Player_PlayBuffer(win_mp3, win_mp3_size, NULL);
                    }
                    if(player2score == 5){
                        pausestatus = 3;
                        gamemode = 5;
                        MP3Player_Stop();
                        MP3Player_PlayBuffer(win_mp3, win_mp3_size, NULL);
                    }
                }
                if(gameplaymode == 3){
                    if(player1score == 10){
                        pausestatus = 2;
                        gamemode = 5;
                        MP3Player_Stop();
                        MP3Player_PlayBuffer(win_mp3, win_mp3_size, NULL);
                    }
                    if(player2score == 10){
                        pausestatus = 3;
                        gamemode = 5;
                        MP3Player_Stop();
                        MP3Player_PlayBuffer(win_mp3, win_mp3_size, NULL);
                    }
                }
                if(gameplaymode == 4){
                    if(player1score == 25){
                        pausestatus = 2;
                        gamemode = 5;
                        MP3Player_Stop();
                        MP3Player_PlayBuffer(win_mp3, win_mp3_size, NULL);
                    }
                    if(player2score == 25){
                        pausestatus = 3;
                        gamemode = 5;
                        MP3Player_Stop();
                        MP3Player_PlayBuffer(win_mp3, win_mp3_size, NULL);
                    }
                }

                //Player 1 Controls
                if (player1pressed & WPAD_BUTTON_DOWN){ //move down if down held
                    if(player1ypos > court_bottom){} //make sure you didn't hit the bottom of the screen
                    else{
                        player1ypos += overallspeed;
                    }
                }
                if (player1pressed & WPAD_BUTTON_UP){ //move up if up held
                    if(player1ypos < court_top){} //make sure you didn't hit the top of the screen
                    else{
                        player1ypos -= overallspeed;
                    }
                }

                //Player 2 Controls
                if (number_of_players == 1){ //Let the CPU control the right Bar
                    if (player2ypos > ballY) player2ypos += - CPU_difficulty; 
                    if ((player2ypos < ballY) && (player2ypos < court_bottom)) player2ypos += CPU_difficulty; 
                }
                if (number_of_players == 2){ //Let Wiimote(1) (aka player 2) control the right Bar
                    CPU_difficulty = 3; //So the ball doesn't go flying
                    if (player2pressed & WPAD_BUTTON_DOWN){ //move down if down held
                        if(player2ypos > court_bottom){} //make sure you didn't hit the bottom of the screen
                        else{
                            player2ypos += overallspeed;
                        }
                    }
                    if (player2pressed & WPAD_BUTTON_UP){ //move up if up held
                        if(player2ypos < court_top){} //make sure you didn't hit the top of the screen
                        else{
                            player2ypos -= overallspeed;
                        }
                    }
                }

                //Ball Controls
                ballX += ballspeedX; //Set the new speed/direction of the ball X
                ballY += ballspeedY; //Set the new speed/direction of the ball Y
                //Bounce off the bottom
                if(ballY >= 388){ //If the Ball Y position is bigger or equal to 388(bottom border), invert the speed and direction. This simulates a bounce off the border.
                    if(CPU_difficulty == 2){
                        ballspeedY = rand() % -5 + -3;
                    }
                    if(CPU_difficulty == 3){
                        ballspeedY = rand() % -5 + -4;
                    }
                    if(CPU_difficulty == 4){
                        ballspeedY = rand() % -5 + -5;
                    }
                    if(CPU_difficulty == 10){
                        ballspeedY = rand() % -5 + -10;
                    }
                }	
                if(ballY <= court_top){//If the Ball Y position is smaller or equal to 40(top border), invert the speed and direction. This simulates a bounce off the border.
                    if(CPU_difficulty == 2){
                        ballspeedY = rand() % 4 + 3;
                    }
                    if(CPU_difficulty == 3){
                        ballspeedY = rand() % 4 + 4;
                    }
                    if(CPU_difficulty == 4){
                        ballspeedY = rand() % 4 + 5;
                    }
                    if(CPU_difficulty == 10){
                        ballspeedY = rand() % 4 + 10;
                    }
                }
                //Bounce off the player
                if (player1hittingball() == true){
                    if(CPU_difficulty == 2){
                        ballspeedX = rand() % 4 + 3;
                    }
                    if(CPU_difficulty == 3){
                        ballspeedX = rand() % 4 + 4;
                    }
                    if(CPU_difficulty == 4){
                        ballspeedX = rand() % 4 + 5;
                    }
                    if(CPU_difficulty == 10){
                        ballspeedX = rand() % 4 + 10;
                    }
                    bool rl = true;
                    if ((rand() % 2) + 1 ==  2){
                        rl = false;
                    }
                    if (rl == true){
                        if(CPU_difficulty == 2){
                            ballspeedY = rand() % -5 + -3;
                        }
                        if(CPU_difficulty == 3){
                            ballspeedY = rand() % -5 + -4;
                        }
                        if(CPU_difficulty == 4){
                            ballspeedY = rand() % -5 + -5;
                        }
                        if(CPU_difficulty == 10){
                            ballspeedY = rand() % -5 + -10;
                        }
                    }
                    else{
                        if(CPU_difficulty == 2){
                            ballspeedY = rand() % 4 + 3;
                        }
                        if(CPU_difficulty == 3){
                            ballspeedY = rand() % 4 + 4;
                        }
                        if(CPU_difficulty == 4){
                            ballspeedY = rand() % 4 + 5;
                        }
                        if(CPU_difficulty == 10){
                            ballspeedY = rand() % 4 + 10;
                        }
                    }
                }
                if (player2hittingball() == true){
                    if(CPU_difficulty == 2){
                        ballspeedX = rand() % -4 + -3;
                    }
                    if(CPU_difficulty == 3){
                        ballspeedX = rand() % -4 + -4;
                    }
                    if(CPU_difficulty == 4){
                        ballspeedX = rand() % -4 + -5;
                    }
                    if(CPU_difficulty == 10){
                        ballspeedX = rand() % -4 + -10;
                    }
                    bool rl = true;
                    if ((rand() % 2) + 1 ==  2){
                        rl = false;
                    }
                    if (rl == true){
                        if(CPU_difficulty == 2){
                            ballspeedY = rand() % -5 + -3;
                        }
                        if(CPU_difficulty == 3){
                            ballspeedY = rand() % -5 + -4;
                        }
                        if(CPU_difficulty == 4){
                            ballspeedY = rand() % -5 + -5;
                        }
                        if(CPU_difficulty == 10){
                            ballspeedY = rand() % -5 + -10;
                        }
                    }
                    else{
                        if(CPU_difficulty == 2){
                            ballspeedY = rand() % 4 + 3;
                        }
                        if(CPU_difficulty == 3){
                            ballspeedY = rand() % 4 + 4;
                        }
                        if(CPU_difficulty == 4){
                            ballspeedY = rand() % 4 + 5;
                        }
                        if(CPU_difficulty == 10){
                            ballspeedY = rand() % 4 + 10;
                        }
                    }
                }
                //reset ball and score
                if(ballX >= 800){
                    player1score += 1;
                    MP3Player_PlayBuffer(score_mp3, score_mp3_size, NULL);
                    resetball();
                }	
                if(ballX <= -100){
                    player2score += 1;
                    MP3Player_PlayBuffer(score_mp3, score_mp3_size, NULL);
                    resetball();
                }
            }
            
            //Style Specific
            if(style == 1){//Classic
                court_bottom = 335;
                court_top = 45;
                GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);//Background color
                objectcolor = 0xFFFFFFFF;
                //Draw Decor
                GRRLIB_Line(320,40,320,400,0xFFFFFFFF); // Central line, made from 3 lines
                GRRLIB_Line(319,40,319,400,0xFFFFFFFF);
                GRRLIB_Line(321,40,321,400,0xFFFFFFFF);
                GRRLIB_Line(25,40,620,40,0xFFFFFFFF); // Top border, made from 3 lines
                GRRLIB_Line(26,41,619,41,0xFFFFFFFF);
                GRRLIB_Line(27,42,618,42,0xFFFFFFFF);
                GRRLIB_Line(27,400,618,400,0xFFFFFFFF); // Bottom border, made from 3 lines
                GRRLIB_Line(26,401,619,401,0xFFFFFFFF);
                GRRLIB_Line(25,402,620,402,0xFFFFFFFF);
                //Draw Objects
                GRRLIB_Rectangle(player1xpos, player1ypos, player1width, player1height, objectcolor, true);//Draw player 1
                GRRLIB_Rectangle(player2xpos, player2ypos, player2width, player2height, objectcolor, true);//Draw player 2
                GRRLIB_Rectangle(ballX, ballY, 15, 15, objectcolor, true);//Draw ball
                //Draw Text
                //Score
                char p1s [100];
                sprintf(p1s, "%d", player1score);
                char p2s [100];
                sprintf(p2s, "%d", player2score);
                GRRLIB_PrintfTTF(150, 1, LCDSolidFont, p1s, 32, objectcolor);
                GRRLIB_PrintfTTF(465, 1, LCDSolidFont, p2s, 32, objectcolor);
                //Player Signs
                GRRLIB_PrintfTTF(30, 415, LCDSolidFont, "Player 1", 24, objectcolor);
                if (number_of_players == 1){ //if there is only 1 player, display that the right is a cpu
                    GRRLIB_PrintfTTF(570, 415, LCDSolidFont, "CPU", 24, objectcolor);
                }
                if (number_of_players == 2){ //If there are 2 players, display that right is player 2
                    GRRLIB_PrintfTTF(500, 415, LCDSolidFont, "Player 2", 24, objectcolor);
                }
            }
            if(style == 2){//Deluxe
                objectcolor = 0xFFFFFFFF;
                court_bottom = 340;
                court_top = 90;
                //Draw BG
                GRRLIB_DrawImg(WinW / 2, WinH / 2, GFX_court_texture, 0, 0.8, 1, 0xFFFFFFFF);//Draw BG
                //Draw Objects
                GRRLIB_DrawImg(player1xpos, player1ypos, GFX_left_paddle_texture, 0, 0.31, 0.46, 0xFFFFFFFF);//Draw BG
                GRRLIB_DrawImg(player2xpos, player2ypos, GFX_right_paddle_texture, 0, 0.31, 0.46, 0xFFFFFFFF);//Draw BG
                GRRLIB_DrawImg(ballX, ballY, GFX_ball_texture, 0, 0.25, 0.25, 0xFFFFFFFF);//Draw BG
                //GRRLIB_Rectangle(player1xpos, player1ypos, player1width, player1height, objectcolor, true);//Draw player 1
                //GRRLIB_Rectangle(player2xpos, player2ypos, player2width, player2height, objectcolor, true);//Draw player 2
                //GRRLIB_Rectangle(ballX, ballY, 15, 15, objectcolor, true);//Draw ball
                //Draw Text
                //Score
                char p1s [100];
                sprintf(p1s, "%d", player1score);
                char p2s [100];
                sprintf(p2s, "%d", player2score);
                GRRLIB_PrintfTTF(150, 1, RubikFont, p1s, 32, objectcolor);
                GRRLIB_PrintfTTF(465, 1, RubikFont, p2s, 32, objectcolor);
                //Player Signs
                GRRLIB_PrintfTTF(30, 415, RubikFont, "Player 1", 24, objectcolor);
                if (number_of_players == 1){ //if there is only 1 player, display that the right is a cpu
                    GRRLIB_PrintfTTF(570, 415, RubikFont, "CPU", 24, objectcolor);
                }
                if (number_of_players == 2){ //If there are 2 players, display that right is player 2
                    GRRLIB_PrintfTTF(500, 415, RubikFont, "Player 2", 24, objectcolor);
                }
            }            
        }
        if(gamemode == 5){ //Pause
            if(pausestatus == 1){
                GRRLIB_DrawImg(WinW / 2, WinH / 2, GFX_pause_background_texture, 0, 0.8, 1, 0xFFFFFFFF);//Draw BG
                GRRLIB_DrawImg(WinW / 2, WinH / 2, GFX_popup_texture, 0, 0.8, 1, 0xFFFFFFFF);//Draw Popup
                
                GRRLIB_PrintfTTF(200, 150, RubikFont, "Paused", 64, 0x000000FF); //Players Sign
                GRRLIB_PrintfTTF(170, 320, RubikFont, "Press A Button To Resume", 24, 0x000000FF); //Players Sign
                if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A && selectorcooldown == 0){
                    MP3Player_Stop();
                    selectorcooldown = 10;
                    gamemode = 4;
                }
                if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME && selectorcooldown == 0){
                    MP3Player_Stop();
                    MP3Player_PlayBuffer(optionsmusic_mp3, optionsmusic_mp3_size, NULL);
                    selectorcooldown = 10;
                    gamemode = 3;
                }
                GRRLIB_PrintfTTF(160, 350, RubikFont, "Press Home Button End Game", 24, 0x000000FF); //Players Sign
            }
            if(pausestatus == 2){
                GRRLIB_DrawImg(WinW / 2, WinH / 2, GFX_pause_background_texture, 0, 0.8, 1, 0xFFFFFFFF);//Draw BG
                GRRLIB_DrawImg(WinW / 2, WinH / 2, GFX_popup_texture, 0, 0.8, 1, 0xFFFFFFFF);//Draw Popup
                GRRLIB_DrawImg(WinW / 2, WinH / 2 - 15, GFX_trophy_texture, 0, 0.8, 0.8, 0xFFFFFFFF);//Draw Trophy
                GRRLIB_PrintfTTF(220, 60, RubikFont, "Player 2 Wins!", 32, 0x000000FF); //Players Sign
                GRRLIB_PrintfTTF(170, 350, RubikFont, "Press A Button To Continue", 24, 0x000000FF); //Players Sign
                if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A && selectorcooldown == 0){
                    MP3Player_Stop();
                    MP3Player_PlayBuffer(optionsmusic_mp3, optionsmusic_mp3_size, NULL);
                    selectorcooldown = 10;
                    gamemode = 3;
                }
                if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME && selectorcooldown == 0){
                    MP3Player_Stop();
                    MP3Player_PlayBuffer(optionsmusic_mp3, optionsmusic_mp3_size, NULL);
                    selectorcooldown = 10;
                    gamemode = 3;
                }
            }
            if(pausestatus == 3){
                GRRLIB_DrawImg(WinW / 2, WinH / 2, GFX_pause_background_texture, 0, 0.8, 1, 0xFFFFFFFF);//Draw BG
                GRRLIB_DrawImg(WinW / 2, WinH / 2, GFX_popup_texture, 0, 0.8, 1, 0xFFFFFFFF);//Draw Popup
                GRRLIB_DrawImg(WinW / 2, WinH / 2 - 15, GFX_trophy_texture, 0, 0.8, 0.8, 0xFFFFFFFF);//Draw Trophy
                
                GRRLIB_PrintfTTF(220, 60, RubikFont, "Player 2 Wins!", 32, 0x000000FF); //Players Sign
                GRRLIB_PrintfTTF(170, 350, RubikFont, "Press A Button To Continue", 24, 0x000000FF); //Players Sign
                if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A && selectorcooldown == 0){
                    MP3Player_Stop();
                    MP3Player_PlayBuffer(optionsmusic_mp3, optionsmusic_mp3_size, NULL);
                    selectorcooldown = 10;
                    gamemode = 3;
                }
                if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME && selectorcooldown == 0){
                    MP3Player_Stop();
                    MP3Player_PlayBuffer(optionsmusic_mp3, optionsmusic_mp3_size, NULL);
                    selectorcooldown = 10;
                    gamemode = 3;
                }
            }
            if(pausestatus == 4){
                GRRLIB_DrawImg(WinW / 2, WinH / 2, GFX_pause_background_texture, 0, 0.8, 1, 0xFFFFFFFF);//Draw BG
                GRRLIB_DrawImg(WinW / 2, WinH / 2, GFX_popup_texture, 0, 0.8, 1, 0xFFFFFFFF);//Draw Popup
                
                GRRLIB_PrintfTTF(250, 60, RubikFont, "Credits", 32, 0x000000FF); //Players Sign
                GRRLIB_PrintfTTF(100, 110, RubikFont, "-Created By ZombieNW", 24, 0x000000FF);
                GRRLIB_PrintfTTF(100, 160, RubikFont, "-Thanks to PaRaDoX", 24, 0x000000FF);
                GRRLIB_PrintfTTF(100, 210, RubikFont, "-You For Playing I Guess", 24, 0x000000FF);
                GRRLIB_PrintfTTF(170, 350, RubikFont, "Press A Button To Go Back", 24, 0x000000FF); //Players Sign
                if (WPAD_ButtonsDown(0) & WPAD_BUTTON_A && selectorcooldown == 0){
                    selectorcooldown = 10;
                    gamemode = 2;
                }
                if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME && selectorcooldown == 0){
                    selectorcooldown = 10;
                    gamemode = 2;
                }
            }
        }
        GRRLIB_Render();//Render the frame buffer
    }
    ExitGame();
    return 0;
}
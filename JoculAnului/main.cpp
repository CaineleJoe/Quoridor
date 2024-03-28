#include "SFML/Graphics.hpp"
#include <time.h>
#include <iostream>
#include "MainMenu.h"

using namespace sf;
using namespace std;

// ------------ BOARD VARIABLES ------------ //
int margin = 15;
int square_size = 50;

// ------------ WINDOW VARIABLES ------------ //
int window_width = 960;
int window_height = 840;

RenderWindow window(sf::VideoMode(window_width, window_height), "QUORIDOR");

// ------------ PLAYER DATA ------------ //
struct player_pos {
    int x = 0;
    int y = 0;
};

player_pos player_pos1;
player_pos player_pos2;
player_pos wall1_pos[10];
player_pos wall2_pos[10];

// ------------ OTHER VARIABLES ------------ //
bool player1_moved = false;
bool player2_moved = true;
bool clicked = false;

bool vertical_oc_pos[8][7];
bool horizontal_oc_pos[7][8];

bool isMove = false;
bool isMuv = false;
bool isWall = false;

unsigned k, q = 0;
unsigned turn = 1;
float dx = 0, dy = 0;

bool menu_looping = false;

// ------------ // FUNCTIONS // ------------ //
void terminate_program() {
    menu_looping = false;
}
bool check(int val1, int val2, player_pos val3)
{
    if (((val1 >= 0 && val1 <= 8)
        &&
        (val2 >= 0 && val2 <= 8))
        &&
        (val1 != val3.x || val2 != val3.y))
        return true;
    else
        return false;
}
bool vertical_check(int val1, int val2)
{
    if ((val1 >=1 && val1 <= 8)
        &&
        (val2 >= 0 && val2 <= 7))
        return true;
    else
        return false;
}
bool orizontal_check(int val1, int val2)
{
    if ((val1 >= 0 && val1 <= 7)
        &&
        (val2 >= 1 && val2 <= 8))
        return true;
    else
        return false;
}

void follow_mouse(int& px_counter_x, int& px_counter_y, Vector2i& pos, Sprite playerX) {
    px_counter_x = (13 + margin + pos.x - dx) / (margin + square_size);
    px_counter_y = (13 + margin + pos.y - dy - 120) / (margin + square_size);
}

void move(Event& e, Sprite& playerX, Vector2i& pos, int& pX_counter_x, int& pX_counter_y, int& pX_counter_x_inverse, int& pX_counter_y_inverse, player_pos& player_posX, sf::Sprite wallx[], unsigned& active_fence) {

    // Player Pickup
    if (e.type == Event::MouseButtonPressed)
    {
        if (e.key.code == Mouse::Left)
        {
            if (playerX.getGlobalBounds().contains(pos.x, pos.y))
            {
                if (turn == 1) {
                    isMove = true;
                    isMuv = false;
                    player1_moved = false;
                    player2_moved = true;
                }

                if (turn == 2) {
                    isMove = false;
                    isMuv = true;
                    player1_moved = true;
                    player2_moved = false;
                }

                dx = pos.x - playerX.getPosition().x;
                dy = pos.y - playerX.getPosition().y;
                pX_counter_x = (13 + margin + pos.x - dx) / (margin + square_size);
                pX_counter_y = (13 + margin + pos.y - dy - 120) / (margin + square_size);
            }

        }

    }

    // Key press
    if (e.type == Event::KeyPressed)
        if (e.key.code == Keyboard::R && clicked == true)
        {
            if (wallx[active_fence].getRotation() == 270)
            {

                wallx[active_fence].setRotation(0.f);
                wallx[active_fence].setOrigin(0, 0);
            }

            else
            {
                wallx[active_fence].setRotation(270.f);
                wallx[active_fence].setOrigin(0, 0);

            }
        }

    //Player Drop
    if (e.type == Event::MouseButtonReleased)
        if (e.key.code == Mouse::Left)
        {
            isWall = false;
            // Check for Overlap
            if (check(pX_counter_x, pX_counter_y, player_posX) && (pX_counter_x != pX_counter_x_inverse || pX_counter_y != pX_counter_y_inverse)&&(((pX_counter_x== player_posX.x+1)&&vertical_oc_pos[player_posX.x+1][player_posX.y]==false) || ((pX_counter_x == player_posX.x - 1)&& vertical_oc_pos[player_posX.x][player_posX.y] == false) || ((pX_counter_y == player_posX.y + 1)&&horizontal_oc_pos[player_posX.x][player_posX.y+1]==false) || ((pX_counter_y == player_posX.y - 1)&& horizontal_oc_pos[player_posX.x][player_posX.y] == false)) && ((pX_counter_y == player_posX.y) || (pX_counter_x == player_posX.x))) {
                playerX.setPosition(5 + pX_counter_x * (square_size + margin), 5 + 120 + pX_counter_y * (square_size + margin));
            
                player_posX.x = pX_counter_x;
                player_posX.y = pX_counter_y;
                if (turn == 1)
                {
                    player1_moved = true;
                    player2_moved = false;
                }
                if (turn == 2)
                {
                    player2_moved = true;
                    player1_moved = false;
                }

                isMove = false;
                isMuv = false;
                isWall = false;
            }
            //COLLISION TO RIGHT
            else if (check(pX_counter_x, pX_counter_y, player_posX) && (pX_counter_x != pX_counter_x_inverse || pX_counter_y != pX_counter_y_inverse) && (pX_counter_x == player_posX.x + 2) && (pX_counter_y == player_posX.y)&& (player_posX.x +1==pX_counter_x_inverse)&&(pX_counter_y==pX_counter_y_inverse)&& (vertical_oc_pos[player_posX.x + 1][player_posX.y] == false) && (vertical_oc_pos[player_posX.x + 2][player_posX.y] == false)) {
                playerX.setPosition(5+ pX_counter_x * (square_size + margin), 5 + 120 + pX_counter_y * (square_size + margin));

                player_posX.x = pX_counter_x;
                player_posX.y = pX_counter_y;
                if (turn == 1)
                {
                    player1_moved = true;
                    player2_moved = false;
                }
                if (turn == 2)
                {
                    player2_moved = true;
                    player1_moved = false;
                }

                isMove = false;
                isMuv = false;
                isWall = false;
            }
            else if (check(pX_counter_x, pX_counter_y, player_posX) && (pX_counter_x != pX_counter_x_inverse || pX_counter_y != pX_counter_y_inverse) && ((pX_counter_x == player_posX.x + 1) && (((pX_counter_y == player_posX.y-1)&&(horizontal_oc_pos[player_posX.x+1][player_posX.y] == false))|| (pX_counter_y == player_posX.y + 1) && (horizontal_oc_pos[player_posX.x+1][player_posX.y+1] == false))) && (player_posX.x + 1 == pX_counter_x_inverse) && (player_posX.y == pX_counter_y_inverse) && (vertical_oc_pos[player_posX.x + 1][player_posX.y] == false) && (vertical_oc_pos[player_posX.x + 2][player_posX.y] ==true))
            { playerX.setPosition(5 + pX_counter_x * (square_size + margin), 5 + 120 + pX_counter_y * (square_size + margin));

            player_posX.x = pX_counter_x;
            player_posX.y = pX_counter_y;
            if (turn == 1)
            {
                player1_moved = true;
                player2_moved = false;
            }
            if (turn == 2)
            {
                player2_moved = true;
                player1_moved = false;
            }

            isMove = false;
            isMuv = false;
            isWall = false;
        }
                //COLLISION TO LEFT
            else if(check(pX_counter_x, pX_counter_y, player_posX) && (pX_counter_x != pX_counter_x_inverse || pX_counter_y != pX_counter_y_inverse) && (pX_counter_x == player_posX.x - 2)&& ((pX_counter_y == player_posX.y)&& (pX_counter_y == pX_counter_y_inverse)) && (player_posX.x- 1 == pX_counter_x_inverse)&&(vertical_oc_pos[player_posX.x][player_posX.y] == false)&& (vertical_oc_pos[player_posX.x-1][player_posX.y] == false)){
                playerX.setPosition(5 + pX_counter_x * (square_size + margin), 5 + 120 + pX_counter_y * (square_size + margin));

                player_posX.x = pX_counter_x;
                player_posX.y = pX_counter_y;
                if (turn == 1)
                {
                    player1_moved = true;
                    player2_moved = false;
                }
                if (turn == 2)
                {
                    player2_moved = true;
                    player1_moved = false;
                }

                isMove = false;
                isMuv = false;
                isWall = false;
            }
            else if (check(pX_counter_x, pX_counter_y, player_posX) && (pX_counter_x != pX_counter_x_inverse || pX_counter_y != pX_counter_y_inverse) && ((pX_counter_x == player_posX.x-1) && (((pX_counter_y == player_posX.y - 1) && (horizontal_oc_pos[player_posX.x-1][player_posX.y] == false)) || (pX_counter_y == player_posX.y + 1) && (horizontal_oc_pos[player_posX.x-1][player_posX.y + 1] == false))) && (player_posX.x-1 == pX_counter_x_inverse) && (player_posX.y == pX_counter_y_inverse) && (vertical_oc_pos[player_posX.x][player_posX.y] == false) && (vertical_oc_pos[player_posX.x -1][player_posX.y] == true))
            {
                playerX.setPosition(5 + pX_counter_x * (square_size + margin), 5 + 120 + pX_counter_y * (square_size + margin));

                player_posX.x = pX_counter_x;
                player_posX.y = pX_counter_y;
                if (turn == 1)
                {
                    player1_moved = true;
                    player2_moved = false;
                }
                if (turn == 2)
                {
                    player2_moved = true;
                    player1_moved = false;
                }

                isMove = false;
                isMuv = false;
                isWall = false;
            }
            //COLLISION TO BACKWARDS
            else if (check(pX_counter_x, pX_counter_y, player_posX) && (pX_counter_x != pX_counter_x_inverse || pX_counter_y != pX_counter_y_inverse) && (pX_counter_y == player_posX.y + 2) && ((pX_counter_x == player_posX.x)&&(pX_counter_x== pX_counter_x_inverse)) && (player_posX.y + 1 == pX_counter_y_inverse) && (horizontal_oc_pos[player_posX.x][player_posX.y+1] == false) && (horizontal_oc_pos[player_posX.x][player_posX.y + 2] == false)) {
                playerX.setPosition(5 + pX_counter_x * (square_size + margin), 5 + 120 + pX_counter_y * (square_size + margin));

                player_posX.x = pX_counter_x;
                player_posX.y = pX_counter_y;
                if (turn == 1)
                {
                    player1_moved = true;
                    player2_moved = false;
                }
                if (turn == 2)
                {
                    player2_moved = true;
                    player1_moved = false;
                }

                isMove = false;
                isMuv = false;
                isWall = false;
            }

            else if (check(pX_counter_x, pX_counter_y, player_posX) && (pX_counter_x != pX_counter_x_inverse || pX_counter_y != pX_counter_y_inverse) && ((pX_counter_y == player_posX.y +1)&&(((pX_counter_x==player_posX.x+1)&&(vertical_oc_pos[player_posX.x + 1][player_posX.y]==false))|| ((pX_counter_x == player_posX.x - 1) && (vertical_oc_pos[player_posX.x][player_posX.y] == false)))) && (player_posX.y + 1 == pX_counter_y_inverse) && (horizontal_oc_pos[player_posX.x][player_posX.y + 1] == false) && (horizontal_oc_pos[player_posX.x][player_posX.y + 2] ==true)) {
                playerX.setPosition(5 + pX_counter_x * (square_size + margin), 5 + 120 + pX_counter_y * (square_size + margin));

                player_posX.x = pX_counter_x;
                player_posX.y = pX_counter_y;
                if (turn == 1)
                {
                    player1_moved = true;
                    player2_moved = false;
                }
                if (turn == 2)
                {
                    player2_moved = true;
                    player1_moved = false;
                }

                isMove = false;
                isMuv = false;
                isWall = false;
            }
            //COLLISION TO FORWARD
            else if (check(pX_counter_x, pX_counter_y, player_posX) && (pX_counter_x != pX_counter_x_inverse || pX_counter_y != pX_counter_y_inverse) && (pX_counter_y == player_posX.y - 2) && ((pX_counter_x == player_posX.x)&&(pX_counter_x==pX_counter_x_inverse)) && (player_posX.y - 1 == pX_counter_y_inverse) && (horizontal_oc_pos[player_posX.x][player_posX.y] == false) && (horizontal_oc_pos[player_posX.x][player_posX.y-1] == false)) {
                playerX.setPosition(5 + pX_counter_x * (square_size + margin), 5 + 120 + pX_counter_y * (square_size + margin));

                player_posX.x = pX_counter_x;
                player_posX.y = pX_counter_y;
                if (turn == 1)
                {
                    player1_moved = true;
                    player2_moved = false;
                }
                if (turn == 2)
                {
                    player2_moved = true;
                    player1_moved = false;
                }

                isMove = false;
                isMuv = false;
                isWall = false;
            }
            else if (check(pX_counter_x, pX_counter_y, player_posX) && (pX_counter_x != pX_counter_x_inverse || pX_counter_y != pX_counter_y_inverse) && ((pX_counter_y == player_posX.y-1) && (((pX_counter_x == player_posX.x + 1) && (vertical_oc_pos[player_posX.x + 1][player_posX.y-1] == false)) || ((pX_counter_x == player_posX.x - 1) && (vertical_oc_pos[player_posX.x][player_posX.y-1] == false)))) && (player_posX.y - 1 == pX_counter_y_inverse) && (horizontal_oc_pos[player_posX.x][player_posX.y] == false) && (horizontal_oc_pos[player_posX.x][player_posX.y-1] == true)) {
                playerX.setPosition(5 + pX_counter_x * (square_size + margin), 5 + 120 + pX_counter_y * (square_size + margin));

                player_posX.x = pX_counter_x;
                player_posX.y = pX_counter_y;
                if (turn == 1)
                {
                    player1_moved = true;
                    player2_moved = false;
                }
                if (turn == 2)
                {
                    player2_moved = true;
                    player1_moved = false;
                }

                isMove = false;
                isMuv = false;
                isWall = false;
            }
            //FAILED TO MOVE
            else {
                pX_counter_x= player_posX.x;
                pX_counter_y= player_posX.y;
                isMove = false;
                isMuv = false;
                isWall = false;
                if (turn == 1)
                    player1_moved = false;
                if (turn == 2)
                    player2_moved = false;
                playerX.setPosition(5 + player_posX.x * (square_size + margin), 5 + 120 + player_posX.y * (square_size + margin));
            }
            //SWAP TURNS IF VALID
            if (player1_moved)
                turn = 2;
            if (player2_moved)
                turn = 1;
        }
}

void move_wall(Event& e, Vector2i& pos, Sprite wallx[], int& wallx_counter_x, int& wallx_counter_y, unsigned& active_fence)
{
    // Wall Press
    if (e.type == Event::MouseButtonPressed)
    {
        if (e.key.code == Mouse::Left)
        {
            for (int i = 0; i < 10; i++)
                if (wallx[i].getGlobalBounds().contains(pos.x, pos.y))
                {
                    isMove = false;
                    isMuv = false;
                    player1_moved = false;
                    player2_moved = false;
                    isWall = true;
                    dx = pos.x - wallx[i].getPosition().x;
                    dy = pos.y - wallx[i].getPosition().y;
                    wallx_counter_x = (pos.x - dx) / (margin + square_size);
                    wallx_counter_y = (pos.y - dy - 120) / (margin + square_size);
                    active_fence = i;
                    clicked = true;
                }

            for (int i = 0; i <= 9; i++)
            {
                if (wallx[i].getGlobalBounds().contains(pos.x, pos.y)) {

                    cout << "[x " << wallx_counter_x << " : " << pos.x << " ] " << "[y " << wallx_counter_y << " : " << pos.y - 120 << " ] " << endl;
                }
            }
        }
    }
    // wall release
    if (e.type == Event::MouseButtonReleased) {
        if (e.key.code == Mouse::Left)
        {
            if (clicked)
                if (wallx[active_fence].getRotation() == 0&& wallx_counter_x){
                    // bad vertical case
                    if ((vertical_oc_pos[wallx_counter_x][wallx_counter_y] == true || vertical_oc_pos[wallx_counter_x][wallx_counter_y + 1] == true) || vertical_check(wallx_counter_x, wallx_counter_y)==false || horizontal_oc_pos[wallx_counter_x - 1][wallx_counter_y + 1] == true)
                    {
                        if (turn == 1)
                            wallx[active_fence].setPosition(600 + active_fence * 20, 200);
                        else
                            wallx[active_fence].setPosition(600 + active_fence * 20, 520);
                        clicked = false;
                    }
                    // good vertical case
                    else {
                        wallx[active_fence].setPosition(margin * wallx_counter_x + wallx_counter_x * square_size, margin + margin * wallx_counter_y + 120 + wallx_counter_y * square_size);
                        cout << "Occupied " << wallx_counter_x << " : " << wallx_counter_y << endl;
                       
                            vertical_oc_pos[wallx_counter_x][wallx_counter_y] = true;
                            vertical_oc_pos[wallx_counter_x][wallx_counter_y + 1] = true;
                        
                        clicked = false;
                        if (turn == 1)
                        {
                            player1_moved = true;
                            player2_moved = false;
                        }
                        if (turn == 2)
                        {
                            player2_moved = true;
                            player1_moved = false;
                        }
                    }
                }
                else if (wallx[active_fence].getRotation() == 270) {
                    // bad horizontal case
                    if ((horizontal_oc_pos[wallx_counter_x][wallx_counter_y] == true || horizontal_oc_pos[wallx_counter_x + 1][wallx_counter_y] == true )|| orizontal_check(wallx_counter_x, wallx_counter_y)==false ||vertical_oc_pos[wallx_counter_x + 1][wallx_counter_y - 1] ==true)
                    {
                        wallx[active_fence].setRotation(0);
                        if (turn == 1)
                            wallx[active_fence].setPosition(600 + active_fence * 20, 200);
                        else
                            wallx[active_fence].setPosition(600 + active_fence * 20, 520);

                        clicked = false;
                    }
                    // good horizontal case
                    else {
                        wallx[active_fence].setPosition(margin + margin * wallx_counter_x + wallx_counter_x * square_size, margin + margin * wallx_counter_y + 120 + wallx_counter_y * square_size);
                        cout << "Occupied " << wallx_counter_x << " : " << wallx_counter_y << endl;
                        horizontal_oc_pos[wallx_counter_x][wallx_counter_y] = true;
                        horizontal_oc_pos[wallx_counter_x + 1][wallx_counter_y] = true;
                       
                           
                        clicked = false;
                        if (turn == 1)
                        {
                            player1_moved = true;
                            player2_moved = false;
                        }
                        if (turn == 2)
                        {
                            player2_moved = true;
                            player1_moved = false;
                        }
                    }
                }
        }
    }
    if (player1_moved)
        turn = 2;
    if (player2_moved)
        turn = 1;
}
// ------------ // GAME VIEWS // ------------ //
void options_loop() {
    bool options_looping = true;
    //photo options
    RectangleShape background;
    background.setSize(Vector2f(window_width, window_height));
    Texture O_texture;
    O_texture.loadFromFile("C:/Users/Luca/Desktop/JoculAnului/Textures/options_photo.jpeg");
    background.setTexture(&O_texture);
    Text rule,detail;
    Font rulefont;
    if (!rulefont.loadFromFile("C:/Users/Luca/Desktop//JoculAnului/Fonts/FruitDays.ttf"))
    {
        cout << "Nu exista font aici";
    }
    rule.setFont(rulefont);
    rule.setCharacterSize(30);
    rule.setFillColor(Color::Cyan);
    rule.setOutlineColor(Color::Black);
    rule.setOutlineThickness(2);

    detail.setFont(rulefont);
    detail.setOutlineColor(Color::Black);
    detail.setFillColor(Color::White); 
    detail.setOutlineThickness(1);
    detail.setCharacterSize(25);
    while (options_looping)
    {
        Event aevent;
        while (window.pollEvent(aevent))
        {
            if (aevent.type == Event::Closed)
            {
                terminate_program();
                window.close();
                exit(0);
            }

            if (aevent.type == Event::KeyPressed)
                if (aevent.key.code == Keyboard::Escape)
                    options_looping = false;
        }

        window.clear();
        window.draw(background);
        //Writing the rulebook
        rule.setPosition(300, 10);
        rule.setString("OBJECT OF THE GAME");
        window.draw(rule);
        detail.setPosition(10,40);
        detail.setString(" To be the first to reach the line opposite to one's base line.");
        window.draw(detail);
        rule.setPosition(360,80);
        rule.setString("GAME PLAY");
        window.draw(rule);
        detail.setPosition(10,110);
        detail.setString(" Each player in turn, chooses to move his pawn or to put up one of his fences(10pcs).");
        window.draw(detail);
        detail.setPosition(10, 130);
        detail.setString(" When he has run out of fences, the player must move his pawn.");
        window.draw(detail);
        rule.setPosition(360,170);
        rule.setString("PAWN MOVES");
        window.draw(rule);
        detail.setPosition(10,200);
        detail.setString(" The pawns are moved one square at a time, horizontally or vertically, forwards or ");
        window.draw(detail);
        detail.setPosition(10, 220);
        detail.setString("backwards, never diagonally.");
        window.draw(detail);
        detail.setPosition(10,240);
        detail.setString(" The pawns must bypass the fences. If, while you move, you face your opponent's");
        window.draw(detail);
        detail.setPosition(10, 260);
        detail.setString("pawn you can jump over.");
        window.draw(detail);
        detail.setPosition(10, 280);
        detail.setString(" If there is a fence behind the said pawn, the player can place his pawn to the left");
        window.draw(detail);
        detail.setPosition(10, 300);
        detail.setString("or the right of the other pawn.");
        window.draw(detail);
        rule.setPosition(280, 340);
        rule.setString("POSITIONING OF THE FENCES");
        window.draw(rule);
        detail.setPosition(10, 370);
        detail.setString(" The fences must be placed between 2 sets of 2 squares(press R to choose the ori-");
        window.draw(detail);
        detail.setPosition(10, 390);
        detail.setString("entation of the fence).");
        window.draw(detail);
        detail.setPosition(10, 410);
        detail.setString(" By placing fences, you force your opponent to move around it and increase the");
        window.draw(detail);
        detail.setPosition(10, 430);
        detail.setString("number of moves they need to make. But be careful, you are not allowed to lock");
        window.draw(detail);
        detail.setPosition(10, 450);
        detail.setString("up your opponents pawn, it must always be able to reach it's goal by at least one .");
        window.draw(detail);
        detail.setPosition(10, 470);
        detail.setString("square.");
        window.draw(detail);
        rule.setPosition(320,510);
        rule.setString("END OF THE GAME");
        window.draw(rule);
        detail.setPosition(10,540);
        detail.setString("The first player who reaches one of the 9 squares opposite his base line is the winner.");
        window.draw(detail);
        detail.setPosition(10, 575);
        detail.setString("Have fun!");
        window.draw(detail);
        rule.setPosition(700,700);
        rule.setString("Press ESC to leave. ");
        window.draw(rule);
        window.display();
    }

}
void show_winner(int winner, Text p, Font font) {
    bool show_looping = true;
    //photo about cazan and luca company
    RectangleShape background1;
    background1.setSize(Vector2f(window_width, window_height));
    Texture AB_texture1;
    AB_texture1.loadFromFile("C:/Users/Luca/Desktop/JoculAnului/Textures/about_photo.jpeg");
    background1.setTexture(&AB_texture1);

    while (show_looping)
    {
        Event aevent;
        while (window.pollEvent(aevent))
        {
            if (aevent.type == Event::Closed)
            {
                terminate_program();
                window.close();
                exit(0);
            }

            if (aevent.type == Event::KeyPressed)
                if (aevent.key.code == Keyboard::Escape)
                    show_looping = false;
        }


        window.clear();

        p.setFont(font);
        p.setCharacterSize(100);
        p.setPosition(window_width / 6, window_height / 3);
        p.setFillColor(Color::White);
        if (winner == 0)
        {
            p.setCharacterSize(80);
            p.setString("Press ESC to leave.");
        }
        if (winner == 1)
            p.setString("Winner: Player 1!");
        if (winner == 2)
            p.setString("Winner: Player 2!");


        window.draw(background1);
        window.draw(p);

        window.display();
    }

}
void about_loop() {
    bool about_looping = true;
    //photo about cazan and luca company
    RectangleShape background;
    background.setSize(Vector2f(window_width, window_height));
    Texture AB_texture;
    AB_texture.loadFromFile("C:/Users/Luca/Desktop/JoculAnului/Textures/credits_photo.jpeg");
    background.setTexture(&AB_texture);
    Font aboutfont;
    Texture texture;
    texture.loadFromFile("C:/Users/Luca/Desktop/JoculAnului/Textures/cheers!.png");
    Sprite  celebration(texture);
    celebration.setPosition(650, 420);

    if (!aboutfont.loadFromFile("C:/Users/Luca/Desktop/JoculAnului/Fonts/FruitDays.ttf"))
    {
        cout << "Nu exista font aici";
    }
    Text text;
    text.setFont(aboutfont);
    text.setOutlineColor(Color::Black);
    text.setFillColor(Color::White);
    text.setOutlineThickness(2);
    text.setCharacterSize(30);

    while (about_looping)
    {
        Event aevent;
        while (window.pollEvent(aevent))
        {
            if (aevent.type == Event::Closed)
            {
                terminate_program();
                window.close();
                exit(0);
            }

            if (aevent.type == Event::KeyPressed)
                if (aevent.key.code == Keyboard::Escape)
                    about_looping = false;
        }

        window.clear();
        window.draw(background);
        text.setPosition(10, 200);
        text.setString(" This project was realized by Cozloschi Luca and Cazan Rares.");
        window.draw(text);
        text.setPosition(10, 230);
        text.setString(" We are currently studying informatics at Alexandru Ioan Cuza");
        window.draw(text);
        text.setPosition(400, 260);
        text.setString("University.");
        window.draw(text);
        text.setPosition(10, 290);
        text.setString(" This is our first attempt of making a game and we are proud of");
        window.draw(text);
        text.setPosition(10, 320);
        text.setString("how many new things we learnt by attemtping this challange.");
        window.draw(text);
        text.setPosition(220, 350);
        text.setString("Thank you for trying our game!");
        window.draw(text);
        window.draw(celebration);
        text.setPosition(700, 700);
        text.setString("Press ESC to leave. ");
        window.draw(text);
        window.display();
    }

}
int game_loop()
{
    int winner = 0;
    bool game_looping = true;


    player_pos1.x = 4;
    player_pos2.x = 4;
    player_pos2.y = 8;

    int p1_counter_x = player_pos1.x;
    int p1_counter_y = player_pos1.y;
    int p2_counter_x = player_pos2.x;
    int p2_counter_y = player_pos2.y;
    int wall1_counter_x = 0;
    int wall1_counter_y = 0;
    int wall2_counter_x = 0;
    int wall2_counter_y = 0;

    Texture t1, t2, t3, t4;
    t1.loadFromFile("C:/Users/Luca/Desktop/JoculAnului/Textures/plus5.png");
    t3.loadFromFile("C:/Users/Luca/Desktop/JoculAnului/Textures/stea2.png");
    t2.loadFromFile("C:/Users/Luca/Desktop/JoculAnului/Textures/wall.png");
    t4.loadFromFile("C:/Users/Luca/Desktop/JoculAnului/Textures/wall2.png");

    sf::RectangleShape active_square(sf::Vector2f(square_size, square_size));
    active_square.setFillColor(sf::Color(94, 173, 160, 255));
    sf::RectangleShape possible_square(sf::Vector2f(square_size, square_size));
    possible_square.setFillColor(sf::Color(107, 196, 88, 255));


    Sprite player1(t1);
    Sprite player2(t3);
    Sprite wall1[10], wall2[10];

    //POZITIE INITIALA 
    player1.setPosition(5 + 4 * (square_size + margin), 125);
    player2.setPosition(5 + 4 * (square_size + margin), 125 + 8 * (square_size + margin));

    for (int i = 0; i < 10; i++)
    {

        wall1[i].setTexture(t2);
        wall1[i].setPosition(600 + 20 * i, 200);
        wall1_pos[i].x = 600 + 20 * i;
        wall1_pos[i].y = 200;

        wall2[i].setTexture(t4);
        wall2[i].setPosition(600 + 20 * i, 520);
        wall2_pos[i].x = 600 + 20 * i;
        wall2_pos[i].y = 520;

    }

    // Vertical Occupied walls
    for (int i = 1; i <= 8; i++)
        for (int j = 0; j <= 7; j++) {
            vertical_oc_pos[i][j] = false;
        }

    // Horizontal Occupied walls
    for (int i = 0; i <= 7; i++)
        for (int j = 1; j <= 8; j++) {
            horizontal_oc_pos[i][j] = false;
        }

    Font font;
    if (!font.loadFromFile("C:/Users/Luca/Desktop/JoculAnului/Fonts/FruitDays.ttf"))
        cout << "eroare font";

    Text p;
    p.setFont(font);
    p.setFillColor(Color::Magenta);
    p.setString("Your turn, buddy!");
    p.setCharacterSize(50);
    p.setPosition(0, 0);

    sf::RectangleShape square(sf::Vector2f(square_size, square_size));
    square.setFillColor(sf::Color(248, 242, 166, 255));

    window.setFramerateLimit(60);



    // --------------- GAME LOOP -------------- //
    while (game_looping)
    {
        //cout << "looping game" << endl;

        Vector2i pos = Mouse::getPosition(window);
        Event e;

        while (window.pollEvent(e))
        {
            // Address Close Button
            if (e.type == Event::Closed)
            {
                terminate_program();
                window.close();
                exit(0);
            }
            // Address Escape Key
            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::Escape)
                    game_looping = false;


            // Handle On-Click Players Movement
            if (turn == 1) {
                move(e, player1, pos, p1_counter_x, p1_counter_y, p2_counter_x, p2_counter_y, player_pos1, wall1, k);
                move_wall(e, pos, wall1, wall1_counter_x, wall1_counter_y, k);
            }
            if (turn == 2) {
                move(e, player2, pos, p2_counter_x, p2_counter_y, p1_counter_x, p1_counter_y, player_pos2, wall2, q);
                move_wall(e, pos, wall2, wall2_counter_x, wall2_counter_y, q);
            }
        }


        // Make the Players follow Cursor
        if (isMove) {
            follow_mouse(p1_counter_x, p1_counter_y, pos, player1);
            player1.setPosition(pos.x - dx, pos.y - dy);
        }
        if (isMuv) {
            follow_mouse(p2_counter_x, p2_counter_y, pos, player2);
            player2.setPosition(pos.x - dx, pos.y - dy);
        }
        if (isWall)
        {
            if (turn == 1)
            {
                follow_mouse(wall1_counter_x, wall1_counter_y, pos, wall1[k]);
                wall1[k].setPosition(pos.x - dx, pos.y - dy);

            }

            if (turn == 2) {
                follow_mouse(wall2_counter_x, wall2_counter_y, pos, wall2[q]);
                wall2[q].setPosition(pos.x - dx, pos.y - dy);

            }

        }

        // --------------- draw ---------------- //
        window.clear();

        if (isMove || isMuv||isWall)
            window.setMouseCursorVisible(false);
        else
            window.setMouseCursorVisible(true);


        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                window.draw(square);
                square.setPosition(margin + i * (square_size + margin), margin + 120 + j * (square_size + margin));
            }
        }

        // visual feedback QoL Active Square
        if (turn == 1)
        {
            active_square.setPosition(margin + player_pos1.x * (square_size + margin), margin + 120 + player_pos1.y * (square_size + margin));
            window.draw(active_square);
        }
        else {
            active_square.setPosition(margin + player_pos2.x * (square_size + margin), margin + 120 + player_pos2.y * (square_size + margin));
            window.draw(active_square);
        }

        // visual feedback QoL Possible Movement Square
        if (turn == 1) {
            if (player_pos1.x != 8)
            {
                if ((player_pos1.x != player_pos2.x -1) || (player_pos1.y != player_pos2.y))
                {
                    if (vertical_oc_pos[player_pos1.x + 1][player_pos1.y] == false)
                    {
                        possible_square.setPosition((margin + square_size) + margin + player_pos1.x * (square_size + margin), margin + 120 + player_pos1.y * (square_size + margin));
                        window.draw(possible_square);
                    }
                }
                else {
                    if (player_pos1.y == player_pos2.y&& vertical_oc_pos[player_pos1.x + 2][player_pos1.y] == false&& vertical_oc_pos[player_pos1.x + 1][player_pos1.y] == false&&player_pos2.x!=8) {
                        possible_square.setPosition(2 * (margin + square_size) + margin + player_pos1.x * (square_size + margin), margin + 120 + player_pos1.y * (square_size + margin));
                        window.draw(possible_square);
                    }
                 //special case face to face+walls RIGHT
                    if (player_pos1.y == player_pos2.y && vertical_oc_pos[player_pos1.x + 2][player_pos1.y] == true && vertical_oc_pos[player_pos1.x + 1][player_pos1.y] == false)
                    {
                        if (horizontal_oc_pos[player_pos1.x+1][player_pos1.y] == false)
                        {
                            possible_square.setPosition((margin + square_size) + margin + player_pos1.x * (square_size + margin), margin + 120 + player_pos1.y * (square_size + margin) - (square_size + margin));
                            window.draw(possible_square);
                        }
                        if (horizontal_oc_pos[player_pos1.x + 1][player_pos1.y+1] == false) 
                        {
                            possible_square.setPosition((margin + square_size) + margin + player_pos1.x * (square_size + margin), margin + 120 + player_pos1.y * (square_size + margin) + (square_size + margin));
                            window.draw(possible_square);
                        }
                    }
                }
            }
            if (player_pos1.x != 0) {
                if ((player_pos1.x != player_pos2.x +1)||(player_pos1.y!= player_pos2.y)) {
                    if (vertical_oc_pos[player_pos1.x][player_pos1.y] == false)
                    {
                        possible_square.setPosition((-margin - square_size) + margin + player_pos1.x * (square_size + margin), margin + 120 + player_pos1.y * (square_size + margin));
                        window.draw(possible_square);
                    }
                }else {
                    if (player_pos1.y == player_pos2.y && vertical_oc_pos[player_pos1.x - 1][player_pos1.y] == false && vertical_oc_pos[player_pos1.x][player_pos1.y] == false)
                    {
                        possible_square.setPosition(2 * (-margin - square_size) + margin + player_pos1.x * (square_size + margin), margin + 120 + player_pos1.y * (square_size + margin));
                        window.draw(possible_square);
                    }
                    //special case face to face+walls LEFT
                   if(player_pos1.y == player_pos2.y && vertical_oc_pos[player_pos1.x- 1][player_pos1.y] == true && vertical_oc_pos[player_pos1.x][player_pos1.y] == false)
                        {
                            if (horizontal_oc_pos[player_pos1.x - 1][player_pos1.y] == false)
                   {
                       possible_square.setPosition(margin + player_pos1.x * (square_size + margin) - (margin + square_size), margin + 120 + player_pos1.y * (square_size + margin) - (square_size + margin));
                       window.draw(possible_square);
                   }
                   if (horizontal_oc_pos[player_pos1.x - 1][player_pos1.y + 1] == false)
                   {
                       possible_square.setPosition(margin + player_pos1.x * (square_size + margin) - (margin + square_size), margin + 120 + player_pos1.y * (square_size + margin) + (square_size + margin));
                       window.draw(possible_square);
                   }
                        }
                    
                }
            }
            if (player_pos1.y != 0) {
               //case wall above opposite player
                if(player_pos2.y == player_pos1.y - 1 && horizontal_oc_pos[player_pos2.x][player_pos2.y] == true&& horizontal_oc_pos[player_pos1.x][player_pos1.y]==false&& player_pos1.x == player_pos2.x)
                {
                    if (vertical_oc_pos[player_pos2.x+1][player_pos1.y-1] == false)
                    {
                        possible_square.setPosition((margin + square_size) + margin + player_pos1.x * (square_size + margin), (-margin - square_size) + margin + 120 + player_pos1.y * (square_size + margin));
                        window.draw(possible_square);
                    }if (vertical_oc_pos[player_pos2.x][player_pos1.y - 1] == false)
                    {
                        possible_square.setPosition((-margin - square_size) + margin + player_pos1.x * (square_size + margin), (-margin - square_size) + margin + 120 + player_pos1.y * (square_size + margin));
                        window.draw(possible_square);
                    }
                }
                if (player_pos1.y != player_pos2.y + 1 || player_pos1.x != player_pos2.x) {
                    if (horizontal_oc_pos[player_pos1.x][player_pos1.y] == false)
                    {
                        possible_square.setPosition(margin + player_pos1.x * (square_size + margin), (-margin - square_size) + margin + 120 + player_pos1.y * (square_size + margin));
                        window.draw(possible_square);
                    }
                }
                else{
                    if (player_pos1.x == player_pos2.x && horizontal_oc_pos[player_pos1.x][player_pos1.y] == false&&horizontal_oc_pos[player_pos1.x][player_pos1.y-1] == false) {
                        possible_square.setPosition(margin + player_pos1.x * (square_size + margin), 2 * (-margin - square_size) + margin + 120 + player_pos1.y * (square_size + margin));
                        window.draw(possible_square);
                    }
                }
            }

        
            if (player_pos1.y != player_pos2.y - 1|| player_pos1.x != player_pos2.x)
            {
                if (horizontal_oc_pos[player_pos1.x][player_pos1.y + 1] == false)
                {
                    possible_square.setPosition(margin + player_pos1.x * (square_size + margin), (margin + square_size) + margin + 120 + player_pos1.y * (square_size + margin));
                    window.draw(possible_square);
                }
            }else
            {
                if (player_pos1.x == player_pos2.x && horizontal_oc_pos[player_pos1.x][player_pos1.y+1] == false && horizontal_oc_pos[player_pos1.x][player_pos1.y+2] == false&&player_pos2.y!=8)
                {
                    possible_square.setPosition(margin + player_pos1.x * (square_size + margin), margin + 120 + player_pos1.y * (square_size + margin) + 2 * (margin + square_size));
                    window.draw(possible_square);
                }

                    if (player_pos2.y == player_pos1.y + 1 && horizontal_oc_pos[player_pos2.x][player_pos2.y+1] == true && horizontal_oc_pos[player_pos1.x][player_pos1.y] == false) 
                    {
                        if (vertical_oc_pos[player_pos2.x + 1][player_pos1.y] == false)
                        {
                            possible_square.setPosition((margin + square_size) + margin + player_pos1.x * (square_size + margin), (margin+square_size) + margin + 120 + player_pos1.y * (square_size + margin));
                            window.draw(possible_square);
                        }
                        if (vertical_oc_pos[player_pos2.x][player_pos1.y] == false)
                        {
                            possible_square.setPosition((-margin - square_size) + margin + player_pos1.x * (square_size + margin), (margin +square_size) + margin + 120 + player_pos1.y * (square_size + margin));
                            window.draw(possible_square);
                        }
                    }
                
            }

        }
        //PLAYER 2
        else {
            if (player_pos2.x != 8) {
                if ((player_pos2.x != player_pos1.x - 1)||(player_pos1.y != player_pos2.y))
                {
                    if (vertical_oc_pos[player_pos2.x + 1][player_pos2.y] == false)
                    {
                        possible_square.setPosition((margin + square_size) + margin + player_pos2.x * (square_size + margin), margin + 120 + player_pos2.y * (square_size + margin));
                        window.draw(possible_square);
                    }
                }
                else {
                    //SPECIAL MOVES FACE TO FACE +WALL RIGHT
                    if (player_pos1.x !=8&& vertical_oc_pos[player_pos2.x + 2][player_pos2.y] == false && vertical_oc_pos[player_pos2.x + 1][player_pos2.y] == false) 
                    {
                        possible_square.setPosition(2 * (margin + square_size) + margin + player_pos2.x * (square_size + margin), margin + 120 + player_pos2.y * (square_size + margin));
                        window.draw(possible_square);
                    }

                    if (player_pos1.y == player_pos2.y && vertical_oc_pos[player_pos2.x + 2][player_pos2.y] == true && vertical_oc_pos[player_pos2.x + 1][player_pos2.y] == false)
                    {
                        if (horizontal_oc_pos[player_pos2.x + 1][player_pos2.y] == false)
                        {
                            possible_square.setPosition((margin + square_size) + margin + player_pos2.x * (square_size + margin), margin + 120 + player_pos2.y * (square_size + margin) - (square_size + margin));
                            window.draw(possible_square);
                        }
                        if (horizontal_oc_pos[player_pos2.x + 1][player_pos2.y + 1] == false)
                        {
                            possible_square.setPosition((margin + square_size) + margin + player_pos2.x * (square_size + margin), margin + 120 + player_pos2.y * (square_size + margin) + (square_size + margin));
                            window.draw(possible_square);
                        }
                    }

                }
                
            }

           

            if (player_pos2.x != 0)
            {
                if ((player_pos2.x != player_pos1.x + 1) || (player_pos1.y != player_pos2.y)) {
                    if (vertical_oc_pos[player_pos2.x][player_pos2.y] == false)
                    {
                        possible_square.setPosition((-margin - square_size) + margin + player_pos2.x * (square_size + margin), margin + 120 + player_pos2.y * (square_size + margin));
                        window.draw(possible_square);
                    }
                }
                else
{
                    if (player_pos1.x != 0&& player_pos1.y == player_pos2.y && vertical_oc_pos[player_pos2.x - 1][player_pos2.y] == false && vertical_oc_pos[player_pos2.x][player_pos2.y] == false)
                    {
                        possible_square.setPosition(2 * (-margin - square_size) + margin + player_pos2.x * (square_size + margin), margin + 120 + player_pos2.y * (square_size + margin));
                        window.draw(possible_square);
                    }

                    //special case face to face+walls LEFT
                    if (player_pos1.y == player_pos2.y && vertical_oc_pos[player_pos2.x - 1][player_pos2.y] == true && vertical_oc_pos[player_pos2.x][player_pos2.y] == false)
                    {
                        if (horizontal_oc_pos[player_pos2.x - 1][player_pos2.y] == false)
                        {
                            possible_square.setPosition(margin + player_pos2.x * (square_size + margin) - (margin + square_size), margin + 120 + player_pos2.y * (square_size + margin) - (square_size + margin));
                            window.draw(possible_square);
                        }
                        if (horizontal_oc_pos[player_pos2.x - 1][player_pos2.y + 1] == false)
                        {
                            possible_square.setPosition(margin + player_pos2.x * (square_size + margin) - (margin + square_size), margin + 120 + player_pos2.y * (square_size + margin) + (square_size + margin));
                            window.draw(possible_square);
                        }
                    }

                }
            }
            if (player_pos2.y != 8) {

             
                if ((player_pos2.y != player_pos1.y -1) || (player_pos1.x != player_pos2.x)){
                    if (horizontal_oc_pos[player_pos2.x][player_pos2.y + 1] == false)
                    {
                        possible_square.setPosition(margin + player_pos2.x * (square_size + margin), (margin + square_size) + margin + 120 + player_pos2.y * (square_size + margin));
                        window.draw(possible_square);
                    }
                }
                else {
                    if (player_pos1.x == player_pos2.x && horizontal_oc_pos[player_pos2.x][player_pos2.y + 1] == false && horizontal_oc_pos[player_pos2.x][player_pos2.y + 2] == false)
                    {
                        possible_square.setPosition(margin + player_pos2.x * (square_size + margin), 2 * (margin + square_size) + margin + 120 + player_pos2.y * (square_size + margin));
                        window.draw(possible_square);
                    }

                    if (player_pos1.y == player_pos2.y + 1 && horizontal_oc_pos[player_pos1.x][player_pos1.y + 1] == true && horizontal_oc_pos[player_pos2.x][player_pos2.y] == false)
                    {
                        if (vertical_oc_pos[player_pos1.x + 1][player_pos2.y] == false)
                        {
                            possible_square.setPosition((margin + square_size) + margin + player_pos2.x * (square_size + margin), (margin + square_size) + margin + 120 + player_pos2.y * (square_size + margin));
                            window.draw(possible_square);
                        }
                        if (vertical_oc_pos[player_pos1.x][player_pos2.y] == false)
                        {
                            possible_square.setPosition((-margin - square_size) + margin + player_pos2.x * (square_size + margin), (margin + square_size) + margin + 120 + player_pos2.y * (square_size + margin));
                            window.draw(possible_square);
                        }
                    }
                }
            }

         
            if ((player_pos2.y != player_pos1.y + 1) || (player_pos1.x != player_pos2.x))
            {
                if (horizontal_oc_pos[player_pos2.x][player_pos2.y] == false)
                {
                    possible_square.setPosition(margin + player_pos2.x * (square_size + margin), (-margin - square_size) + margin + 120 + player_pos2.y * (square_size + margin));
                    window.draw(possible_square);
                }
            }
            else{
                if (player_pos1.y == player_pos2.y - 1 && horizontal_oc_pos[player_pos1.x][player_pos1.y] == true && horizontal_oc_pos[player_pos2.x][player_pos2.y] == false && player_pos2.x == player_pos1.x)
                {
                    if (vertical_oc_pos[player_pos1.x + 1][player_pos2.y - 1] == false)
                    {
                        possible_square.setPosition((margin + square_size) + margin + player_pos2.x * (square_size + margin), (-margin - square_size) + margin + 120 + player_pos2.y * (square_size + margin));
                        window.draw(possible_square);
                    }if (vertical_oc_pos[player_pos1.x][player_pos2.y - 1] == false)
                    {
                        possible_square.setPosition((-margin - square_size) + margin + player_pos2.x * (square_size + margin), (-margin - square_size) + margin + 120 + player_pos2.y * (square_size + margin));
                        window.draw(possible_square);
                    }
                }
                if (player_pos2.x == player_pos1.x && horizontal_oc_pos[player_pos2.x][player_pos2.y] == false && horizontal_oc_pos[player_pos2.x][player_pos2.y - 1] == false&&player_pos1.y!=0)
                {
                    possible_square.setPosition(margin + player_pos2.x * (square_size + margin), 2 * (-margin - square_size) + margin + 120 + player_pos2.y * (square_size + margin));
                    window.draw(possible_square);
                }


            }
        }



        window.draw(player1);
        window.draw(player2);
        for (int i = 0; i < 10; i++)
        {
            window.draw(wall1[i]);
            window.draw(wall2[i]);
        }


        if (turn == 1)
            p.setPosition(0, 0);
        if (turn == 2)
            p.setPosition(0, 725);
        if (player_pos1.y == 8) {
            winner = 1;
            break;
        }
        if (player_pos2.y == 0) {
            winner = 2;
            break;
        }
        window.draw(p);
        window.display();
    }

    show_winner(winner, p, font);

    return 0;
}
int main() {
    bool menu_looping = true;

    MainMenu mainMenu(window.getSize().x, window.getSize().y);

    RectangleShape background;
    background.setSize(Vector2f(window_width, window_height));
    Texture Maintexture;
    Maintexture.loadFromFile("C:/Users/Luca/Desktop/JoculAnului/Textures/background.jpeg");
    background.setTexture(&Maintexture);

    /// <summary>
    ///     remove game_loop() to enter menu
    /// </summary>
    /// <returns></returns>
    /// 

    while (menu_looping)
    {
        cout << "looping menu" << endl;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                menu_looping = false;

            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up)
                {
                    mainMenu.MoveUp();
                    break;
                }
                if (event.key.code == Keyboard::Down)
                {
                    mainMenu.MoveDown();
                    break;
                }

                if (event.key.code == Keyboard::Return)
                {

                    int x = mainMenu.MainMenuPressed();
                    if (x == 0)
                    {
                        game_loop();
                    }
                    if (x == 1)
                    {
                        options_loop();
                    }
                    if (x == 2)
                    {
                        about_loop();

                    }
                    if (x == 3)
                        menu_looping = false;
                }
            }
        }
        window.clear();
        window.draw(background);
        mainMenu.draw(window);
        window.display();
    }
}
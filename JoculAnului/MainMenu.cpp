#include "MainMenu.h"


MainMenu::MainMenu(float width, float height)
{
    if (!font.loadFromFile("C:/Users/Luca/Desktop/JoculAnului/Fonts/FruitDays.ttf"))
    {
        cout << "Nu exista font aici";
    }



    //play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::White);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(400, 200);

    //options
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("Rules");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(400, 300);


    //about
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("About");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(400, 400);

    //exit
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::White);
    mainMenu[3].setString("Exit");
    mainMenu[3].setCharacterSize(70);
    mainMenu[3].setPosition(400, 500);


    MainMenuSelected = 0;
}

MainMenu::~MainMenu()
{}
//desenam meniul
void MainMenu::draw(RenderWindow& window)
{
    for (int i = 0; i < Max_main_menu; ++i)

    {
        window.draw(mainMenu[i]);
    }
}
//Moveup
void MainMenu::MoveUp()
{
    if (MainMenuSelected - 1 >= -1)
    {
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        MainMenuSelected--;
        if (MainMenuSelected == -1)
        {
            MainMenuSelected = 3;
        }mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }
}
//Movedown
void MainMenu::MoveDown()
{
    if (MainMenuSelected + 1 <= Max_main_menu)
    {
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        MainMenuSelected++;
        if (MainMenuSelected == 4)
        {
            MainMenuSelected = 0;
        }
        mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }
}
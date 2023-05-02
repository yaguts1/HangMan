#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <ctime>
float WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width;
float WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height;
sf::String keyWordDashes;
int main()
{
    srand(time(0));
    int wordIndex = rand() % 25 + 0;
    sf::String words[26] = { "LAPISEIRA","MACACO","FRUTA","ORNITORRINCO","ESTOJO", "ALCATRAZ", "MACEDONIA", "GREGO","SOCORRO","FELICIDADE","TAREFA","APRENDIZADO","COMPETICAO","TENTATIVAS","ERROS","CONQUISTAS","VITORIA","LEGITIMO","MAR","TERRA","COICE","HABILIDADE","TRABALHO","PAI","FILHA","CEU" };
    sf::String keyWord = words[wordIndex];
    //Creting variables for centering assets
     
     float hangingThingPosX = WINDOW_WIDTH / 2.0f - 352.0f / 2.0f;
     float hangingThingPosY = WINDOW_HEIGHT / 2.0f - 352.0f;
     float farmerHeadPosX = hangingThingPosX + (352.0f / 2.0f);
     float farmerHeadPosY = hangingThingPosY + (352.0f / 3.5f);
     float farmerDeadHeadPosY = hangingThingPosY + (352.0f / 3.0f);

    // Create and set window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jogo da Forca", sf::Style::None);

    // Declare and load a texture
    sf::Texture texture;
    sf::Texture farmerTexture;
    texture.loadFromFile("./assets/obraprima.png");
    farmerTexture.loadFromFile("./assets/farmer.png");
    sf::Texture farmerDeathTexture;
    farmerDeathTexture.loadFromFile("./assets/farmerDeath.png");
    //sf::Texture bodyTexture;
    //bodyTexture.loadFromFile("./assets/body.png");

    //Create a sprite
    sf::Sprite hangingThing;
    hangingThing.setTexture(texture);
    hangingThing.setPosition(hangingThingPosX, hangingThingPosY);

    sf::Sprite farmer;
    farmer.setTexture(farmerTexture);
    farmer.setPosition(farmerHeadPosX,farmerHeadPosY);

    sf::Sprite farmerDeath;
    farmerDeath.setTexture(farmerDeathTexture);
    farmerDeath.setPosition(farmerHeadPosX, farmerDeadHeadPosY);

    /*sf::Sprite body;
    body.setTexture(bodyTexture);
    body.setPosition(WINDOW_WIDTH / 2.014f, WINDOW_HEIGHT / 4.0f);
    */
    // Configure text
    sf::Font font;
    if (!font.loadFromFile("./assets/SpringSnowstorm.ttf"))
    {
        // handle font loading error
        return -1;
    }
    
    sf::Text message("Esc Pressionado! Encerrando jogo...", font, 60);
    sf::Text keyWordSize(std::to_string(keyWord.getSize()), font, 60);
    sf::Text keyWordText(keyWord, font, 60);

    keyWordSize.setFillColor(sf::Color::Black);
    keyWordText.setFillColor(sf::Color::Black);
    message.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = message.getLocalBounds();
    message.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    message.setPosition(sf::Vector2f(window.getSize().x / 2.0f,
        window.getSize().y / 2.0f));

    //Setting the dashes to the size of the word
    for (int i = 0; i < keyWord.getSize(); i++)
    {
        keyWordDashes.insert(0, "- ");
    }
    //Creating text and setting color
    sf::Text keyWordDashesText(keyWordDashes, font, 200);
    keyWordDashesText.setFillColor(sf::Color::Black);
    //Moving the dashes to below the center of the screen
    keyWordDashesText.setOrigin(keyWordDashesText.getLocalBounds().width / 2.0f, 0);
    keyWordDashesText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.8f);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.draw(message);
                window.display();
                sf::sleep(sf::seconds(2)); // sleep for 2 seconds
                window.close();
            }
        }
        window.clear(sf::Color(255, 255, 153));
        window.draw(hangingThing);
        //window.draw(farmer);
        window.draw(farmerDeath);
        //window.draw(body);
        //window.draw(keyWordSize);
        window.draw(keyWordText);
        window.draw(keyWordDashesText);
        window.display();
    }
    return 0;
}

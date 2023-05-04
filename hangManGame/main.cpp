#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <ctime>
int main()
{   
    float WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width;
    float WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height;
    sf::String keyWordDashes;

    srand(time(0));
    int wordIndex = rand() % 25 + 0;
    sf::String words[26] = { "LAPISEIRA","MACACO","FRUTA","ORNITORRINCO","ESTOJO", "ALCATRAZ", "MACEDÔNIA", "GREGO","SOCORRO","FELICIDADE","TAREFA","APRENDIZADO","COMPETIÇÃO","TENTATIVAS","ERROS","CONQUISTAS","VITÓRIA","LEGÍTIMO","MAR","TERRA","COICE","HABILIDADE","TRABALHO","PAI","FILHA","CÉU" };
    sf::String keyWord = words[wordIndex];
    //Creting variables for centering assets
     
     float hangingThingPosX = WINDOW_WIDTH / 2.0f - 352.0f / 2.0f;
     float hangingThingPosY = WINDOW_HEIGHT / 2.0f - 352.0f;
     float farmerHeadPosX = hangingThingPosX + (352.0f / 2.0f);
     float farmerHeadPosY = hangingThingPosY + (352.0f / 3.5f);
     float farmerDeadHeadPosY = hangingThingPosY + (352.0f / 3.0f);

     auto menuSize = ImVec2(4.0f * (WINDOW_WIDTH / 24.0f), 4.0f * WINDOW_HEIGHT / 24.0f);
     bool menuIsOpened = false;

     sf::String guessedLetter = "gh";

    // Create and set window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jogo da Forca", sf::Style::None);
    ImGui::SFML::Init(window);
    sf::Clock clock;
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
    // Load font
    ImGuiIO& io = ImGui::GetIO();
    ImFont* font1 = io.Fonts->AddFontFromFileTTF("./assets/SpringSnowstorm.ttf", 30.0f);
    // Build font atlas
    ImGui::SFML::UpdateFontTexture();
    
    sf::Text message("Esc Pressionado! Encerrando jogo...", font, 60);
    sf::Text keyWordSize(std::to_string(keyWord.getSize()), font, 60);
    sf::Text keyWordText(keyWord, font, 60);
    sf::Text guessedLettersText(guessedLetter, font, 60);

    
    keyWordSize.setFillColor(sf::Color::Black);
    keyWordText.setFillColor(sf::Color::Black);
    message.setFillColor(sf::Color::Black);
    guessedLettersText.setFillColor(sf::Color::Black);

    

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
        ImGui::SFML::Update(window, clock.restart());
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                if (menuIsOpened == true)
                {
                    menuIsOpened = false;   
                }
                else {
                    menuIsOpened = true;
                }

            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code <= 26 && event.key.code >= 0)
                {
                    guessedLetter.insert(guessedLetter.getSize(), char(event.key.code + 65));
                    guessedLettersText.setString(static_cast<std::string>(guessedLetter)); // update text content
                }

            }
                
        }
            
        if (menuIsOpened)
        {
            ImGui::Begin("Menu do Jogo", &menuIsOpened, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
            ImGui::PushFont(font1);
            ImGui::SetWindowPos(ImVec2(WINDOW_WIDTH - menuSize.x, 0));
            ImGui::SetWindowSize(menuSize);
            ImGui::SetWindowFontScale(1.0);
            ImGui::SetCursorPos(ImVec2(menuSize.x / 2.0f - (menuSize.x / 6.0f), menuSize.y / 2.0f - menuSize.y / 5.0f));
            ImGui::Text("Fechar Jogo ?");
            ImGui::SetCursorPos(ImVec2(menuSize.x / 2.6f, menuSize.y / 1.6f));
            if (ImGui::Button("Fechar"))
            {
                window.draw(message);
                window.display();
                sf::sleep(sf::seconds(2)); // sleep for 2 seconds while the message is being displayed
                window.close();
            }


            ImGui::PopFont();
            ImGui::End();
        }
        


        window.clear(sf::Color(255, 255, 153));
        window.draw(hangingThing);
        //window.draw(farmer);
        window.draw(farmerDeath);
        //window.draw(body);
        //window.draw(keyWordSize);
        window.draw(keyWordText);
        window.draw(keyWordDashesText);
        window.draw(guessedLettersText);

        ImGui::SFML::Render(window);         
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}

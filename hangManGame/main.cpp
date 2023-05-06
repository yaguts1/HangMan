#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

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


     sf::String guessedLetter;
     sf::String wrongLetters;
     sf::String alreadyGuessedLetter = "Letra já utilizada!";

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
    sf::Text wrongLettersText(wrongLetters, font, 60);
    sf::Text alreadyGuessedText(alreadyGuessedLetter, font, 60);

    
    keyWordSize.setFillColor(sf::Color::Black);
    keyWordText.setFillColor(sf::Color::Black);
    message.setFillColor(sf::Color::Black);
    guessedLettersText.setFillColor(sf::Color::Green);
    wrongLettersText.setFillColor(sf::Color::Red);
    alreadyGuessedText.setFillColor(sf::Color::Black);

    
    sf::FloatRect messageTextRect = message.getLocalBounds();
    message.setOrigin(messageTextRect.left + messageTextRect.width / 2.0f, messageTextRect.top + messageTextRect.height / 2.0f);
    message.setPosition(sf::Vector2f(window.getSize().x / 2.0f,window.getSize().y / 2.0f));

    sf::FloatRect guessedLettersTextRect = guessedLettersText.getLocalBounds();
    guessedLettersText.setOrigin(guessedLettersTextRect.left + guessedLettersTextRect.width / 2.0f, guessedLettersTextRect.top + guessedLettersTextRect.height / 2.0f);
    guessedLettersText.setPosition(sf::Vector2f(window.getSize().x / 2.5f, guessedLettersTextRect.top + WINDOW_HEIGHT/10.0f));

    sf::FloatRect wrongLettersTextRect = wrongLettersText.getLocalBounds();
    wrongLettersText.setOrigin(wrongLettersTextRect.left + wrongLettersTextRect.width / 2.0f, wrongLettersTextRect.top + wrongLettersTextRect.height / 2.0f);
    wrongLettersText.setPosition(sf::Vector2f(window.getSize().x / 1.5f, wrongLettersTextRect.top));

    sf::FloatRect alreadyGuessedLettersRect = alreadyGuessedText.getLocalBounds();
    alreadyGuessedText.setOrigin(alreadyGuessedLettersRect.left + alreadyGuessedLettersRect.width / 2.0f, alreadyGuessedLettersRect.top + alreadyGuessedLettersRect.height / 2.0f);
    alreadyGuessedText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
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
            {
                window.close();
            }


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
                    
                     // update text content
                    if (keyWord.find(char(event.key.code + 65)) == sf::String::InvalidPos && (wrongLetters.find(char(event.key.code + 65)) == sf::String::InvalidPos))
                    {
                        std::cout << "Nao tem " << char(event.key.code+65)<<" na palavra." << std::endl;
                        wrongLetters.insert(wrongLetters.getSize(), char(event.key.code + 65));
                        wrongLetters.insert(wrongLetters.getSize(), ' ');
                        wrongLetters.insert(wrongLetters.getSize(), '-');
                        wrongLetters.insert(wrongLetters.getSize(), ' ');
                        wrongLettersText.setString(static_cast<std::string>(wrongLetters));

                    }
                    else if(not (keyWord.find(char(event.key.code + 65)) == sf::String::InvalidPos) && (guessedLetter.find(char(event.key.code + 65)) == sf::String::InvalidPos))
                    {
                        guessedLetter.insert(guessedLetter.getSize(), char(event.key.code + 65));
                        guessedLetter.insert(guessedLetter.getSize(), ' ');
                        guessedLetter.insert(guessedLetter.getSize(), '-');
                        guessedLetter.insert(guessedLetter.getSize(), ' ');
                        guessedLettersText.setString(static_cast<std::string>(guessedLetter));
                    }
                    else {
                        window.draw(alreadyGuessedText);
                        window.display();
                        }

                }

            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && menuIsOpened)
            {
                window.draw(message);
                window.display();
                //sf::sleep(sf::seconds(2)); // sleep for 2 seconds while the message is being displayed
                window.close();
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
        window.draw(wrongLettersText);

        ImGui::SFML::Render(window);         
        window.display();
        // Join the thread after the game loop has exited
    }
    ImGui::SFML::Shutdown();
    return 0;
}

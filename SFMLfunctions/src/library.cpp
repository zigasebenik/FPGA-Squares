#include "../include/library.h"

#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

bool texturesUPDATED = false;

void allignToWindowBuffer()
{
    for(int y=0;y<heightWindow;y++)
    {
        for(int x=0; x<widthWindow*4; x+=4)
        {
            windowBuffer[ y*widthWindow*4 + x + 0] = frameBuffer[ y*stride*4 + x + 0];
            windowBuffer[ y*widthWindow*4 + x + 1] = frameBuffer[ y*stride*4 + x + 1];
            windowBuffer[ y*widthWindow*4 + x + 2] = frameBuffer[ y*stride*4 + x + 2];
            windowBuffer[ y*widthWindow*4 + x + 3] = frameBuffer[ y*stride*4 + x + 3];
        }
    }
}

void writeToWindow()
{
    sf::RenderWindow window(sf::VideoMode(widthWindow, heightWindow), "My window");
    window.setFramerateLimit(30);

    sf::BlendMode() ;

    sf::Texture texture;
    if (!texture.create(widthWindow, heightWindow))
        std :: cout << "texture not created\n";

    sf::Sprite sprite;
    sf::Event event;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop

        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
                exit(0);
            }
        }

        texturesUPDATED = false;
        //window.clear( sf :: Color :: Blue);
        allignToWindowBuffer();
        /*texture.setRepeated(false);
        std::cout<<texture.isRepeated();*/
        texture.update(windowBuffer);
        sprite.setTexture(texture);

        /*std::cout<<sprite.getGlobalBounds().width<<std::endl;
        std::cout<<sprite.getGlobalBounds().height<<std::endl;
        std::cout<<sprite.getGlobalBounds().top<<std::endl;*/

        texturesUPDATED = true;


        window.draw(sprite, sf::BlendNone);
        window.display();
    }
}

void initFrameBufferSFML(uint8_t *frameBufferC, int widthC, int heightC, int setStride)
{
    stride = setStride;
    widthWindow = widthC;
    heightWindow = heightC;

    frameBuffer = frameBufferC;
    windowBuffer = (sf::Uint8*)malloc(widthWindow * heightWindow * 4);

    std :: cout << widthWindow << " " << heightWindow << std :: endl;

    std::thread (writeToWindow).detach();
}

bool timeToSwapFrameBuffer()
{
    return texturesUPDATED;
}

void setActiveFrameBuffer(uint8_t *buffer)
{
    frameBuffer = buffer;
}

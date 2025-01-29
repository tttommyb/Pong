#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


class gameObject
{	
	protected:
        sf::Texture object_texture;
        sf::Sprite object_sprite;
        double vect_X = 0;
        double vect_Y = 0;
        double speed = 0;
        int controller_type   = 1; // 0 - AI, 1 - Player
    public:
        gameObject();
        ~gameObject();
        sf::Sprite* getSpritePtr(); // NEW VARIABLE
        double getSpeed();
        void setSpeed(double s);
        float getVectX();
        float getVectY();
        void setVectors(float x, float y);
        int getControllerType();




};

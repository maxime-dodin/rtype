/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-maxime.dodin
** File description:
** Graphics.h
*/
#pragma once

#include <iostream>
#include <any>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "MyClock.hpp"

namespace Resource {
    class Graphics {
    public:

        enum Font {
            FONT1 = 0,
        };

        enum Textures {
            PLAYERS = 0,
            EFFECTS1,
            EFFECTS2,
            EFFECTS3,
            EFFECTS4,
            EFFECTS5,
            PARALAXE,
            BUTTON_EMPTY,
            RTYPE_LOGO,
            LOGO_BACKGROUND,
            BASIC_ENEMIE,
            ADVANCE_ENEMIES,
            ASTRONAUT,
            MDR,
            TEXTURES_COUNT
        };

        enum Musics {
            GAME = 0,
            MENU,
            MUSIC_NUMBER
        };


        enum Sounds {
            EA_SPORT = 0,
            SHOOT,
            MENU_MUSIC,
            GAME_MUSIC,
            BOOM,
            SOUNDS_NUMBER,
       };
        /**
         * @brief Construct a new Graphics object
         *
         */
        Graphics();
        /**
         * @brief Construct a new Graphics object
         *
         * @param x window size x
         * @param y window size y
         */
        Graphics(unsigned int x, unsigned int y);
        /**
         * @brief Construct a new Graphics object
         *
         * @param copy from another graphic compnent
         */
        Graphics(Graphics &copy);
        /**
         * @brief Destroy the Graphics object
         *
         */
        ~Graphics();

        sf::RenderWindow &getWindow();

        sf::Event &getEvents();

        sf::Font &getFont(Font &&);

        sf::View &getCamera();
        /**
         * @brief Get the Clock object
         *
         * @return MyClock&
         */
        MyClock &getClock();
        /**
         * @brief reset clock to reload the delta time
         *
         */
        void resetClock();
        /**
         * @brief Get the Delta Time object
         *
         * @return double&
         */
        double &getDeltaTime();
        /**
         * @brief Set the Camera Size object
         *
         * @param x size x
         * @param y size y
         */
        void setCameraSize(float x, float y);
        /**
         * @brief Set the Camera Center object
         *
         * @param x camera size x
         * @param y camera size y
         */
        void setCameraCenter(float x, float y);
        /**
         * @brief Get the Sound object
         *
         * @return sf::SoundBuffer&
         */
        sf::SoundBuffer &getSound(Sounds &&);
        /**
         * @brief get a sound from a path
         *
         * @param path from the sound
         * @return sf::SoundBuffer&
         */
        sf::SoundBuffer &addSound(const std::string &path);
        /**
         * @brief Get the Textures object
         *
         * @return const std::vector<sf::Texture>&
         */
        const std::vector<sf::Texture> &getTextures() const;
        /**
         * @brief add texture to the map
         *
         * @param path path to the texture
         * @param lol  rect of the texture
         * @return sf::Texture&
         */
        sf::Texture &addTexture(const std::string &path, const sf::IntRect &lol = sf::IntRect());
        /**
         * @brief Get the Texture object
         *
         * @return sf::Texture&
         */
        sf::Texture &getTexture(Textures &&);
        /**
         * @brief Get the Music Source object
         *
         * @return sf::Sound&
         */
        sf::Sound &getMusicSource();
        /**
         * @brief Set the Music object
         *
         * @param sound sound
         */
        void setMusic(const Sounds &sound);
        /**
         * @brief clear the window
         *
         */
        void clear();

    private:
        sf::Event _eventSystem{};
        sf::RenderWindow _window;
        MyClock _clock;
        sf::View _camera;
        std::vector<sf::Font> _font;
        std::vector<sf::Texture> _textures;


        sf::Sound _musicSource;
        std::vector<sf::SoundBuffer> _sounds;


    };
};

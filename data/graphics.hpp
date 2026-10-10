#pragma once

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <string>

#include <SFML/Graphics.hpp>

namespace gph {
    class image {
    public:
        bool loadFromFile(const std::string& filename) {
            return texture.loadFromFile(filename);
        }

        sf::Texture& getTexture() {
            return texture;
        }

    private:
        sf::Texture texture;
    };

    class window {
    public:
        void create(unsigned int width, unsigned int height, const std::string& title) {
            renderWindow.create(sf::VideoMode(sf::Vector2u(width, height)), title);
        }

        sf::RenderWindow& getRenderWindow() {
            return renderWindow;
        }

    private:
        sf::RenderWindow renderWindow;
    };

    class sprite {
    public:
        explicit sprite(image& img) : spr(img.getTexture()) {}

        void setTexture(image& img) {
            spr.setTexture(img.getTexture());
        }

        sf::Sprite& getSprite() {
            return spr;
        }

    private:
        sf::Sprite spr;
    };

    class font {
    public:
        bool loadFromFile(const std::string& filename) {
            return fnt.openFromFile(filename);
        }

        sf::Font& getFont() {
            return fnt;
        }

    private:
        sf::Font fnt;
    };

    class text {
    public:
        explicit text(font& fnt) : txt(fnt.getFont()) {}

        void setString(const std::string& str) {
            txt.setString(str);
        }

        sf::Text& getText() {
            return txt;
        }

    private:
        sf::Text txt;
    };

    class clock {
    public:
        void restart() {
            clk.restart();
        }

        sf::Time getElapsedTime() {
            return clk.getElapsedTime();
        }

    private:
        sf::Clock clk;
    };

    class circle {
    public:
        void setRadius(float radius) {
            circ.setRadius(radius);
        }

        sf::CircleShape& getCircle() {
            return circ;
        }

    private:
        sf::CircleShape circ;
    };

    class rectangle {
    public:
        void setSize(float width, float height) {
            rect.setSize(sf::Vector2f(width, height));
        }

        sf::RectangleShape& getRectangle() {
            return rect;
        }

    private:
        sf::RectangleShape rect;
    };

    class line {
    public:
        line() : vertices(sf::PrimitiveType::Lines, 2) {}

        void setPoints(float x1, float y1, float x2, float y2) {
            vertices[0].position = sf::Vector2f(x1, y1);
            vertices[1].position = sf::Vector2f(x2, y2);
        }

        sf::VertexArray& getLine() {
            return vertices;
        }

    private:
        sf::VertexArray vertices;
    };
}

#endif // GRAPHICS_HPP

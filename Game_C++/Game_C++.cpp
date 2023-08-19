#include <SFML/Graphics.hpp>
#include <cmath>
#include<ctime>
#include<string.h>

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Sin Graph");
    sf::RectangleShape leftpadder(sf::Vector2f(10.f,90.f)), rightpadder(sf::Vector2f(10.f, 90.f));
    sf::Text scoreleft,scoreright;
    int scorel(0), scorer(0);
    sf::Font font;
    font.loadFromFile("../SFML/times.ttf");
    scoreleft.setFont(font);
    scoreleft.setCharacterSize(30);
    scoreleft.setPosition(350, 30);
    scoreleft.setFillColor(sf::Color::Red);

    scoreright.setFont(font);
    scoreright.setCharacterSize(30);
    scoreright.setPosition(400, 30);
    scoreright.setFillColor(sf::Color::Red);

    leftpadder.setFillColor(sf::Color::Blue);
    rightpadder.setFillColor(sf::Color::Red);
    leftpadder.setPosition(0, 355);
    rightpadder.setPosition(790, 355);
    sf::CircleShape Ball;
    int R = 10;
    Ball.setRadius(R);
    Ball.setFillColor(sf::Color::Yellow);
    Ball.setPosition(400, 400);
    float pi = 3.14159f;
    sf::Clock clock;
    float deltatime = 0.f;
    //Setting PADDDER
    float speed = 600.f;
    //Setting Ball
    float Ballspeed = 400.f;
    float angle = 180.f;
    sf::Vector2f pos;
    sf::Vector2f left;
    sf::Vector2f right;
    int win = 0;
    while (window.isOpen()) {
        deltatime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        scoreleft.setString(std::to_string(scorel));
        scoreright.setString(std::to_string(scorer));
        left = leftpadder.getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (left.y - speed * deltatime) >= 0)
        {
            leftpadder.move(0, -speed * deltatime);
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && (left.y + 90 + speed * deltatime) <= 800)
        {
            leftpadder.move(0, speed * deltatime);
        }
        right = rightpadder.getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (right.y - speed * deltatime) >= 0)
        {
            rightpadder.move(0, -speed * deltatime);
        }
        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (right.y + 90 + speed * deltatime) <= 800)
        {
            rightpadder.move(0, speed * deltatime);
        }
        float factor = Ballspeed * deltatime;
        Ball.move(cos(pi * angle / 180) * factor, -sin(pi * angle / 180) * factor);
        //Setting collusion
        pos = Ball.getPosition();
        if (pos.y - R <= 0)
        {
            if(sqrt(angle*angle)<=90)
                angle = -angle + rand() % 20;
            else
                angle = -angle + rand() % 10;
        }
        if (pos.y + R >= 800)
        {
            if (sqrt(angle * angle) >= 270)
                angle = -angle - rand() % 40;
            else
                angle = angle-180 + rand() % 40;
        }
        if (pos.x - R <= left.x + 5
            && pos.y >= left.y
            && pos.y <= left.y + 90
            && pos.x > left.x)
        {
            if (pos.y > left.y)
                angle = rand() % 20 + 30 + angle;
            else
                angle = 180.f - rand() % 20 - 30 + angle;
        }
        if (pos.x + R >= right.x - 5
            && pos.y >= right.y
            && pos.y <= right.y + 90
            && pos.x < right.x)
        {
            if (pos.y > right.y)
                angle = 180.f + rand() % 20 + 30 + angle;
            else
                angle = 180.f - rand() % 20 + 30 + angle;
        }
        if (pos.x <= 0)
        {
            scorel++;
            win = 1;
        }
        if (pos.x >= 800)
        {
            scorer++;
            win = 1;
        }
        if (win == 1)
        {

            win = 0;
            Ball.setPosition(400, 400);
            leftpadder.setPosition(0, 355);
            rightpadder.setPosition(790, 355);
            if (rand() % 2)
                angle = 0;
            else angle = 180;
        }
        window.clear();
        window.draw(rightpadder);
        window.draw(leftpadder);
        window.draw(Ball);
        window.draw(scoreleft);
        window.draw(scoreright);
        window.display();
    }

    return 0;
}

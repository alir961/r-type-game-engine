/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** TitleBanner.hpp
*/

#pragma once

#include <cmath>
#include <SFML/System/Clock.hpp>
#include "Ui.hpp"
#include "engine/modules/animation/IAnimationModule.hpp"

namespace RType {

    /**
     * @brief Big "R-TYPE" title with a subtitle and the player ship floating under it.
     */
    class TitleBanner {
    private:
        ModuleProviderPtr _provider = ModuleProvider::getInstance();
        IGraphicalModule *_module = _provider->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        AnimationPtr _animation = _provider->loadAndGetModule<IAnimationModule>(ModuleType::ANIMATION)->createAnimation("turquoisePlayer");
        SpriteComponent _ship = _module->createSprite("client/assets/sprites/player.png");
        Label _title = Label("R-TYPE", 150, Theme::Accent, Theme::CENTER_X, 70.0F, Align::CENTER);
        Label _subtitle;
        sf::Clock _clock;     /**< Time since the last frame. */
        sf::Clock _lifetime;  /**< Drives the floating motion of the ship. */
        float _animationTime = 0.0F;

    public:
        explicit TitleBanner(const std::string &subtitle)
                : _subtitle(subtitle, 30, Theme::TextDim, Theme::CENTER_X, 262.0F, Align::CENTER) {
            _ship->setScale(Vector2f(5.0F, 5.0F));
            _ship->setRectangle(_animation->getCurrentFrame());
        }

        void draw() {
            const float deltaTime = _clock.restart().asSeconds();
            const float bob = std::sin(_lifetime.getElapsedTime().asSeconds() * 2.0F) * 8.0F;

            _animationTime += deltaTime;
            if (_animationTime >= _animation->getFrameDuration()) {
                _ship->setRectangle(_animation->update());
                _animationTime = 0.0F;
            }
            _ship->setPosition(Vector2f(Theme::CENTER_X - 33.0F * 5.0F / 2.0F, 318.0F + bob));
            _title.draw();
            _subtitle.draw();
            _ship->draw();
        }
    };
}

/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Explosion.hpp
*/

#pragma once

#include <memory>
#include "engine/modules/ModuleProvider.hpp"
#include "engine/modules/animation/IAnimationModule.hpp"
#include "engine/modules/graphical/IGraphicalModule.hpp"

namespace RType {

    /**
     * @brief One-shot explosion played where a ship or a mine is destroyed.
     */
    class Explosion {
    private:
        static constexpr float FRAME_SIZE = 48.0F;

        ModuleProviderPtr _provider = ModuleProvider::getInstance();
        IGraphicalModule *_module = _provider->get<IGraphicalModule>(ModuleType::GRAPHICAL);
        AnimationPtr _animation = _provider->loadAndGetModule<IAnimationModule>(ModuleType::ANIMATION)->createAnimation("explosion");
        SpriteComponent _sprite = _module->createSprite("client/assets/sprites/explosion.png");
        float _time = 0.0F;
        bool _finished = false;

    public:
        /**
         * @param center Where the explosion is centered
         * @param scale Size multiplier (1 = 48px)
         */
        Explosion(const Vector2f &center, float scale) {
            _sprite->setScale(Vector2f(scale, scale));
            _sprite->setPosition(Vector2f(center.first - FRAME_SIZE * scale / 2.0F, center.second - FRAME_SIZE * scale / 2.0F));
            _sprite->setRectangle(_animation->getCurrentFrame());
        }

        void update(float deltaTime) {
            _time += deltaTime;
            while (!_finished && _time >= _animation->getFrameDuration()) {
                const RectFloat frame = _animation->update();

                _time -= _animation->getFrameDuration();
                // The animation loops: going back to the first frame means it has played once.
                _finished = frame.left == 0.0F;
                _sprite->setRectangle(frame);
            }
        }

        [[nodiscard]] bool isFinished() const { return _finished; }

        void draw() {
            if (!_finished)
                _sprite->draw();
        }
    };

    using ExplosionPtr = std::shared_ptr<Explosion>;

}

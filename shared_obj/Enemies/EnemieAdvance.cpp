#include "EnemieAdvance.hpp"

#ifdef CLIENT
    EnemieAdvance::EnemieAdvance(Registry &game) : Shared::AComponents(game, Resource::Graphics::Textures::ADVANCE_ENEMIES) {};
#else
    EnemieAdvance::EnemieAdvance(Registry &game) : Shared::AComponents(game) {};
#endif

EnemieAdvance::~EnemieAdvance() {};

std::size_t EnemieAdvance::spawnEntity() noexcept
{
    auto enemies = _game.spawn_entity();
    _game.tag_entity(enemies, "enemies");
#ifdef CLIENT
    _game.add_entity_to_scene(enemies, "game");
#else
    _game.add_entity_to_scene(enemies, "default");
#endif
    std::size_t entityid = 0;
    srand((unsigned) time(0));
    auto number = rand()%((900 - 1)- 200 + 1) + 200;
    _game.emplace_component<Velocity>(enemies, -50, 0, 0);
    _game.emplace_component<Position>(enemies, 1800, number);
    _game.emplace_component<Scale>(enemies, 2, 2);
    _game.emplace_component<Collider>(enemies, RectangleCollider{.width = 34, .height = 38});
        auto &spawner = _game.emplace_component<Spawner>(enemies, BulletInfo{
        .path = BulletInfo::STRAIGHT,
        .velocity = {-800, 0},
        .speed = 600,
        .damage = 15
    });
    spawner->timeToWait = 0.8;
    spawner->active = true;
    spawner->offset = sf::Vector2f(-18, 20);
    _game.emplace_component<Collider>(enemies, RectangleCollider{.width = 20, .height = 40});

    auto &bonusFollow = _game.emplace_component<Follow>(enemies);
    bonusFollow->type = Follow::SMOOTH;
    bonusFollow->offset = {-20, 20};
    bonusFollow->active = false;
#ifdef CLIENT
        _animationProper.nextFrameOffset = {34, 0};
        _animationProper.firstFramePosition = sf::Vector2f(0, 0);
        _animationProper.frames = 8;
        _animationProper.timeStep = 0.12;
        _animationProper.active = true;
        _animationProper.loop = true;
        _rectProper.rectLeft = 0;
        _rectProper.rectTop = 0;
        _rectProper.rectHeight = 36;
        _rectProper.rectWidth = 33;
#endif
    return enemies;
}

extern "C" std::shared_ptr<Shared::AComponents> getComponent(Registry &game)
{
    return std::shared_ptr<Shared::AComponents>(new EnemieAdvance(game));
}
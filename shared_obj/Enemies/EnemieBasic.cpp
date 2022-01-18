#include "EnemieBasic.hpp"

#ifdef CLIENT
    EnemieBasic::EnemieBasic(Registry &game) : Shared::AComponents(game, Resource::Graphics::Textures::BASIC_ENEMIE) {};
#else
    EnemieBasic::EnemieBasic(Registry &game) : Shared::AComponents(game) {};
#endif

EnemieBasic::~EnemieBasic() {};

std::size_t EnemieBasic::spawnEntity() noexcept
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

    auto &spawner = _game.emplace_component<Spawner>(enemies, BulletInfo{
        .path = BulletInfo::STRAIGHT,
        .velocity = {-350, 0},
        .speed = 600,
        .damage = 15
    });
    spawner->timeToWait = 0.5;
    spawner->active = true;
    spawner->offset = sf::Vector2f(-18, 18);
    _game.emplace_component<Collider>(enemies, RectangleCollider{.width = 20, .height = 40});

    auto &bonusFollow = _game.emplace_component<Follow>(enemies);
    bonusFollow->type = Follow::SMOOTH;
    bonusFollow->offset = {-18, 20};
    bonusFollow->active = false;
#ifdef CLIENT
        _animationProper.nextFrameOffset = {18, 0};
        _animationProper.firstFramePosition = sf::Vector2f(0, 0);
        _animationProper.frames = 3;
        _animationProper.timeStep = 0.1;
        _animationProper.active = true;
        _animationProper.loop = true;
        _rectProper.rectLeft = 0;
        _rectProper.rectTop = 0;
        _rectProper.rectHeight = 36;
        _rectProper.rectWidth = 18;
#endif
    return enemies;
}

extern "C" std::shared_ptr<Shared::AComponents> getComponent(Registry &game)
{
    return std::shared_ptr<Shared::AComponents>(new EnemieBasic(game));
}
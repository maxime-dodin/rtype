#include <iostream>
#include "Registry.hpp"
#include "sparseArray.hpp"
#include "Graphics.hpp"
#include "NtwClient.hpp"
#include "EntityLoad.hpp"

void registerComponents(Registry &);
void addGameSystemsClient(Registry &, Resource::Graphics&, Resource::NtwClient &, EntityLoad &loader);
void addMainMenuSystems(Registry &, Resource::Graphics&, Resource::NtwClient &);
void addMenuJoinLobbySystems(Registry &, Resource::Graphics &, Resource::NtwClient &);
void addMenuCreateLobbySystems(Registry &, Resource::Graphics &, Resource::NtwClient &);
void addMenuLobbySystems(Registry &, Resource::Graphics &, Resource::NtwClient &);

void initLobbyMenu(Registry &game, Resource::Graphics &gr)
{
    //    Mouse Component -> juste la sourie
    auto mouse = game.spawn_entity();
    game.add_entity_to_scene(mouse, "menuLobby");
    game.tag_entity(mouse, "mouse_lobby");
    game.emplace_component<Controllable>(mouse);

    auto mouse_ready = game.spawn_entity();
    game.add_entity_to_scene(mouse_ready, "menuLobby");
    game.tag_entity(mouse_ready, "mouse_lobby_ready");
    game.emplace_component<Controllable>(mouse_ready);

    // Button
    auto buttonTest = game.spawn_entity();
    game.add_entity_to_scene(buttonTest, "menuLobby");
    game.tag_entity(buttonTest, "LinkToJoinLobby");
    game.emplace_component<Position>(buttonTest, 50, 20);
    game.emplace_component<Collider>(buttonTest, RectangleCollider{.width = 160, .height = 80});
    game.emplace_component<Animations>(buttonTest);
    game.emplace_component<Scale>(buttonTest, 20, 10);

    // set texture to button sprite
    auto &buttonTexture = gr.getTexture(Resource::Graphics::Textures::BUTTON_EMPTY); // Should be done elsewhere
    auto &buttonDrawable = game.emplace_component<Sprite>(buttonTest);
    buttonDrawable->sprite.setTexture(buttonTexture);
    buttonDrawable->sprite.setTextureRect(sf::IntRect(0, 0, 8, 8)); // Should maybe be from systems

    // animation button
    auto &animButton = game.get_components<Animations>()[buttonTest];
    animButton->active = true;
    animButton->animations.emplace("buttonEmpty", AnimationData{.texture = buttonTexture, .nextFrameOffset = {8, 0}, .firstFramePosition = {0, 0}, .frames = 3, .timeStep = 1000});
    animButton->currentAnimation = animButton->animations.begin();

    // Simple yellow text
    auto &buttonIU = game.emplace_component<IU>(buttonTest);
    buttonIU->offset = {50, 20};
    buttonIU->color = sf::Color::Yellow;
    buttonIU->text.setString("Back");
    buttonIU->text.setFont(gr.getFont(Resource::Graphics::FONT1));
    buttonIU->text.setCharacterSize(30);

    // SECOND BUTTON
    auto buttonCreate = game.spawn_entity();
    game.add_entity_to_scene(buttonCreate, "menuLobby");
    game.tag_entity(buttonCreate, "ReadyToPlay");
    game.emplace_component<Position>(buttonCreate, 560, 100);
    game.emplace_component<Collider>(buttonCreate, RectangleCollider{.width = 800, .height = 240});
    game.emplace_component<Animations>(buttonCreate);
    game.emplace_component<Scale>(buttonCreate, 100,  30);
    game.emplace_component<Container<bool>>(buttonCreate, true);

    // set texture to button sprite
    auto &buttonTxt = gr.getTexture(Resource::Graphics::Textures::BUTTON_EMPTY); // Should be done elsewhere
    auto &buttonDraw = game.emplace_component<Sprite>(buttonCreate);
    buttonDraw->sprite.setTexture(buttonTxt);
    buttonDraw->sprite.setTextureRect(sf::IntRect(0, 0, 8, 8)); // Should maybe be from systems

    // animation button
    auto &animBut = game.get_components<Animations>()[buttonCreate];
    animBut->active = true;
    animBut->animations.emplace("buttonEmpty", AnimationData{.texture = buttonTxt, .nextFrameOffset = {8, 0}, .firstFramePosition = {0, 0}, .frames = 3, .timeStep = 1000});
    animBut->currentAnimation = animBut->animations.begin();

    // Simple yellow button
    auto &buttonUI = game.emplace_component<IU>(buttonCreate);
    buttonUI->offset = {110, 40};
    buttonUI->color = sf::Color::Green;
    buttonUI->text.setString("READY TO PLAY");
    buttonUI->text.setFont(gr.getFont(Resource::Graphics::FONT1));
    buttonUI->text.setCharacterSize(70);
}

void initMenuJoinLobby(Registry &game, Resource::Graphics &gr)
{
    // mouse
    auto mouse = game.spawn_entity();
    game.add_entity_to_scene(mouse, "menuJoinLobby");
    game.tag_entity(mouse, "mouse_join_lobby");
    game.emplace_component<Controllable>(mouse);

    // RETURN Button
    auto buttonTest = game.spawn_entity();
    game.add_entity_to_scene(buttonTest, "menuJoinLobby");
    game.tag_entity(buttonTest, "LinkToReturnMainMenu");
    game.emplace_component<Position>(buttonTest, 50, 20);
    game.emplace_component<Collider>(buttonTest, RectangleCollider{.width = 160, .height = 80});
    game.emplace_component<Animations>(buttonTest);
    game.emplace_component<Scale>(buttonTest, 20, 10);

    // set texture to button sprite
    auto &buttonTexture = gr.getTexture(Resource::Graphics::Textures::BUTTON_EMPTY); // Should be done elsewhere
    auto &buttonDrawable = game.emplace_component<Sprite>(buttonTest);
    buttonDrawable->sprite.setTexture(buttonTexture);
    buttonDrawable->sprite.setTextureRect(sf::IntRect(0, 0, 8, 8)); // Should maybe be from systems

    // animation button
    auto &animButton = game.get_components<Animations>()[buttonTest];
    animButton->active = true;
    animButton->animations.emplace("buttonEmpty", AnimationData{.texture = buttonTexture, .nextFrameOffset = {8, 0}, .firstFramePosition = {0, 0}, .frames = 3, .timeStep = 1000});
    animButton->currentAnimation = animButton->animations.begin();

    // Simple yellow button
    auto &buttonIU = game.emplace_component<IU>(buttonTest);
    buttonIU->offset = {40, 15};
    buttonIU->color = sf::Color::Blue;
    buttonIU->text.setString("BACK");
    buttonIU->text.setFont(gr.getFont(Resource::Graphics::FONT1));
    buttonIU->text.setCharacterSize(30);

    //
}

void initMenuCreateLobby(Registry &game, Resource::Graphics &gr)
{
//    Mouse Component -> juste la sourie
    auto mouse = game.spawn_entity();
    game.add_entity_to_scene(mouse, "menuCreateLobby");
    game.tag_entity(mouse, "mouse_create_menu");
    game.emplace_component<Controllable>(mouse);

    // RETURN Button
    auto buttonTest = game.spawn_entity();
    game.add_entity_to_scene(buttonTest, "menuCreateLobby");
    game.tag_entity(buttonTest, "LinkToReturnMainMenu");
    game.emplace_component<Position>(buttonTest, 50, 20);
    game.emplace_component<Collider>(buttonTest, RectangleCollider{.width = 160, .height = 80});
    game.emplace_component<Animations>(buttonTest);
    game.emplace_component<Scale>(buttonTest, 20, 10);

    // set texture to button sprite
    auto &buttonTexture = gr.getTexture(Resource::Graphics::Textures::BUTTON_EMPTY); // Should be done elsewhere
    auto &buttonDrawable = game.emplace_component<Sprite>(buttonTest);
    buttonDrawable->sprite.setTexture(buttonTexture);
    buttonDrawable->sprite.setTextureRect(sf::IntRect(0, 0, 8, 8)); // Should maybe be from systems

    // animation button
    auto &animButton = game.get_components<Animations>()[buttonTest];
    animButton->active = true;
    animButton->animations.emplace("buttonEmpty", AnimationData{.texture = buttonTexture, .nextFrameOffset = {8, 0}, .firstFramePosition = {0, 0}, .frames = 3, .timeStep = 1000});
    animButton->currentAnimation = animButton->animations.begin();

    // Simple yellow button
    auto &buttonIU = game.emplace_component<IU>(buttonTest);
    buttonIU->offset = {8, 10};
    buttonIU->color = sf::Color::Green;
    buttonIU->text.setString("     EXIT");
    buttonIU->text.setFont(gr.getFont(Resource::Graphics::FONT1));
    buttonIU->text.setCharacterSize(30);

    // CREATE BUTTON
    auto createButton = game.spawn_entity();
    game.add_entity_to_scene(createButton, "menuCreateLobby");
    game.tag_entity(createButton, "LinkToCreateNewLobby");
    game.emplace_component<Position>(createButton, 640, 700);
    game.emplace_component<Collider>(createButton, RectangleCollider{.width = 640, .height = 200});
    game.emplace_component<Animations>(createButton);
    game.emplace_component<Scale>(createButton, 80, 25);

    // set texture to button sprite
    auto &buttonTxt = gr.getTexture(Resource::Graphics::Textures::BUTTON_EMPTY); // Should be done elsewhere
    auto &buttonDra = game.emplace_component<Sprite>(createButton);
    buttonDra->sprite.setTexture(buttonTxt);
    buttonDra->sprite.setTextureRect(sf::IntRect(0, 0, 8, 8)); // Should maybe be from systems

    // animation button
    auto &animBut = game.get_components<Animations>()[createButton];
    animBut->active = true;
    animBut->animations.emplace("buttonEmpty", AnimationData{.texture = buttonTxt, .nextFrameOffset = {8, 0}, .firstFramePosition = {0, 0}, .frames = 3, .timeStep = 1000});
    animBut->currentAnimation = animBut->animations.begin();

    // Simple yellow button
    auto &buttonUI = game.emplace_component<IU>(createButton);
    buttonUI->offset = {115, 50};
    buttonUI->color = sf::Color::Black;
    buttonUI->text.setString("CREATE NEW LOBBY");
    buttonUI->text.setFont(gr.getFont(Resource::Graphics::FONT1));
    buttonUI->text.setCharacterSize(40);
    buttonUI->text.setOutlineThickness(2);
}

void initMainMenu(Registry &game, Resource::Graphics &gr)
{
//    Mouse Component -> juste la sourie
    auto mouse = game.spawn_entity();
    game.add_entity_to_scene(mouse, "menu");
    game.tag_entity(mouse, "mouse_menu");
    game.emplace_component<Controllable>(mouse);

    // background logo Rtype
    auto logoBackground = game.spawn_entity();
    game.add_entity_to_scene(logoBackground, "menu");
    game.emplace_component<Position>(logoBackground, 660, 30);
    game.emplace_component<Scale>(logoBackground, 2.6, 2);

    auto &logoBgTexture = gr.getTexture(Resource::Graphics::Textures::LOGO_BACKGROUND);
    auto &logoBgSprite = game.emplace_component<Sprite>(logoBackground);
    logoBgSprite->sprite.setTexture(logoBgTexture);
    logoBgSprite->sprite.setTextureRect(sf::IntRect(0, 0, 231, 115));

    // Logo SUPER Rtype
    auto rtypeLogo = game.spawn_entity();
    game.add_entity_to_scene(rtypeLogo, "menu");
    game.emplace_component<Position>(rtypeLogo, 660, 30);
    game.emplace_component<Scale>(rtypeLogo, 1.5, 1.5);

    auto &rtypeLogoTexture = gr.getTexture(Resource::Graphics::Textures::RTYPE_LOGO);
    auto &rtypeLogoSprite = game.emplace_component<Sprite>(rtypeLogo);
    rtypeLogoSprite->sprite.setTexture(rtypeLogoTexture);
    rtypeLogoSprite->sprite.setTextureRect(sf::IntRect(0, 0, 400, 148));

    // Button
    auto buttonTest = game.spawn_entity();
    game.add_entity_to_scene(buttonTest, "menu");
    game.tag_entity(buttonTest, "LinkToCreateLobby");
    game.emplace_component<Position>(buttonTest,  300, 700);
    game.emplace_component<Collider>(buttonTest, RectangleCollider{.width = 320, .height = 120});
    game.emplace_component<Animations>(buttonTest);
    game.emplace_component<Scale>(buttonTest, 40, 15);

    // set texture to button sprite
    auto &buttonTexture = gr.getTexture(Resource::Graphics::Textures::BUTTON_EMPTY); // Should be done elsewhere
    auto &buttonDrawable = game.emplace_component<Sprite>(buttonTest);
    buttonDrawable->sprite.setTexture(buttonTexture);
    buttonDrawable->sprite.setTextureRect(sf::IntRect(0, 0, 8, 8)); // Should maybe be from systems

    // animation button
    auto &animButton = game.get_components<Animations>()[buttonTest];
    animButton->active = true;
    animButton->animations.emplace("buttonEmpty", AnimationData{.texture = buttonTexture, .nextFrameOffset = {8, 0}, .firstFramePosition = {0, 0}, .frames = 3, .timeStep = 1000});
    animButton->currentAnimation = animButton->animations.begin();

    // Simple yellow text
    auto &buttonIU = game.emplace_component<IU>(buttonTest);
    buttonIU->offset = {-25, 25};
    buttonIU->color = sf::Color::Yellow;
    buttonIU->text.setString("         CREATE");
    buttonIU->text.setFont(gr.getFont(Resource::Graphics::FONT1));
    buttonIU->text.setCharacterSize(40);

    // SECOND BUTTON
    auto buttonCreate = game.spawn_entity();
    game.add_entity_to_scene(buttonCreate, "menu");
    game.tag_entity(buttonCreate, "LinkToJoinLobby");
    game.emplace_component<Position>(buttonCreate, 1300, 700);
    game.emplace_component<Collider>(buttonCreate, RectangleCollider{.width = 320, .height = 120});
    game.emplace_component<Animations>(buttonCreate);
    game.emplace_component<Scale>(buttonCreate, 40, 15);

    // set texture to button sprite
    auto &buttonTxt = gr.getTexture(Resource::Graphics::Textures::BUTTON_EMPTY); // Should be done elsewhere
    auto &buttonDraw = game.emplace_component<Sprite>(buttonCreate);
    buttonDraw->sprite.setTexture(buttonTxt);
    buttonDraw->sprite.setTextureRect(sf::IntRect(0, 0, 8, 8)); // Should maybe be from systems

    // animation button
    auto &animBut = game.get_components<Animations>()[buttonCreate];
    animBut->active = true;
    animBut->animations.emplace("buttonEmpty", AnimationData{
        .texture = buttonTxt, 
        .nextFrameOffset = {8, 0}, 
        .firstFramePosition = {0, 0}, 
        .frames = 3, 
        .timeStep = 1000
    });

    animBut->currentAnimation = animBut->animations.begin();

    // Simple yellow button
    auto &buttonUI = game.emplace_component<IU>(buttonCreate);
    buttonUI->offset = {0, 25};
    buttonUI->color = sf::Color::Green;
    buttonUI->text.setString("          JOIN");
    buttonUI->text.setFont(gr.getFont(Resource::Graphics::FONT1));
    buttonUI->text.setCharacterSize(40);
}

void initPlayer(Registry &game, Resource::Graphics &gr)
{
    auto player = game.spawn_entity();

    game.add_entity_to_scene(player, "game");
    game.tag_entity(player, "player");
    game.tag_entity(player, "players");
    game.emplace_component<Velocity>(player, 0, 0, 400);
    game.emplace_component<Animations>(player);
    game.emplace_component<Position>(player, 100, 100);
    game.emplace_component<Scale>(player, 2, 2);
    game.emplace_component<Controllable>(player);
    auto &spawner = game.emplace_component<Spawner>(player, BulletInfo{
            .path = BulletInfo::STRAIGHT,
            .velocity = {400, 0},
            .speed = 600,
            .damage = 15
    });
    spawner->timeToWait = 0.5;
    spawner->offset = sf::Vector2f(30, 17/2 - 2);
    game.emplace_component<Uuid>(player, 0);//c tjr le 0
    game.emplace_component<Collider>(player, RectangleCollider{.width = 33, .height = 17});

    // Add texture to player
    auto &playerTexture = gr.getTexture(Resource::Graphics::Textures::PLAYERS); // Should be done elsewhere
    auto &playerDrawable = game.emplace_component<Sprite>(player);
    playerDrawable->sprite.setTexture(playerTexture);

    playerDrawable->sprite.setTextureRect(sf::IntRect(0, 17, 33, 17)); // Should maybe be from systems

    // Add BasicAnim to player
    auto &playerAnimations = game.get_components<Animations>()[player];
    playerAnimations->animations.emplace("BasicAnim", AnimationData{
        .texture = playerTexture,
        .nextFrameOffset = {33, 0},
        .firstFramePosition = sf::Vector2f(0, 17),
        .frames = 5,
        .timeStep = 0.1
    });
    playerAnimations->currentAnimation = playerAnimations->animations.begin();
    playerAnimations->loop = true;

    // auto &bulletSpawner = game.get_components<Spawner>()[player];
    // bulletSpawner->
}

void initParalaxes(Registry &game, Resource::Graphics &gr)
{
    auto paralaxe = game.spawn_entity();

    game.add_entity_to_scene(paralaxe, "game");
    game.tag_entity(paralaxe, "paralaxe");
    game.emplace_component<Position>(paralaxe, 0, -30);
    game.emplace_component<Velocity>(paralaxe, -350, 0, 0);
    game.emplace_component<Scale>(paralaxe, 1, 1);
    auto &testSprite = game.emplace_component<Sprite>(paralaxe);
    auto &testTexture = gr.addTexture("./assets/textures/paralaxes/ParalaxeElarged.png");
    testSprite->sprite.setTexture(testTexture);
}

void initLevels([[maybe_unused]]Registry &game, [[maybe_unused]]Resource::Graphics &gr)
{
    //auto &mdrTexture = gr.getTexture(Resource::Graphics::MDR);
    auto &lvlTexture = gr.addTexture("./assets/textures/levels/gamemap0.png");

    //level map
    auto level = game.spawn_entity();
    game.add_entity_to_scene(level, "game");
    game.tag_entity(level, "level");
    game.emplace_component<Position>(level, 0, -30);
    game.emplace_component<Velocity>(level, 0, 0, 0);
    game.emplace_component<Scale>(level, 5.5, 5.6);
    auto &lvlSprite = game.emplace_component<Sprite>(level);
    lvlSprite->sprite.setTexture(lvlTexture);

    //screen limit 
    auto lvlDownLimit = game.spawn_entity();
    game.add_entity_to_scene(lvlDownLimit, "game");
    game.tag_entity(lvlDownLimit, "limit");
    game.emplace_component<Position>(lvlDownLimit, ((1920 / 2) - ((225 / 2) * 8.3)), (1080 - 120));
    game.emplace_component<Scale>(lvlDownLimit, 8.3, 0.5);
    game.emplace_component<Collider>(lvlDownLimit, RectangleCollider{.width = 225, .height = 100});
    //auto &lvlDownSprite = game.emplace_component<Sprite>(lvlDownLimit);
    //lvlDownSprite->sprite.setTexture(mdrTexture);
    
    auto lvlUpLimit = game.spawn_entity();
    game.add_entity_to_scene(lvlUpLimit, "game");
    game.tag_entity(lvlUpLimit, "limit");
    game.emplace_component<Position>(lvlUpLimit, ((1920 / 2) - ((225 / 2) * 8.3)), -100);
    game.emplace_component<Scale>(lvlUpLimit, 8.3, 1);
    game.emplace_component<Collider>(lvlUpLimit, RectangleCollider{.width = 225, .height = 100});
    //auto &lvlUpSprite = game.emplace_component<Sprite>(lvlUpLimit);
    //lvlUpSprite->sprite.setTexture(mdrTexture);

    //level design boxes ///////////////////////////////////////////////////////////////
    auto block1 = game.spawn_entity();
    game.add_entity_to_scene(block1, "game");
    game.tag_entity(block1, "level");
    game.emplace_component<Position>(block1, 750, (1080 - 250));
    game.emplace_component<Velocity>(block1, 0, 0, 0);
    game.emplace_component<Scale>(block1, 1.3, 1);
    game.emplace_component<Collider>(block1, RectangleCollider{.width = 100, .height = 225});

    auto block2 = game.spawn_entity();
    game.add_entity_to_scene(block2, "game");
    game.tag_entity(block2, "level");
    game.emplace_component<Position>(block2, 2100, (1080 - 250));
    game.emplace_component<Velocity>(block2, 0, 0, 0);
    game.emplace_component<Scale>(block2, 3, 2);
    game.emplace_component<Collider>(block2, RectangleCollider{.width = 120, .height = 225});

    auto block3 = game.spawn_entity();
    game.add_entity_to_scene(block3, "game");
    game.tag_entity(block3, "level");
    game.emplace_component<Position>(block3, 4650, (1080 - 250));
    game.emplace_component<Velocity>(block3, 0, 0, 0);
    game.emplace_component<Scale>(block3, 1.3, 1);
    game.emplace_component<Collider>(block3, RectangleCollider{.width = 100, .height = 225});

    auto block4 = game.spawn_entity();
    game.add_entity_to_scene(block4, "game");
    game.tag_entity(block4, "level");
    game.emplace_component<Position>(block4, 5300, (1080 - 250));
    game.emplace_component<Velocity>(block4, 0, 0, 0);
    game.emplace_component<Scale>(block4, 1.3, 1);
    game.emplace_component<Collider>(block4, RectangleCollider{.width = 100, .height = 225});

    auto block5 = game.spawn_entity();
    game.add_entity_to_scene(block5, "game");
    game.tag_entity(block5, "level");
    game.emplace_component<Position>(block5, 8100, (1080 - 250));
    game.emplace_component<Velocity>(block5, 0, 0, 0);
    game.emplace_component<Scale>(block5, 1.3, 2.5);
    game.emplace_component<Collider>(block5, RectangleCollider{.width = 100, .height = 225});
    
    //down
    auto block6 = game.spawn_entity();
    game.add_entity_to_scene(block6, "game");
    game.tag_entity(block6, "level");
    game.emplace_component<Position>(block6, 9000, (225 * 2.5) + 50 );
    game.emplace_component<Velocity>(block6, 0, 0, 0);
    game.emplace_component<Scale>(block6, 2, 2.1);
    game.emplace_component<Collider>(block6, RectangleCollider{.width = 100, .height = 225});
    //up
    auto block7 = game.spawn_entity();
    game.add_entity_to_scene(block7, "game");
    game.tag_entity(block7, "level");
    game.emplace_component<Position>(block7, 9000, ((225 * 2.5) / 2 ) - 350 );
    game.emplace_component<Velocity>(block7, 0, 0, 0);
    game.emplace_component<Scale>(block7, 2, 2.1);
    game.emplace_component<Collider>(block7, RectangleCollider{.width = 100, .height = 225});

    //down2
    auto block8 = game.spawn_entity();
    game.add_entity_to_scene(block8, "game");
    game.tag_entity(block8, "level");
    game.emplace_component<Position>(block8, 10700, (225 * 2.5) + 100 );
    game.emplace_component<Velocity>(block8, 0, 0, 0);
    game.emplace_component<Scale>(block8, 2.5, 1.7);
    game.emplace_component<Collider>(block8, RectangleCollider{.width = 100, .height = 225});
    //up2
    auto block9 = game.spawn_entity();
    game.add_entity_to_scene(block9, "game");
    game.tag_entity(block9, "level");
    game.emplace_component<Position>(block9, 10700, ((225 * 2.5) / 2 ) - 350 );
    game.emplace_component<Velocity>(block9, 0, 0, 0);
    game.emplace_component<Scale>(block9, 2.5, 1.7);
    game.emplace_component<Collider>(block9, RectangleCollider{.width = 100, .height = 225});

    //down2end ~
    auto block10 = game.spawn_entity();
    game.add_entity_to_scene(block10, "game");
    game.tag_entity(block10, "level");
    game.emplace_component<Position>(block10, 16700, (225 * 2.5) + 100 );
    game.emplace_component<Velocity>(block10, 0, 0, 0);
    game.emplace_component<Scale>(block10, 3.9, 2.2);
    game.emplace_component<Collider>(block10, RectangleCollider{.width = 100, .height = 225});
    //up2end ~
    auto block11 = game.spawn_entity();
    game.add_entity_to_scene(block11, "game");
    game.tag_entity(block11, "level");
    game.emplace_component<Position>(block11, 16700, ((225 * 2.5) / 2 ) - 350 );
    game.emplace_component<Velocity>(block11, 0, 0, 0);
    game.emplace_component<Scale>(block11, 3.9, 2.2);
    game.emplace_component<Collider>(block11, RectangleCollider{.width = 100, .height = 225});

    //down2end ++
    auto block12 = game.spawn_entity();
    game.add_entity_to_scene(block12, "game");
    game.tag_entity(block12, "level");
    game.emplace_component<Position>(block12, 21500, (225 * 2.5) + 100 );
    game.emplace_component<Velocity>(block12, 0, 0, 0);
    game.emplace_component<Scale>(block12, 2, 1.5);
    game.emplace_component<Collider>(block12, RectangleCollider{.width = 100, .height = 225});
    //up2end ++
    auto block13 = game.spawn_entity();
    game.add_entity_to_scene(block13, "game");
    game.tag_entity(block13, "level");
    game.emplace_component<Position>(block13, 21500, ((225 * 2.5) / 2 ) - 350 );
    game.emplace_component<Velocity>(block13, 0, 0, 0);
    game.emplace_component<Scale>(block13, 2, 1.5);
    game.emplace_component<Collider>(block13, RectangleCollider{.width = 100, .height = 225});

    

    //////////////////////////////////////////////////////////////////////////////////////

    //bonuses
    auto bonus = game.spawn_entity();
    game.add_entity_to_scene(bonus, "game");
    game.emplace_component<Position>(bonus, 900, 500);//la pos a pas bougé wsh
    game.emplace_component<Collider>(bonus, RectangleCollider{.width = 20, .height = 16});

    auto &bonusInfo = game.emplace_component<BeamBonusInfo>(bonus);
    bonusInfo->animationId = 0;
    bonusInfo->beamIndice = 10;
    game.emplace_component<Scale>(bonus, 2, 2);
    game.emplace_component<Velocity>(bonus, 0, 0, 200);
    auto &bonusDrawable = game.emplace_component<Sprite>(bonus);
    auto &bonusAnimations = game.emplace_component<Animations>(bonus);
    auto &bonusTexture = gr.getTexture(Resource::Graphics::EFFECTS2); // Should be done elsewhere
    bonusDrawable->sprite.setTexture(bonusTexture);
    bonusDrawable->sprite.setTextureRect(sf::IntRect(159, 35, 20, 16)); // Should maybe be from systems

    bonusAnimations->animations.emplace("BasicAnim", AnimationData{
            .texture = bonusTexture,
            .nextFrameOffset = {20 + 4, 0},
            .firstFramePosition = sf::Vector2f(159, 35),
            .frames = 5,
            .timeStep = 0.1
    });
    bonusAnimations->currentAnimation = bonusAnimations->animations.begin();
    bonusAnimations->loop = true;
    bonusAnimations->active = true;

    auto &bonusFollow = game.emplace_component<Follow>(bonus);
    bonusFollow->type = Follow::SMOOTH;
    bonusFollow->offset = {33 * 2, 8};

}

void initSounds([[maybe_unused]]Registry &game, [[maybe_unused]]Resource::Graphics &gr)
{
    //auto &audioSounds = gr.getAudioSources();
    //audioSounds.begin()->setBuffer(*gr.getSounds().begin());
    //audioSounds.begin()->play();
    
    //gr.setMusic(Resource::Graphics::MENU);
}

void initText([[maybe_unused]]Registry &game, [[maybe_unused]]Resource::Graphics &gr)
{/*
    auto bonus = game.spawn_entity();
    sf::Font testFont;
    testFont.loadFromFile("./assets/fonts/LiberationSans.ttf");
    // Add text to an entity
    auto &iuDrawable = game.emplace_component<IU>(object);
    iuDrawable->text.setFont(testFont);
    iuDrawable->text.setFillColor(sf::Color::White);
    iuDrawable->text.setString("RTYPE");*/
}

int main([[maybe_unused]] int ac, char **av)
{
    Registry game;

    Resource::Graphics resources;
    Resource::NtwClient client(av[1], std::atoi(av[2]));
    SignalHandler signalHandler;
    signalHandler.setupSignalHandlers();
    EntityLoad loader;

    registerComponents(game);

    resources.setMusic(Resource::Graphics::MENU_MUSIC);

    // SCENE MAIN MENU
    game.add_scene("menu", Registry::Scene());
    game.change_scene("menu");
    game.handle_scenes();
    addMainMenuSystems(game, resources, client);

    initMainMenu(game, resources);

    // SCENE JOIN LOBBY
    game.add_scene("menuJoinLobby", Registry::Scene());
    game.change_scene("menuJoinLobby");
    game.handle_scenes();
    addMenuJoinLobbySystems(game, resources, client);

    initMenuJoinLobby(game, resources);

    // SCENE CREATE LOBBY
    game.add_scene("menuCreateLobby", Registry::Scene());
    game.change_scene("menuCreateLobby");
    game.handle_scenes();
    addMenuCreateLobbySystems(game, resources, client);

    initMenuCreateLobby(game, resources);

    // SCENE GAME
    game.add_scene("game", Registry::Scene());
    game.change_scene("game");
    game.handle_scenes();
    loader.loadEntity(game);
    addGameSystemsClient(game, resources, client, loader);

    initParalaxes(game, resources);
    initLevels(game, resources);
    initText(game, resources);
    initSounds(game, resources);


    // SCENE LOBBY
    game.add_scene("menuLobby", Registry::Scene());
    game.change_scene("menuLobby");
    game.handle_scenes();
    addMenuLobbySystems(game, resources, client);

    initLobbyMenu(game, resources);


    // REMET LA SCENE DE DÉPART
    game.change_scene("menu");
    game.handle_scenes();

    // systems will run in order of adding
    resources.resetClock();
    while (resources.getWindow().isOpen()) {
        game.run_scene_systems();
        game.handle_scenes();
    }
    client.getClient().ReqDisconnectionBySignal((client.getClient().GetTcpClient()->getInLobby().first
        ? client.getClient().GetTcpClient()->getInLobby().second : 0));
    return 0;
}
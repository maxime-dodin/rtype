#include "Registry.hpp"
#include "Graphics.hpp"
#include "sparseArray.hpp"

void manage_levels([[maybe_unused]] Registry &r, Resource::Graphics &resources, sparseArray<Position> &arrPos, sparseArray<Collider> &arrCol, sparseArray<Velocity> &arrVel)
{
    auto levelMap = r.get_tagged_entities("level").begin();
    auto iteLevel = r.get_tagged_entities("level").begin();
    static bool once = false;

    const std::size_t resetPosColliders [] = {0, 750, 2100, 4650, 5300, 
                                        8100, 9000, 9000, 10700, 10700, 
                                        16700, 16700, 21500, 21500};

    int speedMap = -200;

    if (!once) {
        for (int i = 0; i < 13 ; ++i, (*iteLevel++) ) {
            arrPos[*iteLevel]->x = resetPosColliders[i];
            arrVel[*iteLevel]->x = speedMap;
        }/*
        arrPos[*iteLevel]->x = 0;
        arrVel[*iteLevel]->x = speedMap;
        (*iteLevel++);
        arrPos[*iteLevel]->x = 750;
        arrVel[*iteLevel]->x = speedMap;
        (*iteLevel++);
        arrPos[*iteLevel]->x = 2100;
        arrVel[*iteLevel]->x = speedMap;
        (*iteLevel++);
        arrPos[*iteLevel]->x = 4650;
        arrVel[*iteLevel]->x = speedMap;
        (*iteLevel++);
        arrPos[*iteLevel]->x = 5300;
        arrVel[*iteLevel]->x = speedMap;
        (*iteLevel++);
        arrPos[*iteLevel]->x = 8100;
        arrVel[*iteLevel]->x = speedMap;
        (*iteLevel++);
        arrPos[*iteLevel]->x = 9000;
        arrVel[*iteLevel]->x = speedMap;
        (*iteLevel++);
        arrPos[*iteLevel]->x = 9000;
        arrVel[*iteLevel]->x = speedMap;
        (*iteLevel++);
        arrPos[*iteLevel]->x = 10700;
        arrVel[*iteLevel]->x = speedMap;
        (*iteLevel++);
        arrPos[*iteLevel]->x = 10700;
        arrVel[*iteLevel]->x = speedMap;
        (*iteLevel++);
        arrPos[*iteLevel]->x = 16700;
        arrVel[*iteLevel]->x = speedMap;
        (*iteLevel++);
        arrPos[*iteLevel]->x = 16700;
        arrVel[*iteLevel]->x = speedMap;
        (*iteLevel++);
        arrPos[*iteLevel]->x = 21500;
        arrVel[*iteLevel]->x = speedMap;
        (*iteLevel++);
        arrPos[*iteLevel]->x = 21500;
        arrVel[*iteLevel]->x = speedMap;*/

        once = true;
        resources.resetClock();
    }

    //std::cout << "POSX map = " << arrPos[*levelMap]->x << std::endl;
    if (arrPos[*levelMap]->x <= (-23125)) {
        //display text
    }

    //la map est a pos[map]->x <= 1920 * 10 doisplay text
    //la map est a pos[map]->x <= 1920 * 20 change_scene("menu") && all pos init as ^
}
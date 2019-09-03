// intro_scene.inc.c

void func_8029B964(struct Object *parent, s16 xOffset, s16 yOffset, s16 zOffset, s16 pitchOffset,
                   s16 yawOffset, s16 rollOffset, s16 forwardVel, s32 model, void *behavior) {
    struct Object *sp1C = spawn_object(parent, model, behavior);

    sp1C->header.gfx.unk38.animFrame = RandomFloat() * 6.f;
    sp1C->oEndBirdUnk104 = D_8033B6F0[9].unk4[0];
    D_8033B6F0[9].unk4[0] += 1.f;
    sp1C->oPosX += xOffset;
    sp1C->oPosY += yOffset;
    if (gCutsceneTimer > 700)
        sp1C->oPosY += -150.f;
    sp1C->oPosZ += zOffset;
    sp1C->oMoveAnglePitch += pitchOffset;
    sp1C->oMoveAngleYaw += yawOffset;
    sp1C->oMoveAngleRoll += rollOffset;
    sp1C->oForwardVel = forwardVel;
}

void bhv_intro_scene_loop(void) {
    UNUSED struct Object *sp34;

    if (sCutscenePhase != 0) {
        gCurrentObject->oPosX = gCurrLevelCamera->pos[0];
        gCurrentObject->oPosY = gCurrLevelCamera->pos[1];
        gCurrentObject->oPosZ = gCurrLevelCamera->pos[2];
        gCurrentObject->oMoveAnglePitch = 0;
        gCurrentObject->oMoveAngleYaw = 0;

        switch (sCutscenePhase) {
            case 6:
                sp34 = spawn_object(gCurrentObject, MODEL_LAKITU, bhvBeginningLakitu);
                break;
            case 5:
                sp34 = spawn_object(gCurrentObject, MODEL_PEACH, bhvBeginningPeach);
                break;
            case 7:
                func_8029B964(gCurrentObject, 0, 205, 500, 0x1000, 0x6000, -0x1E00, 25, MODEL_BIRDS,
                              bhvEndBirds1);
                func_8029B964(gCurrentObject, 0, 205, 800, 0x1800, 0x6000, -0x1400, 35, MODEL_BIRDS,
                              bhvEndBirds1);
                func_8029B964(gCurrentObject, -100, 300, 500, 0x800, 0x6000, 0, 25, MODEL_BIRDS,
                              bhvEndBirds1);
                func_8029B964(gCurrentObject, 100, -200, 800, 0, 0x4000, 0x1400, 45, MODEL_BIRDS,
                              bhvEndBirds1);
                func_8029B964(gCurrentObject, -80, 300, 350, 0x1800, 0x5000, 0xA00, 35, MODEL_BIRDS,
                              bhvEndBirds1);
                func_8029B964(gCurrentObject, -300, 300, 500, 0x800, 0x6000, 0x2800, 25, MODEL_BIRDS,
                              bhvEndBirds1);
                func_8029B964(gCurrentObject, -400, -200, 800, 0, 0x4000, -0x1400, 45, MODEL_BIRDS,
                              bhvEndBirds1);
                break;
            case 9:
                func_8029B964(gCurrentObject, 50, 205, 500, 0x1000, 0x6000, 0, 35, MODEL_BIRDS,
                              bhvEndBirds1);
                func_8029B964(gCurrentObject, 0, 285, 800, 0x1800, 0x6000, 0, 35, MODEL_BIRDS,
                              bhvEndBirds1);
                break;
            case 8:
                func_8029B964(gCurrentObject, -100, -100, -700, 0, 0, -0xF00, 25, MODEL_BIRDS,
                              bhvEndBirds2);
                func_8029B964(gCurrentObject, -250, 255, -200, 0, 0, -0x1400, 25, MODEL_BIRDS,
                              bhvEndBirds2);
                func_8029B964(gCurrentObject, -100, 155, -600, 0, 0, -0x500, 35, MODEL_BIRDS,
                              bhvEndBirds2);
                func_8029B964(gCurrentObject, 250, 200, -1200, 0, 0, -0x700, 25, MODEL_BIRDS,
                              bhvEndBirds2);
                func_8029B964(gCurrentObject, -250, 255, -700, 0, 0, 0, 25, MODEL_BIRDS, bhvEndBirds2);
                break;
        }

        sCutscenePhase = 0;
    }
}

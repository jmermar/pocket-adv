#pragma once
#include "nds.h"
struct spr {
    u16 color;
    u16* gfx;
};

void init_gfx();

void begin_frame();
void end_frame();

void spr_create(u16 color, struct spr* spr);
void spr_free(struct spr* spr);

void spr_draw(struct spr* spr, int x, int y);
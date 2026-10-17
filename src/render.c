#include "render.h"

int spr_number = 0;

void init_gfx() {
    videoSetMode(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_SPRITE);
	oamInit(&oamMain, SpriteMapping_Bmp_1D_128, false);

	videoSetModeSub(MODE_0_2D);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	oamInit(&oamSub, SpriteMapping_Bmp_1D_128, false);
}

void begin_frame() {
    spr_number = 0;
}

void end_frame() {
    swiWaitForVBlank();
    oamUpdate(&oamSub);
    oamUpdate(&oamMain);
}

void spr_create(u16 color, struct spr* spr) {
    spr->color = color;
    spr->gfx = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_Bmp);
    dmaFillHalfWords(spr->color, spr->gfx, 16*4*2);
}

void spr_free(struct spr* spr) {
    oamFreeGfx(&oamMain, spr->gfx);
    spr->gfx = 0;
}

void spr_draw(struct spr* spr, int x, int y) {
    oamSet(&oamMain, // which display
		spr_number, // the oam entry to set
		x, y, // x & y location
		0, // priority
		15, // palette for 16 color sprite or alpha for bmp sprite
		SpriteSize_16x16, // size
		SpriteColorFormat_Bmp, // color type
		spr->gfx, // the oam gfx
		0, //affine index
		true, //double the size of rotated sprites
		false, //don't hide the sprite
		false, false, //vflip, hflip
		false //apply mosaic
		);
    spr_number++;
}
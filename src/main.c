#include <nds.h>
#include <stdio.h>
#include "render.h"

int score = 0;

int main(int argc, char** argv) {
    init_gfx();

    struct spr red, blue;
    spr_create(ARGB16(1, 31, 0, 0), &red);
    spr_create(ARGB16(1, 0, 12, 31), &blue);

    int frame = 0;

	while(1) {
    begin_frame();
        for (int i = 0; i < 16; i++) {
            int x = i * 16;
            int y = ((i%6) * frame / 4) + (i % 16) * 12;
            struct spr* spr = (i % 2) == 0 ? &red : &blue;
            spr_draw(spr, x, y);
        }

        end_frame();
        frame ++;
	}
	return 0;
}
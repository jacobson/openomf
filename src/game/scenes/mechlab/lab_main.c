#include "game/scenes/mechlab/lab_main.h"
#include "game/gui/trn_menu.h"
#include "game/gui/spritebutton.h"
#include "game/gui/sizer.h"
#include "game/gui/text_render.h"
#include "resources/bk.h"
#include "utils/log.h"

typedef struct {
    const char *text;
    text_direction dir;
    text_halign halign;
    text_valign valign;
    int top;
    int bottom;
    int left;
    int right;
} button_details;

static const button_details details_list[] = {
    {"ARENA", TEXT_HORIZONTAL, TEXT_CENTER, TEXT_TOP, 2, 0, 0, 0},
    {"TRAINING COURSES", TEXT_HORIZONTAL, TEXT_CENTER, TEXT_MIDDLE, 0, 0, 28, 0},
    {"BUY", TEXT_HORIZONTAL, TEXT_CENTER, TEXT_TOP, 2, 0, 0, 0},
    {"SELL", TEXT_HORIZONTAL, TEXT_CENTER, TEXT_TOP, 2, 0, 0, 0},
    {"LOAD", TEXT_HORIZONTAL, TEXT_CENTER, TEXT_MIDDLE, 0, 0, 14, 0},
    {"NEW", TEXT_HORIZONTAL, TEXT_CENTER, TEXT_MIDDLE, 0, 0, 14, 0},
    {"DELETE", TEXT_HORIZONTAL, TEXT_CENTER, TEXT_MIDDLE, 0, 0, 14, 0},
    {"SIM", TEXT_HORIZONTAL, TEXT_CENTER, TEXT_TOP, 2, 0, 0, 0},
    {"QUIT", TEXT_VERTICAL, TEXT_CENTER, TEXT_MIDDLE, 0, 0, 0, 0},
    {"NEW TOURNAMENT", TEXT_HORIZONTAL, TEXT_CENTER, TEXT_MIDDLE, 0, 0, 0, 0},
};

component* lab_main_create(scene *s) {
    animation *main_sheets = &bk_get_info(&s->bk_data, 1)->ani;
    animation *main_buttons = &bk_get_info(&s->bk_data, 8)->ani;

    // Initialize menu, and set button sheet
    sprite *msprite = animation_get_sprite(main_sheets, 2);
    component* menu = trnmenu_create(msprite->data, msprite->pos.x, msprite->pos.y);

    // Default text configuration
    text_settings tconf;
    text_defaults(&tconf);
    tconf.font = FONT_SMALL;

    // Init GUI buttons with locations from the "select" button sprites
    for(int i = 0; i < animation_get_sprite_count(main_buttons); i++) {
        sprite *bsprite = animation_get_sprite(main_buttons, i);
        surface *bsurface = bsprite->data;
        component *button = spritebutton_create(&font_small, details_list[i].text, bsurface, COM_ENABLED, NULL, NULL);
        tconf.valign = details_list[i].valign;
        tconf.halign = details_list[i].halign;
        tconf.padding.top = details_list[i].top;
        tconf.padding.bottom = details_list[i].bottom;
        tconf.padding.left = details_list[i].left;
        tconf.padding.right = details_list[i].right;
        tconf.direction = details_list[i].dir;
        spritebutton_set_text_style(button, &tconf);
        component_set_size_hints(button, bsurface->w, bsurface->h);
        component_set_pos_hints(button, bsprite->pos.x, bsprite->pos.y);
        trnmenu_attach(menu, button);
    }

    return menu;
}
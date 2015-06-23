#include <stdio.h>
#include "game/scenes/mainmenu/menu_audio.h"
#include "game/gui/gui.h"
#include "utils/log.h"
#include "game/utils/settings.h"
#include "audio/music.h"
#include "audio/sound.h"
#include "audio/sources/dumb_source.h"
#include "audio/sources/modplug_source.h"
#include "audio/sources/xmp_source.h"

typedef struct {
    settings_sound old_audio_settings;
    component *lib_selector;
} audio_menu_data;

static const char* mono_opts[] = {"OFF","ON"};

void menu_audio_music_slide(component *c, void *userdata, int pos) {
    music_set_volume(pos/10.0f);
}

void menu_audio_sound_slide(component *c, void *userdata, int pos) {
    sound_set_volume(pos/10.0f);
}

void menu_audio_mono_toggle(component *c, void *userdata, int pos) {
    music_reload();
}

void menu_audio_done(component *c, void *u) {
    menu *m = sizer_get_obj(c->parent);
    m->finished = 1;
}

void menu_audio_library_toggled(component *c, void *userdata, int pos) {
    audio_menu_data *local = userdata;
    (void)(local);
    module_source *sources = music_get_module_sources();
    settings_get()->sound.music_library = sources[pos].id;
    music_reload();
}

void menu_audio_free(component *c) {
    audio_menu_data *local = menu_get_userdata(c);
    free(local);
}

component* menu_audio_create(scene *s) {
    // Menu userdata
    audio_menu_data *local = malloc(sizeof(audio_menu_data));
    memset(local, 0, sizeof(audio_menu_data));
    local->old_audio_settings = settings_get()->sound;

    // Text config
    text_settings tconf;
    text_defaults(&tconf);
    tconf.font = FONT_BIG;
    tconf.halign = TEXT_CENTER;
    tconf.cforeground = color_create(0, 121, 0, 255);

    // Create menu and its header
    component* menu = menu_create(11);
    menu_attach(menu, label_create(&tconf, "AUDIO"));
    menu_attach(menu, filler_create());
    menu_attach(menu, textslider_create_bind(&tconf, "SOUND", 10, 1, menu_audio_sound_slide, NULL, &settings_get()->sound.sound_vol));
    menu_attach(menu, textslider_create_bind(&tconf, "MUSIC", 10, 1, menu_audio_music_slide, NULL, &settings_get()->sound.music_vol));
    menu_attach(menu, textselector_create_bind_opts(&tconf, "MONO", menu_audio_mono_toggle, NULL, &settings_get()->sound.music_mono, mono_opts, 2));

    local->lib_selector = textselector_create(&tconf, "PLAYBACK:", menu_audio_library_toggled, local);
    module_source *sources = music_get_module_sources();
    for(int i = 0; sources[i].name != 0; i++) {
        textselector_add_option(local->lib_selector, sources[i].name);
        if(sources[i].id == settings_get()->sound.music_library) {
            textselector_set_pos(local->lib_selector, i);
        }
    }
    menu_attach(menu, local->lib_selector);

    menu_attach(menu, textbutton_create(&tconf, "DONE", COM_ENABLED, menu_audio_done, s));

    // Userdata & free function for it
    menu_set_userdata(menu, local);
    menu_set_free_cb(menu, menu_audio_free);
    return menu;
}

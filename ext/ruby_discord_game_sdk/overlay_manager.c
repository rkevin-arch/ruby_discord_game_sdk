#include "overlay_manager.h"

VALUE rb_cDiscordOverlayManager;

void rb_discord_init_overlay_manager(VALUE module) {
    rb_cDiscordOverlayManager = rb_define_module_under(module, "OverlayManager");
}

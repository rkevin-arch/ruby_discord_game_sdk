#include "image_manager.h"

VALUE rb_cDiscordImageManager;

void rb_discord_init_image_manager(VALUE module) {
    rb_cDiscordImageManager = rb_define_module_under(module, "ImageManager");
}

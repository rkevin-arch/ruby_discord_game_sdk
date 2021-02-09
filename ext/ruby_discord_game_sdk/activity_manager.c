#include "activity_manager.h"

VALUE rb_cDiscordActivityManager;

void rb_discord_init_activity_manager(VALUE module) {
    rb_cDiscordActivityManager = rb_define_module_under(module, "ActivityManager");
}

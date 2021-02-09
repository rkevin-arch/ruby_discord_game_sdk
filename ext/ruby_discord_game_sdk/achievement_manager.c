#include "achievement_manager.h"

VALUE rb_cDiscordAchievementManager;

void rb_discord_init_achievement_manager(VALUE module) {
    rb_cDiscordAchievementManager = rb_define_module_under(module, "AchievementManager");
}

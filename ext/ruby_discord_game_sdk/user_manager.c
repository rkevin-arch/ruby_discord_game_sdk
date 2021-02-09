#include "user_manager.h"

VALUE rb_cDiscordUserManager;

void rb_discord_init_user_manager(VALUE module) {
    rb_cDiscordUserManager = rb_define_module_under(module, "UserManager");
}

#include "application_manager.h"

VALUE rb_cDiscordApplicationManager;

void rb_discord_init_application_manager(VALUE module) {
    rb_cDiscordApplicationManager = rb_define_module_under(module, "ApplicationManager");
}

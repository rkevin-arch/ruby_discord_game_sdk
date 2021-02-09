#include "network_manager.h"

VALUE rb_cDiscordNetworkManager;

void rb_discord_init_network_manager(VALUE module) {
    rb_cDiscordNetworkManager = rb_define_module_under(module, "NetworkManager");
}

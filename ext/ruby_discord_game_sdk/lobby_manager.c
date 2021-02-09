#include "lobby_manager.h"

VALUE rb_cDiscordLobbyManager;

void rb_discord_init_lobby_manager(VALUE module) {
    rb_cDiscordLobbyManager = rb_define_module_under(module, "LobbyManager");
}

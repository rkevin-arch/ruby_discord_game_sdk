#ifndef RUBY_DISCORD_GAME_SDK_USER_MANAGER_H
#define RUBY_DISCORD_GAME_SDK_USER_MANAGER_H

#include "ruby_discord_game_sdk.h"

extern VALUE rb_cDiscordUserManager;

void rb_discord_init_user_manager(VALUE module);

void rb_discord_on_current_user_update(void* event_data);

#endif /* RUBY_DISCORD_GAME_SDK_USER_MANAGER_H */

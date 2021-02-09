#ifndef RUBY_DISCORD_GAME_SDK_USER_H
#define RUBY_DISCORD_GAME_SDK_USER_H 1

#include "ruby.h"
#include <discord_game_sdk.h>

VALUE rb_discord_user_from_struct(struct DiscordUser* data);
void rb_discord_init_user(VALUE module);

#endif /* RUBY_DISCORD_GAME_SDK_USER_H */

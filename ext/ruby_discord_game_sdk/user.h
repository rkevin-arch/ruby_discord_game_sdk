#ifndef RUBY_DISCORD_GAME_SDK_USER_H
#define RUBY_DISCORD_GAME_SDK_USER_H 1

#include "helpers.h"

extern VALUE rb_cDiscordUser;

DECLARE_DISCORD_TYPE(user, struct DiscordUser)
DECLARE_STANDARD_CALLBACK_FUNC(user, struct DiscordUser)
void rb_discord_init_user(VALUE module);

#endif /* RUBY_DISCORD_GAME_SDK_USER_H */

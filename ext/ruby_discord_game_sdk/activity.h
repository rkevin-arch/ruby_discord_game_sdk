#ifndef RUBY_DISCORD_GAME_SDK_ACTIVITY_H
#define RUBY_DISCORD_GAME_SDK_ACTIVITY_H 1

#include "helpers.h"

extern VALUE rb_cDiscordActivity;

DECLARE_DISCORD_TYPE(activity, struct DiscordActivity)
void rb_discord_init_activity(VALUE module);

#endif /* RUBY_DISCORD_GAME_SDK_ACTIVITY_H */

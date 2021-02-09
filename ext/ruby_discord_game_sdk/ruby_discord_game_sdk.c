#include "ruby_discord_game_sdk.h"
#include "user.h"

VALUE rb_mDiscordGameSDK;

void Init_ruby_discord_game_sdk(void) {
    rb_mDiscordGameSDK = rb_define_module("DiscordGameSDK");
    rb_discord_init_user(rb_mDiscordGameSDK);
}

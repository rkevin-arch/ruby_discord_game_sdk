#include "ruby_discord_game_sdk.h"
#include "user.h"

VALUE rb_mDiscordGameSDK;
VALUE rb_oDiscordPendingCallbacks;

struct DiscordSDK DiscordSDK;

void Init_ruby_discord_game_sdk(void) {
    memset(&DiscordSDK, 0, sizeof(struct DiscordSDK));
    rb_mDiscordGameSDK = rb_define_module("DiscordGameSDK");
    rb_discord_init_user(rb_mDiscordGameSDK);
}

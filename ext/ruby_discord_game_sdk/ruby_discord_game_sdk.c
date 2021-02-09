#include "ruby_discord_game_sdk.h"
#include "user.h"
#include "application_manager.h"
#include "user_manager.h"
#include "image_manager.h"
#include "activity_manager.h"
#include "relationship_manager.h"
#include "lobby_manager.h"
#include "network_manager.h"
#include "overlay_manager.h"
#include "storage_manager.h"
#include "store_manager.h"
#include "voice_manager.h"
#include "achievement_manager.h"


VALUE rb_mDiscordGameSDK;
VALUE rb_oDiscordPendingCallbacks;

struct DiscordSDK DiscordSDK;

void Init_ruby_discord_game_sdk(void) {
    memset(&DiscordSDK, 0, sizeof(struct DiscordSDK));
    rb_mDiscordGameSDK = rb_define_module("DiscordGameSDK");
    rb_discord_init_user(rb_mDiscordGameSDK);
    rb_discord_init_application_manager(rb_mDiscordGameSDK);
    rb_discord_init_user_manager(rb_mDiscordGameSDK);
    rb_discord_init_image_manager(rb_mDiscordGameSDK);
    rb_discord_init_activity_manager(rb_mDiscordGameSDK);
    rb_discord_init_relationship_manager(rb_mDiscordGameSDK);
    rb_discord_init_lobby_manager(rb_mDiscordGameSDK);
    rb_discord_init_network_manager(rb_mDiscordGameSDK);
    rb_discord_init_overlay_manager(rb_mDiscordGameSDK);
    rb_discord_init_storage_manager(rb_mDiscordGameSDK);
    rb_discord_init_store_manager(rb_mDiscordGameSDK);
    rb_discord_init_voice_manager(rb_mDiscordGameSDK);
    rb_discord_init_achievement_manager(rb_mDiscordGameSDK);
}

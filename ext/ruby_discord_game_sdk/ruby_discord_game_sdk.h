#ifndef RUBY_DISCORD_GAME_SDK_H
#define RUBY_DISCORD_GAME_SDK_H 1

#include "ruby.h"
#include <discord_game_sdk.h>
#include "stdbool.h"

struct DiscordSDK { // storing actual discord instance in c, not ruby
    bool initialized;
    struct IDiscordCore* core;
    struct IDiscordApplicationManager* application;
    struct IDiscordUserManager* user;
    struct IDiscordImageManager* image;
    struct IDiscordActivityManager* activity;
    struct IDiscordRelationshipManager* relationship;
    struct IDiscordLobbyManager* lobby;
    struct IDiscordNetworkManager* network;
    struct IDiscordOverlayManager* overlay;
    struct IDiscordStorageManager* storage;
    struct IDiscordStoreManager* store;
    struct IDiscordVoiceManager* voice;
    struct IDiscordAchievementManager* achievement;
    struct IDiscordUserEvents user_events;
    VALUE log_callback;
};

extern struct DiscordSDK DiscordSDK;

extern VALUE rb_mDiscordGameSDK;
extern VALUE rb_oDiscordPendingCallbacks; // array containing callback procs, marked global to not gc

#endif /* RUBY_DISCORD_GAME_SDK_H */

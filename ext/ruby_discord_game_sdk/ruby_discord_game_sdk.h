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
    VALUE log_callback;
    // some stuff specific for user manager
    struct IDiscordUserEvents user_events; // used to store the function pointer for on_current_user_update
    VALUE onCurrentUserUpdate; // will be used if the user wants to register a custom ruby function for this
    bool receivedCurrentUserUpdate; // have we seen at least one currentUserUpdate event yet?
};

extern struct DiscordSDK DiscordSDK;

extern VALUE rb_mDiscordGameSDK;
extern VALUE rb_oDiscordPendingCallbacks; // array containing callback procs, marked global to not gc

#endif /* RUBY_DISCORD_GAME_SDK_H */

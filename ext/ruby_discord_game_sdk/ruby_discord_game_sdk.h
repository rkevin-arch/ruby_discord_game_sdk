#ifndef RUBY_DISCORD_GAME_SDK_H
#define RUBY_DISCORD_GAME_SDK_H 1

#include "ruby.h"

extern VALUE rb_mDiscordGameSDK;
extern VALUE rb_oDiscordPendingCallbacks; // array containing callback procs, marked global to not gc

#endif /* RUBY_DISCORD_GAME_SDK_H */

#include "ruby_discord_game_sdk.h"

VALUE rb_mRubyDiscordGameSdk;

void
Init_ruby_discord_game_sdk(void)
{
  rb_mRubyDiscordGameSdk = rb_define_module("RubyDiscordGameSdk");
}

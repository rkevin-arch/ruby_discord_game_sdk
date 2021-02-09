#include "voice_manager.h"

VALUE rb_cDiscordVoiceManager;

void rb_discord_init_voice_manager(VALUE module) {
    rb_cDiscordVoiceManager = rb_define_module_under(module, "VoiceManager");
}

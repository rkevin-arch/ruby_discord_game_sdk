#include "ruby_discord_game_sdk.h"
#include "user.h"
#include "activity.h"
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

void rb_discord_debug_log(void* hook_data, enum EDiscordLogLevel level, const char* message) {
    if (DiscordSDK.log_callback == Qnil) {
        return;
    }
    VALUE args = rb_ary_new_from_args(2, INT2NUM(level), rb_str_new_cstr(message));
    rb_proc_call(DiscordSDK.log_callback, args);
    puts(message);
}

VALUE rb_discord_init(VALUE self, VALUE client_id, VALUE flags){
    if(DiscordSDK.initialized) {
        rb_raise(rb_eRuntimeError, "Discord SDK already initialized before!");
    }
    struct DiscordCreateParams params;
    DiscordCreateParamsSetDefault(&params);
    params.client_id = NUM2LL(client_id);
    params.flags = NUM2LL(flags);
    enum EDiscordResult result = DiscordCreate(DISCORD_VERSION, &params, &DiscordSDK.core);
    DiscordSDK.log_callback = Qnil;
    if (result != DiscordResult_Ok) {
        DiscordSDK.core = NULL;
        return INT2NUM(result);
    }
    DiscordSDK.initialized = true;
    return INT2NUM(result);
}

VALUE rb_discord_set_log_hook(VALUE self, VALUE loglevel) {
    CHECK_DISCORD_SDK_INITIALIZED
    VALUE proc = rb_discord_get_callback_proc(2);
    if (DiscordSDK.log_callback != Qnil) {
        rb_ary_delete(rb_oDiscordPendingCallbacks, DiscordSDK.log_callback);
    }
    rb_ary_push(rb_oDiscordPendingCallbacks, proc);
    DiscordSDK.log_callback = proc;
    DiscordSDK.core->set_log_hook(DiscordSDK.core, NUM2INT(loglevel), NULL, rb_discord_debug_log);
    return Qnil;
}

VALUE rb_discord_run_callbacks(VALUE self) {
    CHECK_DISCORD_SDK_INITIALIZED
    return INT2NUM(DiscordSDK.core->run_callbacks(DiscordSDK.core));
}

void Init_ruby_discord_game_sdk(void) {
    memset(&DiscordSDK, 0, sizeof(struct DiscordSDK));
    rb_oDiscordPendingCallbacks = rb_ary_new();
    rb_global_variable(&rb_oDiscordPendingCallbacks); // globally load array to prevent garbage collection for anything in it
    rb_mDiscordGameSDK = rb_define_module("DiscordGameSDK");
    rb_define_module_function(rb_mDiscordGameSDK, "init", rb_discord_init, 2);
    rb_define_module_function(rb_mDiscordGameSDK, "set_log_hook", rb_discord_set_log_hook, 1);
    rb_define_module_function(rb_mDiscordGameSDK, "run_callbacks", rb_discord_run_callbacks, 0);

    rb_discord_init_user(rb_mDiscordGameSDK);
    rb_discord_init_activity(rb_mDiscordGameSDK);

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

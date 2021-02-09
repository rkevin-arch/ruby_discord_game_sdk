#include "activity_manager.h"
#include "activity.h"
#include "helpers.h"

VALUE rb_cDiscordActivityManager;

VALUE rb_discord_activity_mananger_update_activity(VALUE self, VALUE activity, VALUE callback) {
    CHECK_DISCORD_MGR_INITIALIZED(activity)
    rb_discord_validate_callback_proc(callback, 1);
    DiscordSDK.activity->update_activity(
        DiscordSDK.activity,
        rb_discord_activity_get_struct(activity),
        (void*) callback,
        discord_callback_wrapper_nodata
    );
    return Qnil;
}

void rb_discord_init_activity_manager(VALUE module) {
    rb_cDiscordActivityManager = rb_define_module_under(module, "ActivityManager");
    rb_define_module_function(rb_cDiscordActivityManager, "update_activity", rb_discord_activity_mananger_update_activity, 2);
}

#include "activity_manager.h"
#include "activity.h"
#include "helpers.h"

VALUE rb_cDiscordActivityManager;

VALUE rb_discord_activity_manager_register_command(VALUE self, VALUE command) {
    CHECK_DISCORD_MGR_INITIALIZED(activity)
    return INT2NUM(DiscordSDK.activity->register_command(
        DiscordSDK.activity,
        StringValueCStr(command)
    ));
}

VALUE rb_discord_activity_manager_register_steam(VALUE self, VALUE steam_id) {
    CHECK_DISCORD_MGR_INITIALIZED(activity)
    return INT2NUM(DiscordSDK.activity->register_steam(
        DiscordSDK.activity,
        NUM2INT(steam_id)
    ));
}

VALUE rb_discord_activity_manager_update_activity(VALUE self, VALUE activity, VALUE callback) {
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

VALUE rb_discord_activity_manager_clear_activity(VALUE self, VALUE callback) {
    CHECK_DISCORD_MGR_INITIALIZED(activity)
    rb_discord_validate_callback_proc(callback, 1);
    DiscordSDK.activity->clear_activity(
        DiscordSDK.activity,
        (void*) callback,
        discord_callback_wrapper_nodata
    );
    return Qnil;
}

VALUE rb_discord_activity_manager_send_request_reply(VALUE self, VALUE user_id, VALUE reply, VALUE callback) {
    CHECK_DISCORD_MGR_INITIALIZED(activity)
    rb_discord_validate_callback_proc(callback, 1);
    DiscordSDK.activity->send_request_reply(
        DiscordSDK.activity,
        NUM2LL(user_id),
        NUM2INT(reply),
        (void*) callback,
        discord_callback_wrapper_nodata
    );
    return Qnil;
}

VALUE rb_discord_activity_manager_send_invite(VALUE self, VALUE user_id, VALUE type, VALUE content, VALUE callback) {
    CHECK_DISCORD_MGR_INITIALIZED(activity)
    rb_discord_validate_callback_proc(callback, 1);
    DiscordSDK.activity->send_invite(
        DiscordSDK.activity,
        NUM2LL(user_id),
        NUM2INT(type),
        StringValueCStr(content),
        (void*) callback,
        discord_callback_wrapper_nodata
    );
    return Qnil;
}

VALUE rb_discord_activity_manager_accept_invite(VALUE self, VALUE user_id, VALUE callback) {
    CHECK_DISCORD_MGR_INITIALIZED(activity)
    rb_discord_validate_callback_proc(callback, 1);
    DiscordSDK.activity->accept_invite(
        DiscordSDK.activity,
        NUM2LL(user_id),
        (void*) callback,
        discord_callback_wrapper_nodata
    );
    return Qnil;
}

void rb_discord_init_activity_manager(VALUE module) {
    rb_cDiscordActivityManager = rb_define_module_under(module, "ActivityManager");
    EXPOSE_FUNCTION(rb_cDiscordActivityManager, activity_manager, register_command, 1);
    EXPOSE_FUNCTION(rb_cDiscordActivityManager, activity_manager, register_steam, 1);
    EXPOSE_FUNCTION(rb_cDiscordActivityManager, activity_manager, update_activity, 2);
    EXPOSE_FUNCTION(rb_cDiscordActivityManager, activity_manager, clear_activity, 1);
    EXPOSE_FUNCTION(rb_cDiscordActivityManager, activity_manager, send_request_reply, 3);
    EXPOSE_FUNCTION(rb_cDiscordActivityManager, activity_manager, send_invite, 4);
    EXPOSE_FUNCTION(rb_cDiscordActivityManager, activity_manager, accept_invite, 2);
}

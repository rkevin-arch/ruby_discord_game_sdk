#include "user_manager.h"
#include "helpers.h"
#include "user.h"

VALUE rb_cDiscordUserManager;

VALUE rb_discord_user_manager_get_current_user(VALUE self) {
    CHECK_DISCORD_MGR_INITIALIZED(user);
    struct DiscordUser current_user;
    DiscordSDK.user->get_current_user(
        DiscordSDK.user,
        &current_user
    );

    return rb_discord_user_from_struct(&current_user);
}

VALUE rb_discord_user_manager_get_user(VALUE self, VALUE user_id, VALUE reply) {
    CHECK_DISCORD_MGR_INITIALIZED(user);
    VALUE callback = rb_discord_get_callback_proc(2);
    DiscordSDK.user->get_user(
        DiscordSDK.user,
        NUM2LL(user_id),
        (void*) callback,
        discord_callback_wrapper_user
    );
    return Qnil;
}

VALUE rb_discord_user_manager_get_current_user_premium_type(VALUE self) { //segfault
    CHECK_DISCORD_MGR_INITIALIZED(user);
    bool* result;
    DiscordSDK.user->get_current_user_premium_type(
        DiscordSDK.user,
        &result
    );

    return BOOL2RB(result);
}

void rb_discord_init_user_manager(VALUE module) {
    rb_cDiscordUserManager = rb_define_module_under(module, "UserManager");
    EXPOSE_FUNCTION(rb_cDiscordUserManager, user_manager, get_current_user, 0);
    EXPOSE_FUNCTION(rb_cDiscordUserManager, user_manager, get_user, 2);
    EXPOSE_FUNCTION(rb_cDiscordUserManager, user_manager, get_current_user_premium_type, 0);
}
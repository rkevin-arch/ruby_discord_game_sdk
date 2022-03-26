#include "user_manager.h"
#include "helpers.h"
#include "user.h"

// sleep for 5ms every time we wait for the current user to become ready
#define RB_DISCORD_USER_SPIN_WAIT_SLEEP_US 5000

VALUE rb_cDiscordUserManager;

enum EDiscordResult rb_discord_spin_until_current_user_update() {
    // assume we already have a user manager (which since we create it on init, we always do)
    // if we need the current user but we haven't gotten a DiscordSDK.receivedCurrentUserUpdate=true
    // then we keep calling `DiscordSDK.core->run_callbacks(DiscordSDK.core)` and spin in place until that happens
    if (DiscordSDK.receivedCurrentUserUpdate) {
        return DiscordResult_Ok;
    }
    enum EDiscordResult result = DiscordSDK.core->run_callbacks(DiscordSDK.core);
    if (result != DiscordResult_Ok) {
        // something went wrong, abort
        return result;
    }
    struct timeval sleeptime;
    sleeptime.tv_sec = 0;
    sleeptime.tv_usec = RB_DISCORD_USER_SPIN_WAIT_SLEEP_US;
    while (!DiscordSDK.receivedCurrentUserUpdate) {
        // this means we are still waiting
        // sleep for a while then retry
        rb_thread_wait_for(sleeptime);
        result = DiscordSDK.core->run_callbacks(DiscordSDK.core);
        if (result != DiscordResult_Ok) {
            // something went wrong, abort
            return result;
        }
    }
    return DiscordResult_Ok;
}

VALUE rb_discord_user_manager_get_current_user(VALUE self) {
    CHECK_DISCORD_MGR_INITIALIZED(user);
    CHECK_DISCORD_RESULT(rb_discord_spin_until_current_user_update());

    struct DiscordUser current_user;
    CHECK_DISCORD_RESULT(DiscordSDK.user->get_current_user(DiscordSDK.user, &current_user));
    return rb_discord_user_from_struct(&current_user);
}

VALUE rb_discord_user_manager_get_user(VALUE self, VALUE user_id) {
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

VALUE rb_discord_user_manager_get_current_user_premium_type(VALUE self) {
    CHECK_DISCORD_MGR_INITIALIZED(user);
    CHECK_DISCORD_RESULT(rb_discord_spin_until_current_user_update());

    enum EDiscordPremiumType result;
    CHECK_DISCORD_RESULT(DiscordSDK.user->get_current_user_premium_type(DiscordSDK.user, &result));
    return INT2NUM(result);
}

//TODO: allow user to set DiscordSDK.onCurrentUserUpdate

void rb_discord_on_current_user_update(void* event_data) {
    // will be called by the discord game sdk if there's an update to the current user
    // we must have at least one of these before running get_current_user
    // set the flag so get_current_user knows we've gotten this
    DiscordSDK.receivedCurrentUserUpdate = true;
    // if the user set their own onCurrentUserUpdate callback, call that as well
    if (DiscordSDK.onCurrentUserUpdate == Qnil) {
        return;
    }
    rb_proc_call(DiscordSDK.onCurrentUserUpdate, rb_ary_new());
}

void rb_discord_init_user_manager(VALUE module) {
    rb_cDiscordUserManager = rb_define_module_under(module, "UserManager");
    EXPOSE_FUNCTION(rb_cDiscordUserManager, user_manager, get_current_user, 0);
    EXPOSE_FUNCTION(rb_cDiscordUserManager, user_manager, get_user, 1);
    EXPOSE_FUNCTION(rb_cDiscordUserManager, user_manager, get_current_user_premium_type, 0);
}

#include "activity.h"
#include "helpers.h"
#include <discord_game_sdk.h>

VALUE rb_cDiscordActivity;

DEFINE_DISCORD_TYPE(activity, struct DiscordActivity)

DEFINE_ATTRIBUTE_INT(activity, type);
DEFINE_ATTRIBUTE_LL(activity, application_id);
DEFINE_ATTRIBUTE_STR(activity, name, 128);
DEFINE_ATTRIBUTE_STR(activity, state, 128);
DEFINE_ATTRIBUTE_STR(activity, details, 128);
DEFINE_ATTRIBUTE_BOOL(activity, instance);

// end attribute getters / setters

void rb_discord_init_activity(VALUE module){
    rb_cDiscordActivity = rb_define_class_under(module, "Activity", rb_cData);
    rb_define_alloc_func(rb_cDiscordActivity, rb_discord_activity_alloc);

    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, type);
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, application_id);
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, name);
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, state);
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, details);
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, instance);
}

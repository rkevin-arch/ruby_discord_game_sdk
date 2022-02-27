#include "activity.h"
#include "helpers.h"
#include <discord_game_sdk.h>

VALUE rb_cDiscordActivity;

DEFINE_DISCORD_TYPE(activity, struct DiscordActivity)

DEFINE_ATTRIBUTE_INT(activity, type)
DEFINE_ATTRIBUTE_LL(activity, application_id)
DEFINE_ATTRIBUTE_STR(activity, name, 128)
DEFINE_ATTRIBUTE_STR(activity, state, 128)
DEFINE_ATTRIBUTE_STR(activity, details, 128)
DEFINE_RENAMED_ATTRIBUTE_LL(activity, timestamp_start, timestamps.start)
DEFINE_RENAMED_ATTRIBUTE_LL(activity, timestamp_end, timestamps.end)
DEFINE_RENAMED_ATTRIBUTE_STR(activity, assets_large_image, assets.large_image, 128)
DEFINE_RENAMED_ATTRIBUTE_STR(activity, assets_large_text, assets.large_text, 128)
DEFINE_RENAMED_ATTRIBUTE_STR(activity, assets_small_image, assets.small_image, 128)
DEFINE_RENAMED_ATTRIBUTE_STR(activity, assets_small_text, assets.small_text, 128)
DEFINE_RENAMED_ATTRIBUTE_STR(activity, party_id, party.id, 128)
DEFINE_RENAMED_ATTRIBUTE_INT(activity, party_current_size, party.size.current_size)
DEFINE_RENAMED_ATTRIBUTE_INT(activity, party_max_size, party.size.max_size)
DEFINE_RENAMED_ATTRIBUTE_STR(activity, secrets_match, secrets.match, 128)
DEFINE_RENAMED_ATTRIBUTE_STR(activity, secrets_join, secrets.join, 128)
DEFINE_RENAMED_ATTRIBUTE_STR(activity, secrets_spectate, secrets.spectate, 128)
DEFINE_ATTRIBUTE_BOOL(activity, instance)

// end attribute getters / setters

void rb_discord_init_activity(VALUE module){
    rb_cDiscordActivity = rb_define_class_under(module, "Activity", rb_cObject);
    rb_define_alloc_func(rb_cDiscordActivity, rb_discord_activity_alloc);

    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, type)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, application_id)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, name)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, state)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, details)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, timestamp_start)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, timestamp_end)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, assets_large_image)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, assets_large_text)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, assets_small_image)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, assets_small_text)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, party_id)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, party_current_size)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, party_max_size)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, secrets_match)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, secrets_join)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, secrets_spectate)
    EXPOSE_ATTRIBUTE(rb_cDiscordActivity, activity, instance)
}

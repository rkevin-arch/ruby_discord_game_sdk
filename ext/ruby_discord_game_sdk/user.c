#include "user.h"
#include "helpers.h"
#include <discord_game_sdk.h>

VALUE rb_cDiscordUser;

DEFINE_DISCORD_TYPE(user, struct DiscordUser)
DEFINE_STANDARD_CALLBACK_FUNC(user, struct DiscordUser, rb_cDiscordUser);

DEFINE_ATTRIBUTE_LL(user, id)
DEFINE_ATTRIBUTE_STR(user, username, 256)
DEFINE_ATTRIBUTE_STR(user, discriminator, 8)
DEFINE_ATTRIBUTE_STR(user, avatar, 128)
DEFINE_ATTRIBUTE_BOOL(user, bot)

void rb_discord_init_user(VALUE module){
    rb_cDiscordUser = rb_define_class_under(module, "User", rb_cObject);
    rb_define_alloc_func(rb_cDiscordUser, rb_discord_user_alloc);

    EXPOSE_ATTRIBUTE(rb_cDiscordUser, user, id)
    EXPOSE_ATTRIBUTE(rb_cDiscordUser, user, username)
    EXPOSE_ATTRIBUTE(rb_cDiscordUser, user, discriminator)
    EXPOSE_ATTRIBUTE(rb_cDiscordUser, user, avatar)
    EXPOSE_ATTRIBUTE(rb_cDiscordUser, user, bot)
}

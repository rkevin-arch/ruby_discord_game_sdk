#include "user.h"
#include "helpers.h"
#include <discord_game_sdk.h>

VALUE rb_cDiscordUser;

DEFINE_DISCORD_TYPE(user, struct DiscordUser)
DEFINE_STANDARD_CALLBACK_FUNC(user, struct DiscordUser, rb_cDiscordUser);

// begin attribute getters / setters

VALUE rb_discord_user_get_id(VALUE self) {
    return LL2NUM(rb_discord_user_get_struct(self)->id);
}

VALUE rb_discord_user_get_username(VALUE self) {
    return rb_str_new_cstr(rb_discord_user_get_struct(self)->username);
}

VALUE rb_discord_user_get_discriminator(VALUE self) {
    return rb_str_new_cstr(rb_discord_user_get_struct(self)->discriminator);
}

VALUE rb_discord_user_get_avatar(VALUE self) {
    return rb_str_new_cstr(rb_discord_user_get_struct(self)->avatar);
}

VALUE rb_discord_user_get_bot(VALUE self) {
    return BOOL2RB(rb_discord_user_get_struct(self)->bot);
}

// end attribute getters / setters

void rb_discord_init_user(VALUE module){
    rb_cDiscordUser = rb_define_class_under(module, "User", rb_cData);
    rb_define_alloc_func(rb_cDiscordUser, rb_discord_user_alloc);

    rb_define_method(rb_cDiscordUser, "id", rb_discord_user_get_id, 0);
    rb_define_method(rb_cDiscordUser, "username", rb_discord_user_get_username, 0);
    rb_define_method(rb_cDiscordUser, "discriminator", rb_discord_user_get_discriminator, 0);
    rb_define_method(rb_cDiscordUser, "avatar", rb_discord_user_get_avatar, 0);
    rb_define_method(rb_cDiscordUser, "bot", rb_discord_user_get_bot, 0);
}

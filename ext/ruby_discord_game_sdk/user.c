#include "user.h"
#include "helpers.h"
#include <discord_game_sdk.h>

VALUE rb_cDiscordUser;

size_t rb_discord_user_dsize(const void* data) {
    return sizeof(struct DiscordUser);
}

const rb_data_type_t rb_discord_user_type = {
    .wrap_struct_name = "DiscordGameSDK::User",
    .function = {
        .dmark = NULL,
        .dfree = free,
        .dsize = rb_discord_user_dsize,
    },
    .data = NULL,
    .flags = RUBY_TYPED_FREE_IMMEDIATELY,
};

VALUE rb_discord_user_alloc(VALUE self) {
    // allocate memory for newly created object
    struct DiscordUser* data = malloc(sizeof(struct DiscordUser));
    memset(data, 0, sizeof(struct DiscordUser));
    return TypedData_Wrap_Struct(self, &rb_discord_user_type, data);
}

inline struct DiscordUser* rb_discord_user_get_struct(VALUE self) {
    // given a user ruby object, return the underlying DiscordUser struct
    struct DiscordUser* data;
    TypedData_Get_Struct(self, struct DiscordUser, &rb_discord_user_type, data);
    return data;
}

void rb_discord_user_set_struct(VALUE self, struct DiscordUser* data) {
    // given a DiscordUser struct, copy its data into the user ruby object
    // this is meant to be called by the callback function only
    memcpy(rb_discord_user_get_struct(self), data, sizeof(struct DiscordUser));
}

VALUE rb_discord_user_from_struct(struct DiscordUser* data) {
    VALUE self = rb_discord_user_alloc(rb_cDiscordUser);
    rb_discord_user_set_struct(self, data);
    return self;
}

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

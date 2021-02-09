#ifndef RUBY_DISCORD_GAME_SDK_HELPERS_H
#define RUBY_DISCORD_GAME_SDK_HELPERS_H 1

#include "ruby.h"
#include "ruby_discord_game_sdk.h"
#include <discord_game_sdk.h>
#define BOOL2RB(val) ((val) ? Qtrue : Qfalse)

#define DECLARE_DISCORD_TYPE(name, ctype) \
    size_t rb_discord_##name##_dsize(const void* data); \
    extern const rb_data_type_t rb_discord_##name##_type; \
    VALUE rb_discord_##name##_alloc(VALUE self); \
    ctype* rb_discord_##name##_get_struct(VALUE self); \
    void rb_discord_##name##_set_struct(VALUE self, ctype* data);

#define DEFINE_DISCORD_TYPE(name, ctype) \
    size_t rb_discord_##name##_dsize(const void* data) { \
        return sizeof(ctype); \
    } \
    \
    const rb_data_type_t rb_discord_##name##_type = { \
        .wrap_struct_name = "DiscordGameSDK_" #name, \
        .function = { \
            .dmark = NULL, \
            .dfree = free, \
            .dsize = rb_discord_##name##_dsize, \
        }, \
        .data = NULL, \
        .flags = RUBY_TYPED_FREE_IMMEDIATELY, \
    }; \
    \
    VALUE rb_discord_##name##_alloc(VALUE self) { \
        /* allocate memory for newly created object */ \
        ctype* data = malloc(sizeof(ctype)); \
        memset(data, 0, sizeof(ctype)); \
        return TypedData_Wrap_Struct(self, &rb_discord_##name##_type, data); \
    } \
    \
    ctype* rb_discord_##name##_get_struct(VALUE self) { \
        /* given a ruby object, return the underlying c struct */ \
        ctype* data; \
        TypedData_Get_Struct(self, ctype, &rb_discord_##name##_type, data); \
        return data; \
    } \
    \
    void rb_discord_##name##_set_struct(VALUE self, ctype* data) { \
        /* given a struct, copy its data into the ruby object */ \
        memcpy(rb_discord_##name##_get_struct(self), data, sizeof(ctype)); \
    }

#define DECLARE_STANDARD_CALLBACK_FUNC(name, ctype) \
    VALUE rb_discord_##name##_from_struct(ctype* data); \
    void discord_callback_wrapper_##name(void* callback_data, enum EDiscordResult result, ctype* data);

#define DEFINE_STANDARD_CALLBACK_FUNC(name, ctype, rbtype) \
    VALUE rb_discord_##name##_from_struct(ctype* data) { \
        VALUE self = rb_discord_##name##_alloc(rbtype); \
        rb_discord_##name##_set_struct(self, data); \
        return self; \
    } \
    void discord_callback_wrapper_##name(void* callback_data, enum EDiscordResult result, ctype* data) { \
        /* standard callback function that accepts a result and a ctype */ \
        /* callback_data should be a VALUE that's a Proc that takes in 2 arguments */ \
        /* unless the user explicitly doesn't want a callback */ \
        if((VALUE)callback_data == Qnil) \
            return; \
        /* first we remove the proc from the rb_oDiscordPendingCallbacks array */ \
        rb_ary_delete(rb_oDiscordPendingCallbacks, (VALUE) callback_data); \
        /* next we construc the ruby object to pass to the proc */ \
        VALUE rb_data = Qnil; \
        if (result == DiscordResult_Ok) { \
            rb_data = rb_discord_##name##_from_struct(data); \
        } \
        /* finally, we call the callback function */ \
        VALUE ary = rb_ary_new_from_args(3, (VALUE)callback_data, INT2NUM(result), rb_data); \
        int state; \
        rb_protect(rb_discord_call_callback, ary, &state); \
        if (state) { \
            /* callback function broke, theres not much we can do other than print out an error */ \
            VALUE exception = rb_sprintf("[DiscordGameSDK] Callback function error: %"PRIsVALUE, rb_errinfo()); \
            fwrite(StringValuePtr(exception), 1, RSTRING_LEN(exception), stderr); \
            rb_set_errinfo(Qnil); \
        } \
    }

#define CHECK_DISCORD_SDK_INITIALIZED \
    if (!DiscordSDK.initialized) \
        rb_raise(rb_eRuntimeError, "The Discord SDK is not initialized. Please call DiscordGameSDK.init first.");

#define CHECK_DISCORD_MGR_INITIALIZED(type) \
    CHECK_DISCORD_SDK_INITIALIZED \
    if (DiscordSDK.type == NULL) { \
        DiscordSDK.type = DiscordSDK.core->get_##type##_manager(DiscordSDK.core); \
    }

#define DEFINE_RENAMED_ATTRIBUTE_INT(type, name, path) \
    VALUE rb_discord_##type##_get_##name(VALUE self) { \
        return INT2NUM(rb_discord_##type##_get_struct(self)->path); \
    } \
    VALUE rb_discord_##type##_set_##name(VALUE self, VALUE val) { \
        rb_discord_##type##_get_struct(self)->path = NUM2INT(val); \
        return Qnil; \
    }

#define DEFINE_RENAMED_ATTRIBUTE_LL(type, name, path) \
    VALUE rb_discord_##type##_get_##name(VALUE self) { \
        return LL2NUM(rb_discord_##type##_get_struct(self)->path); \
    } \
    VALUE rb_discord_##type##_set_##name(VALUE self, VALUE val) { \
        rb_discord_##type##_get_struct(self)->path = NUM2LL(val); \
        return Qnil; \
    }

#define DEFINE_RENAMED_ATTRIBUTE_STR(type, name, path, len) \
    VALUE rb_discord_##type##_get_##name(VALUE self) { \
        return rb_str_new_cstr(rb_discord_##type##_get_struct(self)->path); \
    } \
    VALUE rb_discord_##type##_set_##name(VALUE self, VALUE val) { \
        Check_Type(val, T_STRING); \
        if(RSTRING_LEN(val) >= len) { \
            rb_raise(rb_eArgError, "The length of the string may not exceed %d bytes", len-1); \
        } \
        memcpy(rb_discord_##type##_get_struct(self)->path, StringValuePtr(val), RSTRING_LEN(val)); \
        rb_discord_##type##_get_struct(self)->path[RSTRING_LEN(val)] = '\0'; \
        return Qnil; \
    }

#define DEFINE_RENAMED_ATTRIBUTE_BOOL(type, name, path) \
    VALUE rb_discord_##type##_get_##name(VALUE self) { \
        return BOOL2RB(rb_discord_##type##_get_struct(self)->path); \
    } \
    VALUE rb_discord_##type##_set_##name(VALUE self, VALUE val) { \
        rb_discord_##type##_get_struct(self)->path = RTEST(val); \
    }

#define DEFINE_ATTRIBUTE_INT(type, name) \
    DEFINE_RENAMED_ATTRIBUTE_INT(type, name, name)

#define DEFINE_ATTRIBUTE_LL(type, name) \
    DEFINE_RENAMED_ATTRIBUTE_LL(type, name, name)

#define DEFINE_ATTRIBUTE_STR(type, name, len) \
    DEFINE_RENAMED_ATTRIBUTE_STR(type, name, name, len)

#define DEFINE_ATTRIBUTE_BOOL(type, name) \
    DEFINE_RENAMED_ATTRIBUTE_BOOL(type, name, name)

#define EXPOSE_ATTRIBUTE(klass, type, name) \
    rb_define_method(klass, #name, rb_discord_##type##_get_##name, 0); \
    rb_define_method(klass, #name "=", rb_discord_##type##_set_##name, 1);

void rb_discord_validate_callback_proc(VALUE proc, int argc);
VALUE rb_discord_call_callback(VALUE ary);
void discord_callback_wrapper_nodata(void* callback_data, enum EDiscordResult result);

#endif /* RUBY_DISCORD_GAME_SDK_HELPERS_H */

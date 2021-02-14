#include "helpers.h"
// misc helpers, along with some callback helpers

VALUE rb_discord_get_callback_proc(int argc) {
    if (!rb_block_given_p())
        return Qnil;
    VALUE proc = rb_block_proc();
    if (rb_proc_arity(proc) != argc) {
         rb_raise(rb_eTypeError, "Proc (code block) passed in should take %d arguments, got %d", argc, rb_proc_arity(proc));
    }
    rb_ary_push(rb_oDiscordPendingCallbacks, proc); // adds this proc to a globally loaded array, to not make it garbage collected
    return proc;
}

VALUE rb_discord_call_callback(VALUE ary) {
    VALUE proc = rb_ary_shift(ary);
    return rb_proc_call(proc, ary);
}

void discord_callback_wrapper_nodata(void* callback_data, enum EDiscordResult result) {
    /* standard callback function that only accepts a result */
    /* callback_data should be a VALUE that's a Proc that takes in 1 argument */
    /* unless the user explicitly doesn't want a callback */
    if((VALUE)callback_data == Qnil)
        return;
    /* first we remove the proc from the rb_oDiscordPendingCallbacks array */
    rb_ary_delete(rb_oDiscordPendingCallbacks, (VALUE) callback_data);
    /* then we call the callback function */
    VALUE ary = rb_ary_new_from_args(2, (VALUE)callback_data, INT2NUM(result));
    int state;
    rb_protect(rb_discord_call_callback, ary, &state);
    if (state) {
        /* callback function broke, theres not much we can do other than print out an error */
        VALUE exception = rb_sprintf("[DiscordGameSDK] Callback function error: %"PRIsVALUE, rb_errinfo());
        fwrite(StringValuePtr(exception), 1, RSTRING_LEN(exception), stderr);
        rb_set_errinfo(Qnil);
    }
}

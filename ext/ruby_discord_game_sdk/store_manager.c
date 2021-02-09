#include "store_manager.h"

VALUE rb_cDiscordStoreManager;

void rb_discord_init_store_manager(VALUE module) {
    rb_cDiscordStoreManager = rb_define_module_under(module, "StoreManager");
}

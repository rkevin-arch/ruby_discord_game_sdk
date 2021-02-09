#include "storage_manager.h"

VALUE rb_cDiscordStorageManager;

void rb_discord_init_storage_manager(VALUE module) {
    rb_cDiscordStorageManager = rb_define_module_under(module, "StorageManager");
}

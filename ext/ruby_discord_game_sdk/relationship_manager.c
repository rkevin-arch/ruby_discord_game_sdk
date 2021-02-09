#include "relationship_manager.h"

VALUE rb_cDiscordRelationshipManager;

void rb_discord_init_relationship_manager(VALUE module) {
    rb_cDiscordRelationshipManager = rb_define_module_under(module, "RelationshipManager");
}

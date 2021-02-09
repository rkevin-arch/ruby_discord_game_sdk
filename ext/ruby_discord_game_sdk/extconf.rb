# frozen_string_literal: true

require "mkmf"

HEADER_DIR = File.join(File.dirname(__FILE__), "../../third_party/include")

if not find_header("discord_game_sdk.h", HEADER_DIR)
  abort "Cannot find the Discord Game SDK header"
end

create_makefile("ruby_discord_game_sdk/ruby_discord_game_sdk")

# frozen_string_literal: true

require "mkmf"

THIRDPARTY_DIR = File.join(File.dirname(__FILE__), "../../third_party")
HEADER_DIR = File.join(THIRDPARTY_DIR, "include")
if RUBY_PLATFORM.start_with?("x86_64")
  LIBRARY_DIR = File.join(THIRDPARTY_DIR, "lib/x86_64")
elsif RUBY_PLATFORM.start_with?("i686")
  LIBRARY_DIR = File.join(THIRDPARTY_DIR, "lib/x86")
else
  abort "Unrecognized architecture (not x86 or x86_64)"
end

if not find_header("discord_game_sdk.h", HEADER_DIR)
  abort "Cannot find the Discord Game SDK header"
end

$LDFLAGS += ' -L' + LIBRARY_DIR + ' -Wl,-R. -l:discord_game_sdk.so'
$CFLAGS += ' -g -O0'
create_makefile("ruby_discord_game_sdk/ruby_discord_game_sdk")

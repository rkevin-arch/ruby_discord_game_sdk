# frozen_string_literal: true

require "bundler/gem_tasks"
require "rake/extensiontask"

task build: :compile

Rake::ExtensionTask.new("ruby_discord_game_sdk") do |ext|
  ext.lib_dir = "lib/ruby_discord_game_sdk"
end

task default: %i[clobber compile]

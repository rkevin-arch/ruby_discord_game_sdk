#!/bin/bash
set -xeuo pipefail
# jank shellscript to format the artifact into a `artifact-upload` directory
# sucks that we can't specify a destination path for uploading artifacts cuz this is jank
# usage: run `bin/format-artifact.sh os` where `os` is `ubuntu` or `windows`

# get RUBY_PLATFORM
RUBY_PLATFORM=$(echo 'print(RUBY_PLATFORM)'|ruby)

if [[ "$1" == "ubuntu" ]]; then
    # upload both the linux binaries and the ruby code
    mkdir -p artifact-upload/lib/ruby/$RUBY_PLATFORM
    cp -r lib/* artifact-upload/lib/ruby # most of the lib files, including the .so
    # move lib to the right place, lib include dir is set in modshot by platform
    mv artifact-upload/lib/ruby/ruby_discord_game_sdk/ruby_discord_game_sdk.so artifact-upload/lib/ruby/$RUBY_PLATFORM/
    cp third_party/lib/x86_64/discord_game_sdk.so artifact-upload/lib # the upstream library
    for i in pkg/*; do
        cp -r "$i" "artifact-upload/linux-$(basename $i)" # the gem, not really needed but nice to have
    done
elif [[ "$1" == "windows" ]]; then
    # only upload the windows binaries, the .rb files are already uploaded by the linux version
    mkdir -p artifact-upload/lib/ruby/$RUBY_PLATFORM
    cp -r lib/ruby_discord_game_sdk/ruby_discord_game_sdk.so artifact-upload/lib/ruby/$RUBY_PLATFORM/ # the .so itself
    cp third_party/lib/x86_64/discord_game_sdk.dll artifact-upload/lib # the upstream library
    for i in pkg/*; do
        cp -r "$i" "artifact-upload/windows-$(basename $i)" # the gem, not really needed but nice to have
    done
else
    echo "This script is not meant to be run manually, please don't run me!"
fi

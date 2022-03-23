# Ruby Discord Game SDK

This is a Ruby gem that implements bindings for the Discord [Game SDK](https://discord.com/developers/docs/game-sdk/discord), so your games using Ruby can use these tools. This is developed for [ModShot](https://github.com/Astrabit-ST/Modshot-Core), but any Ruby program should be able to use this.

## Development progress

### Data classes implemented (including the structs that are not implemented but exposed on the parent)

- [x] DiscordUser
- [ ] DiscordOAuth2Token
- [ ] DiscordImageHandle
- [ ] DiscordImageDimensions
- [x] DiscordActivityTimestamps
- [x] DiscordActivityAssets
- [x] DiscordPartySize
- [x] DiscordActivityParty
- [x] DiscordActivitySecrets
- [x] DiscordActivity
- [ ] DiscordPresence
- [ ] DiscordRelationship
- [ ] DiscordLobby
- [ ] DiscordFileStat
- [ ] DiscordEntitlement
- [ ] DiscordSkuPrive
- [ ] DiscordSku
- [ ] DiscordInputMode
- [ ] DiscordUserAchievement

### Managers implemented
- [ ] ApplicationManager
- [ ] UserManager
- [ ] ImageManager
- [x] ActivityManager
- [ ] RelationshipManager
- [ ] LobbyManager
- [ ] NetworkManager
- [ ] OverlayManager
- [ ] StorageManager
- [ ] StoreManager
- [ ] VoiceManager
- [ ] AchievementManager

### Others
- [ ] Core functionality
  - [x] Initialization
  - [ ] Teardown
  - [x] Run callbacks
  - [x] Log hooks
- [x] All enums
- [ ] DiscordLobbyTransaction
- [ ] DiscordLobbySearchQuery
- [ ] Events
  - [ ] UserEvents
  - [ ] ActivityEvents
  - [ ] RelationshipEvents
  - [ ] LobbyEvents
  - [ ] NetworkEvents
  - [ ] OverlayEvents
  - [ ] StoreEvents
  - [ ] VoiceEvents
  - [ ] AchievementEvents

## Usage

This gem should expose the [SDK](https://discord.com/developers/docs/game-sdk/discord) functions without any fluff. For details on what this gem provides, check out Discord's documentation on the SDK.

The things that are different between the SDKs:
- You can instantiate the SDK using `DiscordGameSDK::init(client_id, flags)`. Afterwards, no need to get any managers, just do `DiscordGameSDK::SomeManager::do_something`.
- Enums are just integers under `DiscordGameSDK`. For example, the OK return code is `DiscordGameSDK::Result::Ok`, the Playing activity type is `DiscordGameSDK::ActivityType::Playing`, etc. Check [enums.rb](lib/ruby_discord_game_sdk/enums.rb) for a list.
- For functions that take callbacks, you should use a code block. For example:
  ```ruby
  DiscordGameSDK::ActivityManager.update_activity(activity) do |result|
    # do something with the result. note the update_activity function will return _before_ your code block is called.
  end
  ```
  If you don't care about getting the result (and is fine to ignore the error even if it fails), you can omit the code block.

### Quickstart

This code would set an activity on Discord.

```ruby
require "ruby_discord_game_sdk"
DiscordGameSDK::init(REPLACE_ME_WITH_CLIENT_ID, DiscordGameSDK::CreateFlags::Default)

# add a log hook so you can debug errors
# your code block should take two arguments, one int (log level) and one string
# this code block will be called on any discord log message higher than the level you specified
# this is optional, but highly recommended to catch errors
DiscordGameSDK::set_log_hook(DiscordGameSDK::LogLevel::Debug) do |level, message|
    puts message
end

# make sure this run_callbacks function runs every frame in your game
# you can add this to a function that is called every frame
# for example, add it to the update function in `Game_System.rb`
# (unfortunately RMXP doesn't have a good place to add a function that's called every frame,
# i'm not sure if this actuall will be called outside of a map (e.g. on the menu))
DiscordGameSDK::run_callbacks

# construct an activity
activity = DiscordGameSDK::Activity.new
activity.type = DiscordGameSDK::ActivityType::Playing
activity.state = "In an area of the game"
activity.assets_large_image = "image" # some image you uploaded in the developer portal
activity.timestamp_start = Time.now.to_i

# set the activity
DiscordGameSDK::ActivityManager.update_activity(activity) do |result|
  if result != DiscordGameSDK::Result::Ok
    puts "Set activity failed: " + result.to_s
  end
end
# note this function returns immediately, and the callback function is called later

```

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'ruby_discord_game_sdk'
```

And then execute:

    $ bundle install

Or install it yourself as:

    $ gem install ruby_discord_game_sdk

## Usage

TODO: Write usage instructions here

## Development

After checking out the repo, run `bin/setup` to install dependencies. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and the created tag, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/[USERNAME]/ruby_discord_game_sdk.

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

This gem also uses the [Discord SDK](https://discord.com/developers/docs/game-sdk/discord) (which is kind of the point), which is proprietary. Everything under `third_party/` is owned by Discord.

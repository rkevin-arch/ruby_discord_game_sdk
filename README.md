# Ruby Discord Game SDK

This is a Ruby gem that implements bindings for the Discord [Game SDK](https://discord.com/developers/docs/game-sdk/discord), so your games using Ruby can use these tools. This is developed for [ModShot](https://github.com/Astrabit-ST/Modshot-Core), but any Ruby program should be able to use this.

NOTE: This is a work in progress, and it is currently not usable. The core features are not finished yet.

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
- [ ] Discord
- [ ] Discord
- [ ] Discord
- [ ] Discord
- [ ] Discord

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
  - [ ] Log hooks
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

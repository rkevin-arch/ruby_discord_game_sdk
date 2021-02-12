import os
from conans import CMake, ConanFile, tools

class RubyDiscordGameSDKConan(ConanFile):
    name = "ruby_discord_game_sdk"
    version = "0.0.0"
    license = "MIT"
    url = "https://github.com/rkevin-arch/ruby-discord-game-sdk"
    description = "Ruby bindings for the Discord SDK. Note this conanfile is ONLY meant to build binaries for the ModShot project on Windows (using ruby/2.5.3@eliza/testing), and this is not meant to be a proper conan package."
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "*"
    requires = (
        "ruby/2.5.3@eliza/testing",
    )

    def build(self):
        if os.system("ruby/bin/gem install bundler") != 0:
            raise Exception
        if os.system("bundle install") != 0:
            raise Exception
        if os.system("bundle exec rake") != 0:
            raise Exception
        if os.system("bundle exec rake build") != 0:
            raise Exception
        if os.system("ruby/bin/gem install -l -i build pkg/ruby_discord_game_sdk-*.gem") != 0:
            raise Exception

    def package(self):
        self.copy("*", dst="bin", src="bin")

    def imports(self):
        self.do_copy_deps(self.copy)

    def deploy(self):
        self.copy("*")
        self.do_copy_deps(self.copy_deps)

    def do_copy_deps(self, copy):
        copy("*",
             dst="ruby",
             src="",
             root_package="ruby",
             keep_path=True)
        if self.settings.build_type == "Debug":
            copy("*.pdb", dst="bin", root_package=dep, keep_path=False)

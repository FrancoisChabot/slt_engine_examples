#include "slt/core.h"
#include "slt/log.h"
#include "slt/settings.h"

// Create a setting
// Settings are configurable through code, command line, config file and can
// be used to populate guis easily,
slt::Setting<std::string> message(
    "Hello World",                                        // default value
    "message",                                            // name
    "The name of the player",                             // description
    [](std::string const& v) { return v.length() > 0; }); // validator


int main(int argc, const char* argv[]) {
  //1: Override engine settings default values.
  slt::settings::log_async.set(false);

  //2: Initialize the engine core
  // argc and argv will be used to override engine settings
  slt::Core slt_core(argc, argv);

  //3: Use the logging system
  slt::log->info("The message is {}", message.get());

  //slt_core's destructor will handle cleanup
  return 0;
}

#include "slt/core.h"
#include "slt/file/read.h"
#include "slt/log.h"
#include "slt/settings.h"

slt::Setting<std::string> file_to_read(
    "foo.txt",                                        // default value
    "file_to_read",                                   // name
    "The file to load",                               // description
    [](std::string const& v) { return v.length() > 0; }); // validator

// Realistically, most of your interactions with the file system will be done
// using the resources system, and not the low-level file system.
//
// However, this can still come in handy when writing custom build tools
// or more complex file interactions like streaming. This also serves
// as a nice introduction to the event mechanisms.
//
//  ...
//
// Alright, I confess, this example was written before the resource system
// was a thing, and odds are it's of little real-world value to you.
int main(int argc, const char* argv[]) {
  slt::Core slt_core(argc, argv);

  // Synchronous file loads are highly discouraged by slt, so this may look like
  // a lot of boilerplate for a simple file load. Keep in mind that most
  // applications will already have a main event queue to reuse.
  slt::concur::EventQueue evt_queue;

  bool load_complete = false;
  slt::file::asyncRead(file_to_read.get(), evt_queue,
    [&load_complete](slt::DataBlock d) {
      load_complete = true;
      // Use the file data.
    },
    [&load_complete](slt::file::ReadError e) {
      slt::log->error("failed to load {}, because {}", file_to_read.get(), e.what());
      load_complete = true;
    }
  );

  // There is no need for protecting load_complete with a mutex because the
  // async_read callbacks will be invoked in this main thread.
  evt_queue.executeUntil([&load_complete]() {
    return load_complete;
  });

  return 0;
}

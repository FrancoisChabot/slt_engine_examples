#include "slt/core.h"
#include "slt_runtime/render.h"
#include "slt_runtime/runtime.h"

void update() {
  //...
}

void render() {
  // This use will RAII to handle frame initialization/deinitialization
  slt::render::FrameScope frame_scope;

  // Fill the screen with a white void
  slt::render::clearFrame(slt::white);
}

int main(int argc, const char* argv[]) {
  // Override settings
  slt::settings::window_title.set("Hello window!");
  slt::settings::window_size.set({1280, 720});

  // Create the slt core and runtime
  slt::Core slt_core(argc, argv);
  slt::Runtime slt_runtime;

  // Loop until the user closes the window
  while(slt_runtime.keepRunning()) {
    // This will flush the main event queue, gather inputs, and generally talk
    // with the OS.
    slt_runtime.sync();

    update();
    render();
  }
  return 0;
}

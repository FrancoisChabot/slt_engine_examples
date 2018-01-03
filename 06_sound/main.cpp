#include "slt/core.h"
#include "slt/log.h"
#include "slt_runtime/render.h"
#include "slt_runtime/runtime.h"
#include "slt_runtime/resources.h"
#include "slt_runtime/audio/sound.h"
#include "slt_runtime/audio/emmiter.h"
#include "slt_runtime/gui/widgets/text.h"
#include "slt_runtime/gui/viewport.h"
#include "slt_runtime/gui/renderer/raw_renderer.h"

// For lazyness: force preload the sounds asset
auto  preloadAssets() {
  auto assets = slt::addRegistry("init", slt::RegistryLoadMode::PRELOAD);

  slt::Runtime::instance->getMainQueue().executeUntil([assets]() {
    return !assets->hasPendingLoads();
  });
  return assets;
}

int main(int argc, const char* argv[]) {
  // Override settings
  slt::settings::window_title.set("Hello window!");
  slt::settings::window_size.set({1280, 720});

  // Create the slt core and runtime
  slt::Core slt_core(argc, argv);
  slt::Runtime slt_runtime;

  auto assets = preloadAssets();

  auto sound = assets->getPreloaded<slt::audio::Sound>("bwap");
  slt::audio::Emmiter emmiter;

  emmiter.play(sound);

  // Loop until the ser closes the window
  while(slt_runtime.keepRunning()) {
    // This will flush the main event queue, gather inputs, and generally talk
    // with the OS.
    slt_runtime.sync();


    slt::render::FrameScope frame_scope;
    slt::render::clearFrame(slt::white);
  }
  return 0;
}

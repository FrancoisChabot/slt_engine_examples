#include "slt/core.h"
#include "slt/log.h"
#include "slt_runtime/render.h"
#include "slt_runtime/runtime.h"
#include "slt_runtime/resources.h"
#include "slt_runtime/gui/widgets/text.h"
#include "slt_runtime/gui/viewport.h"
#include "slt_runtime/gui/renderer/raw_renderer.h"

void preloadAssets() {
  // Generally, you will want to have a basic UI ready to go
  // by the time you draw the first frame. We can do this by loading
  // a resource registry in preload mode, and synchronously wait
  // for it to be loaded.

  // Ideally, this should be your only ever synchronous load.
  // (because after that, you should have the assets needed to draw
  // a loading screen).
  auto assets = slt::addRegistry("init", slt::RegistryLoadMode::PRELOAD);

  slt::Runtime::instance->getMainQueue().executeUntil([assets]() {
    return !assets->hasPendingLoads();
  });
}

int main(int argc, const char* argv[]) {
  // Override settings
  slt::settings::window_title.set("Hello window!");
  slt::settings::window_size.set({1280, 720});

  // Create the slt core and runtime
  slt::Core slt_core(argc, argv);
  slt::Runtime slt_runtime;

  slt::gui::Viewport vp({ 1280, 720 });

  preloadAssets();
  slt::gui::Text::default_font = slt::getRegistry("init")->getPreloaded<slt::gui::FontData>("roboto")->getScaled(64);

  slt::gui::RawRenderer gui_renderer(slt::getRegistry("init")->getPreloaded<slt::render::Program>("gui"));


  vp.setRoot(std::make_unique<slt::gui::Text>("Hello World"));

  // Loop until the ser closes the window
  while(slt_runtime.keepRunning()) {
    // This will flush the main event queue, gather inputs, and generally talk
    // with the OS.
    slt_runtime.sync();


    slt::render::FrameScope frame_scope;
    slt::render::clearFrame(slt::white);
    vp.render(gui_renderer);
  }
  return 0;
}

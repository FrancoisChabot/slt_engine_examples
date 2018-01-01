#include "slt/core.h"
#include "slt/log.h"
#include "slt_runtime/render.h"
#include "slt_runtime/runtime.h"
#include "slt_runtime/resources.h"
#include "slt_runtime/drawing/model.h"
#include "slt_runtime/drawing/program.h"
#include "slt_runtime/drawing/texture.h"

// This example introduces the asset management components of SLT.
class MyApp {
public:
  MyApp() {
    using slt::render::Program;
    using slt::render::Texture;

    //1. get the resource registry.
    auto reg = slt::getRegistry("main");

    //2. Lookup resources asynchronously.
    reg->get<Program>("stamp",
      [this](auto p) {
        program_ = std::move(p);
      });
  
    reg->get<Texture>("bird",
      [this](auto t) {
        texture_ = std::move(t);
      });

    // The engine does provide a few commonly used procedural assets.
    model_ = slt::models::createQuad({-1.0f, 1.0f}, {1.0f, -1.0f});
  }

  bool initComplete() {
    return model_ && texture_ && program_;
  }

  void render() {
    slt::render::FrameScope frame_scope;

    slt::render::clearFrame(slt::white);
    
    slt::render::ProgramUsage use_prg(program_);
    slt::render::TextureUsage use_txt(texture_, 0);
    slt::render::draw(model_);
  }

private:
  slt::render::ModelRef model_;
  slt::render::TextureRef texture_;
  slt::render::ProgramRef program_;
};


int main(int argc, const char* argv[]) {
  // Override settings
  slt::settings::window_title.set("Hello window!");
  slt::settings::window_size.set({1280, 720});

  // Create the slt core and runtime
  slt::Core slt_core(argc, argv);
  slt::Runtime slt_runtime;

  // Enable our "main" registry.
  slt::addRegistry("main", slt::RegistryLoadMode::ON_DEMAND);
  MyApp app;
  // Loop until the ser closes the window
  while(slt_runtime.keepRunning()) {
    // This will flush the main event queue, gather inputs, and generally talk
    // with the OS.
    slt_runtime.sync();

    if(app.initComplete()) {
      app.render();
    }
  }
  return 0;
}

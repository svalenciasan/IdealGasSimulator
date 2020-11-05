#include <visualizer/ideal_gas_app.h>

#include <sstream>

using std::stringstream;
namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp()
    : simulator_(glm::vec2(kMargin, kMargin), kImageDimension,
                 kWindowSize - 2 * kMargin) {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}
void IdealGasApp::update() {
  simulator_.Update();
}

void IdealGasApp::draw() {
    ci::Color8u background_color(255, 246, 148);  // light yellow
    ci::gl::clear(background_color);

    simulator_.Draw();
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  vec2 velocity;
  float radius;
  float mass;

  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_LEFT:
      velocity = vec2(-2,-3);
      radius = 10;
      mass = 3;
      simulator_.AddParticle(radius, mass, vec2(kMargin + radius, kMargin + radius), velocity);
      break;

    case ci::app::KeyEvent::KEY_RIGHT:
      velocity = vec2(-3,-2);
      radius = 20;
      mass = 10;
      simulator_.AddParticle(radius, mass, vec2(kMargin + radius, kMargin + radius), velocity);
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      simulator_.Clear();
      break;
  }
}
}  // namespace visualizer

}  // namespace naivebayes

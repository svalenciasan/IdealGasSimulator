#include <visualizer/ideal_gas_app.h>

#include <sstream>

using std::stringstream;
namespace idealgas {

namespace visualizer {
IdealGasApp::IdealGasApp() : simulator_(kTopLeftCorner, kBottomRightCorner),
      firstHistogram_(vec2(50, 50), vec2(350, 300), 6),
      secondHistogram_(vec2(50, 375), vec2(350, 625), 6),
      thirdHistogram_(vec2(50, 700), vec2(350, 950), 6) {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void IdealGasApp::update() {
  ParticleManager particleManager = simulator_.Update();
  firstHistogram_.Update(particleManager, "black");
  secondHistogram_.Update(particleManager, "blue");
  thirdHistogram_.Update(particleManager, "red");
}

void IdealGasApp::draw() {
    ci::Color8u background_color(255, 246, 148);  // light yellow
    ci::gl::clear(background_color);

    simulator_.Draw();
    firstHistogram_.Draw();
    secondHistogram_.Draw();
    thirdHistogram_.Draw();
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  vec2 position;
  vec2 velocity;
  float radius;
  float mass;
  string color;

  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_LEFT:
      velocity = vec2(-2,-3);
      radius = 10;
      position = vec2(kTopLeftCorner.x + radius, kTopLeftCorner.y + radius);
      mass = 3;
      color = "black";
      simulator_.AddParticle(radius, mass, position, velocity, color);
      break;

    case ci::app::KeyEvent::KEY_DOWN:
      velocity = vec2(-3,-2);
      radius = 20;
      position = vec2(kTopLeftCorner.x + radius, kTopLeftCorner.y + radius);
      mass = 10;
      color = "blue";
      simulator_.AddParticle(radius, mass, position, velocity, color);
      break;

    case ci::app::KeyEvent::KEY_RIGHT:
      velocity = vec2(-1.5,-2.4);
      radius = 30;
      position = vec2(kTopLeftCorner.x + radius, kTopLeftCorner.y + radius);
      mass = 20;
      color = "red";
      simulator_.AddParticle(radius, mass, position, velocity, color);
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      simulator_.Clear();
      break;
  }
}
}  // namespace visualizer

}  // namespace naivebayes

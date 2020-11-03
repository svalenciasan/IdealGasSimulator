#include <visualizer/naive_bayes_app.h>
#include <sstream>

using std::stringstream;
namespace idealgas {

namespace visualizer {

NaiveBayesApp::NaiveBayesApp()
    : sketchpad_(glm::vec2(kMargin, kMargin), kImageDimension,
                 kWindowSize - 2 * kMargin) {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}
void NaiveBayesApp::update() {
  sketchpad_.Update();
}

void NaiveBayesApp::draw() {
    ci::Color8u background_color(255, 246, 148);  // light yellow
    ci::gl::clear(background_color);

    sketchpad_.Draw();
}

void NaiveBayesApp::keyDown(ci::app::KeyEvent event) {
  vec2 velocity;
  float radius;

  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_LEFT:
      velocity = vec2(-2,-3);
      radius = 10;
      sketchpad_.AddParticle(radius, vec2(kMargin + radius, kMargin + radius), velocity);
      break;

    case ci::app::KeyEvent::KEY_RIGHT:
      velocity = vec2(-3,-2);
      radius = 20;
      sketchpad_.AddParticle(radius, vec2(kMargin + radius, kMargin + radius), velocity);
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      sketchpad_.Clear();
      break;
  }
}
}  // namespace visualizer

}  // namespace naivebayes

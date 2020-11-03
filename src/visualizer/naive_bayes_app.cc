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

void NaiveBayesApp::draw() {
    ci::Color8u background_color(255, 246, 148);  // light yellow
    ci::gl::clear(background_color);

    sketchpad_.Draw();
}
}  // namespace visualizer

}  // namespace naivebayes

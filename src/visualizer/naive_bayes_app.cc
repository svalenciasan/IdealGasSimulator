#include <visualizer/naive_bayes_app.h>
#include <sstream>

using std::stringstream;
namespace naivebayes {

namespace visualizer {

NaiveBayesApp::NaiveBayesApp(){

}
void NaiveBayesApp::draw() {
    ci::Color8u background_color(255, 246, 148);  // light yellow
    ci::gl::clear(background_color);

    sketchpad_.Draw();

    ci::gl::drawStringCentered(
            "Press Delete to clear the sketchpad. Press Enter to make a prediction.",
            glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("black"));

    ci::gl::drawStringCentered(
            "Prediction: " + std::to_string(current_prediction_),
            glm::vec2(kWindowSize / 2, kWindowSize - kMargin / 2), ci::Color("blue"));
}
}  // namespace visualizer

}  // namespace naivebayes

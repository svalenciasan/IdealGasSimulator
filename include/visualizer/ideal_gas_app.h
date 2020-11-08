#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "simulator.h"

namespace idealgas {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();
  void update() override;
  void draw() override;
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowSize = 1000;
  const double kMargin = 200;
  const size_t kImageDimension = 28;
 private:
  Simulator simulator_;
};

}  // namespace visualizer

}  // namespace naivebayes

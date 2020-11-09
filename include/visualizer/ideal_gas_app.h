#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "simulator.h"
#include "histogram.h"

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
  const vec2 kTopLeftCorner = vec2(400, 200);
  const vec2 kBottomRightCorner = vec2(950, 800);
  //const double kMargin = 200;
 private:
  Simulator simulator_;
  Histogram firstHistogram_;
  Histogram secondHistogram_;
  Histogram thirdHistogram_;

};

}  // namespace visualizer

}  // namespace naivebayes

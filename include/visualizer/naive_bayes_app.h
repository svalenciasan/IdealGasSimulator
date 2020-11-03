#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "sketchpad.h"

namespace idealgas {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class NaiveBayesApp : public ci::app::App {
 public:
  NaiveBayesApp();
  void draw() override;
  const double kWindowSize = 875;
  const double kMargin = 100;
  const size_t kImageDimension = 28;
 private:
  Sketchpad sketchpad_;
};

}  // namespace visualizer

}  // namespace naivebayes

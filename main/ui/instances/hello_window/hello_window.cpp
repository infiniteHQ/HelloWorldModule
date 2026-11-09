#include "hello_window.hpp"
#include "../../../src/module.hpp"

#include <filesystem>
#include <iostream>
#include <string>

namespace ModuleUI {
HelloWindow::HelloWindow(const std::string &name) {
  app_window_ = std::make_shared<Cherry::AppWindow>(name, name);

  app_window_->SetIcon(TextEdit::get_path("resources/icons/edit.png"));

  app_window_->m_CloseCallback = [=]() {
    Cherry::DeleteAppWindow(app_window_);
    app_window_->SetVisibility(false);
  };
}
std::shared_ptr<Cherry::AppWindow> &HelloWindow::get_app_window() {
  return app_window_;
}

std::shared_ptr<HelloWindow> HelloWindow::create(const std::string &name) {
  auto instance = std::shared_ptr<HelloWindow>(new HelloWindow(name));
  instance->setup_render_callback();
  return instance;
}

void HelloWindow::setup_render_callback() {
  auto self = shared_from_this();
  app_window_->SetRenderCallback([self]() {
    if (self) {
      self->render();
    }
  });
}

void HelloWindow::render() {
  CherryApp.PushComponentPool(&component_pool_);

  CherryKit::TextSimple("Hello module");

  CherryApp.PopComponentPool();
}

}; // namespace ModuleUI

#pragma once
#include <vxcore/include/vortex.h>
#include <vxcore/include/vortex_internals.h>

#ifndef TEXT_EDITOR_HPP
#define TEXT_EDITOR_HPP

namespace ModuleUI {

class HelloWindow : public std::enable_shared_from_this<HelloWindow> {
public:
  HelloWindow(const std::string &name);

  void menubar();
  void render();

  std::shared_ptr<Cherry::AppWindow> &get_app_window();
  static std::shared_ptr<HelloWindow> create(const std::string &name);
  void setup_render_callback();

private:
  std::shared_ptr<Cherry::AppWindow> app_window_;
  ComponentsPool component_pool_;
};
}; // namespace ModuleUI

#endif // LOGUTILITY_H

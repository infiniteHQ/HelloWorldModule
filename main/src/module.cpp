#include "module.hpp"

// runtime pointer
#ifndef CTextEdit
std::weak_ptr<HelloWorldModule::Context> CTextEdit;
#endif

std::shared_ptr<HelloWorldModule::Context> HelloWorldModule::create_context() {
  auto ctx = std::make_shared<HelloWorldModule::Context>();

  set_current_context(ctx);

  return ctx;
}

void HelloWorldModule::destroy_context(
    std::shared_ptr<HelloWorldModule::Context> ctx) {
  set_current_context(nullptr);
}

void HelloWorldModule::set_current_context(
    std::shared_ptr<HelloWorldModule::Context> ctx) {
  CTextEdit = ctx;
}

std::shared_ptr<HelloWorldModule::Context>
HelloWorldModule::get_current_context() {
  return CTextEdit.lock();
}

std::string HelloWorldModule::get_path(const std::string &path) {
  return get_current_context()->m_interface->cook_path(path);
}

bool HelloWorldModule::IsValidFile(const std::string &path) {
  namespace fs = std::filesystem;

  if (!fs::is_directory(path)) {
    return false;
  }

  for (const auto &entry : fs::directory_iterator(path)) {
    if (entry.is_regular_file() &&
        entry.path().filename() == "SampleConfig.txt") {
      return true;
    }
  }

  return false;
}

void HelloWorldModule::StartTextEditorInstance(const std::string &path) {
  std::string filename = fs::path(path).filename().string();

  const size_t maxLen = 24;
  if (filename.size() > maxLen) {
    filename = filename.substr(0, maxLen - 3) + "...";
  }

  std::string window_name =
      std::to_string(get_current_context()->m_text_editor_instances.size());

  auto inst = ModuleUI::HelloWindow::create(window_name);
  Cherry::AddAppWindow(inst->get_app_window());
  HelloWorldModule::get_current_context()->m_text_editor_instances.push_back(
      inst);
}

void HelloWorldModule::oe_save_all() {}
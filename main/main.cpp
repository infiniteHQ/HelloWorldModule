#include "./src/module.hpp"

class infinitehq_textedit : public ModuleInterface {
public:
  std::shared_ptr<HelloWorldModule::Context> ctx;
  void execute() override {
    ctx = HelloWorldModule::create_context();

    auto m = ModuleInterface::get_editor_module_by_name(this->name());
    HelloWorldModule::get_current_context()->m_interface = m;

    // Add item handler for simple txt files
    this->add_content_browser_item_handler(ItemHandlerInterface(
        "file_txt", HelloWorldModule::StartTextEditorInstance, "Edit",
        "Edit this txt file",
        HelloWorldModule::get_path("resources/icons/edit.png")));

    this->add_content_browser_item_handler(ItemHandlerInterface(
        "infinitehq.helloworldmodule:superfile",
        HelloWorldModule::StartTextEditorInstance, "Super Edit",
        "Edit this txt file",
        HelloWorldModule::get_path("resources/icons/edit.png")));

    this->add_content_browser_item_identifier(ItemIdentifierInterface(
        HelloWorldModule::IsValidFile, "infinitehq.helloworldmodule:superfile",
        "Super file", "#553333"));
    this->add_toolbar_handler(ToolbarHandlerInterface(
        []() { HelloWorldModule::StartTextEditorInstance(""); }, "Hello window",
        "Open a hello window", "Hello/Test",
        HelloWorldModule::get_path("resources/icons/edit.png")));
    this->add_toolbar_topic_logo(
        "Hello/Test", HelloWorldModule::get_path("resources/icons/edit.png"));

    this->set_toolbar_main_logo_path(
        HelloWorldModule::get_path("resources/icons/edit.png"));
    this->set_credits_file(HelloWorldModule::get_path("CREDITS"));

    this->add_output_event(
        ModuleOutputEvent(HelloWorldModule::oe_save_all, "save_all"));
  }

  void init_ui() override {
    // CherryApp.AddFont(
    //     "JetBrainsMono",
    //     HelloWorldModule::GetPath("resources/fonts/JetBrainsMono-Regular.ttf"),
    //     40.0f);
  }

  void destroy() override {
    // Reset module
    this->reset_module();

    // Clear windows
    for (auto i :
         HelloWorldModule::get_current_context()->m_text_editor_instances) {
      CherryApp.DeleteAppWindow(i->get_app_window());
    }

    HelloWorldModule::destroy_context(ctx);
    ctx.reset();
  }
};

#ifdef _WIN32
extern "C" __declspec(dllexport) ModuleInterface *create_em() {
  return new infinitehq_textedit();
}
#else
extern "C" ModuleInterface *create_em() { return new infinitehq_textedit(); }
#endif

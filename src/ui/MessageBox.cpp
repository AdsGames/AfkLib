#include "ui/MessageBox.h"

#include <allegro5/allegro_native_dialog.h>

#include "Locator.h"

MessageBox::MessageBox(MessageBoxType type)
    : title(""), heading(""), text(""), type(type) {}

// Set the title of the message box
void MessageBox::setTitle(const std::string& title) {
  this->title = title;
}

// Set the heading of the message box
void MessageBox::setHeading(const std::string& heading) {
  this->heading = heading;
}

// Set the body text of the message box
void MessageBox::setText(const std::string& text) {
  this->text = text;
}

// Show the message box on screen
int MessageBox::show() {
  int return_code =
      al_show_native_message_box(nullptr, title.c_str(), heading.c_str(),
                                 text.c_str(), nullptr, resolveType());

  return return_code;
}

// Get type of box in allegro terms
int MessageBox::resolveType() {
  switch (type) {
    case ERROR:
      return ALLEGRO_MESSAGEBOX_ERROR;
    case QUESTION:
      return ALLEGRO_MESSAGEBOX_QUESTION;
    case OK_CANCEL:
      return ALLEGRO_MESSAGEBOX_OK_CANCEL;
    case YES_NO:
      return ALLEGRO_MESSAGEBOX_YES_NO;
    case WARN:
    default:
      return ALLEGRO_MESSAGEBOX_WARN;
  }
}
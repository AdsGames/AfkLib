/**
 * @file MessageBox.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of MessageBox
 * @version 0.1
 * @date 2020-11-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "ui/MessageBox.h"

#include <SDL2/SDL_messagebox.h>
#include "services/Services.h"

namespace afk {

MessageBox::MessageBox(MessageBoxType type) : type(type) {}

// Set the title of the message box
void MessageBox::setTitle(const std::string& title) {
  this->title = title;
}

// Set the body text of the message box
void MessageBox::setText(const std::string& text) {
  this->text = text;
}

// Show the message box on screen
int MessageBox::show() {
  SDL_Window* window = Services::getDisplayService().getWindow();
  int returnCode = SDL_ShowSimpleMessageBox(resolveType(), title.c_str(),
                                             text.c_str(), window);
  return returnCode;
}

// Get type of box in SDL terms
int MessageBox::resolveType() {
  switch (type) {
    case MessageBoxType::Error:
      return SDL_MESSAGEBOX_ERROR;
    case MessageBoxType::Info:
      return SDL_MESSAGEBOX_INFORMATION;
    case MessageBoxType::Warn:
    default:
      return SDL_MESSAGEBOX_WARNING;
  }
}

}  // namespace afk

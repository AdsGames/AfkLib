/**
 * @file AudioService.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Default audio service, can actually play audio.
 * @version 0.1
 * @date 2020-10-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_AUDIOSERVICE_H
#define AFK_AUDIOSERVICE_H

#include <string>

#include "../../assets/Sound.h"
#include "../../assets/Stream.h"

namespace afk {

/**
 * @brief Implementation of audio service
 *
 */
class AudioService {
 public:
  /**
   * @brief Destroy the Audio Service
   *
   */
  virtual ~AudioService() = default;

  /**
   * @brief Play sound by id
   *
   * @param key Id of sound to play
   * @param gain Gain from 0 to 1
   * @param pan Pan from -1 to 1
   * @param speed Speed (unused)
   * @param loop Loop mode
   */
  void playSound(const std::string& key,
                 float gain = 1.0f,
                 float pan = 0.0f,
                 float speed = 1.0f,
                 bool loop = false);

  /**
   * @brief Play audio stream by id
   *
   * @param key Id of stream to play
   * @param loop Loop mode, true for looping, false for one shot
   */
  void playStream(const std::string& key, bool loop = false);

  /**
   * @brief Stop stream by id. Stops all instances of stream currently playing.
   *
   * @param key Id of stream to stop
   */
  void stopStream(const std::string& key);
};

}  // namespace afk

#endif  // AFK_AUDIOSERVICE_H

/**
 * @example ex_sound.cpp
 * This example shows how to use basic sound features
 */

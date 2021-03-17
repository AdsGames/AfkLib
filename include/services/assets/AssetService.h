/**
 * @file AssetService.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Service for managing Sound, Texture, Font and Stream assets
 * @version 0.1
 * @date 2020-08-05
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_SERVICES_ASSETS_ASSETSERVICE_H_
#define INCLUDE_SERVICES_ASSETS_ASSETSERVICE_H_

#include <string>
#include <unordered_map>

#include "../../assets/Font.h"
#include "../../assets/Sound.h"
#include "../../assets/Stream.h"
#include "../../assets/Texture.h"

namespace afk {

/**
 * @brief Hold and manages Sound, Texture, Stream and Font assets
 *
 **/
class AssetService {
 public:
  /**
   * @brief Create a new instance of asset manager
   *
   * @todo Unload assets on delete
   */
  AssetService();

  /**
   * Destroy instance of asset manager
   * Cleans up assets upon unloading
   *
   */
  virtual ~AssetService();

  /**
   * @brief Get reference to audio by key reference
   *
   * @param key unique id of asset to find
   * @return Reference to sound if found at key
   * @throws KeyLookupException Thrown if no object can be found for `key`
   * @see loadAudio
   */
  const Sound& getAudio(const std::string& key);

  /**
   * @brief Get reference to audio by key reference
   *
   * @param key unique id of asset to find
   * @return Reference to image if found at key
   * @throws KeyLookupException Thrown if no object can be found for `key`
   * @see loadImage
   */
  const Texture& getImage(const std::string& key);

  /**
   * @brief Get reference to font by key reference
   *
   * @param key unique id of asset to find
   * @return Reference to font if found at key
   * @throws KeyLookupException Thrown if no object can be found for `key`
   * @see loadFont
   */
  const Font& getFont(const std::string& key);

  /**
   * @brief Get reference to audio stream by key reference
   *
   * @param key unique id of asset to find
   * @return Reference to stream if found at key
   * @throws KeyLookupException Thrown if no object can be found for `key`
   * @see loadStream
   */
  const Stream& getStream(const std::string& key);

  /**
   * @brief Loads an image into memory from a given path. Image is assigned to
   * provided key for lookup.
   *
   * @param key unique id to assign to image
   * @param path path to asset
   * @throws FileIOException Thrown if file can not be loaded
   * @see getImage
   */
  void loadImage(const std::string& key, const std::string& path);

  /**
   * @brief Loads an audio file into memory from a given path. Font is assigned
   * to provided key for lookup.
   *
   * @param key unique id to assign to audio file
   * @param path path to asset
   * @throws FileIOException Thrown if file can not be loaded
   * @see getAudioService
   */
  void loadAudio(const std::string& key, const std::string& path);

  /**
   * @brief Loads a font into memory from a given path. Audio file is assigned
   * to provided key for lookup.
   *
   * @param key unique id to assign to font file
   * @param path path to asset
   * @param size size of font to load in
   * @throws FileIOException Thrown if file can not be loaded
   * @see getFont
   */
  void loadFont(const std::string& key,
                const std::string& path,
                const int size);

  /**
   * @brief Loads an audio stream into memory from a given path. Stream is
   * assigned to provided key for lookup.
   *
   * @param key unique id to assign to audio stream file
   * @param path path to asset
   * @throws FileIOException Thrown if file can not be loaded
   * @see getStream
   */
  void loadStream(const std::string& key, const std::string& path);

 private:
  /// Container that stores all Sound assets
  std::unordered_map<std::string, Sound> loaded_audio;

  /// Container that stores all Image assets
  std::unordered_map<std::string, Texture> loaded_image;

  /// Container that stores all Font assets
  std::unordered_map<std::string, Font> loaded_font;

  /// Container that stores all Stream assets
  std::unordered_map<std::string, Stream> loaded_stream;
};

}  // namespace afk

#endif  // INCLUDE_SERVICES_ASSETS_ASSETSERVICE_H_

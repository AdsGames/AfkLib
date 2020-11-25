#ifndef ENGINE_SCENE_SCENE_H
#define ENGINE_SCENE_SCENE_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../Locator.h"
#include "../common/Exceptions.h"
#include "../entities/GameObject.h"

/**
 * @brief Scene for state machine
 *
 * @author Allan Legemaate
 * @date 30/12/2016
 */
class Scene {
 public:
  /**
   * @brief Destroy the Scene object
   *
   */
  virtual ~Scene(){};

  /**
   * @brief Start the scene
   *
   */
  virtual void start() = 0;

  /**
   * @brief Draw to be overridden by derived scenes
   *
   */
  virtual void draw() = 0;

  /**
   * @brief Update to be overridden by derived scenes
   *
   */
  virtual void update() = 0;

  /**
   * @brief Stop the scene
   *
   */
  virtual void stop() = 0;

  /**
   * @brief Internall cleanup call
   *
   */
  void stopInternal();

  /**
   * @brief Draw all objects hooked into scene
   *
   */
  void drawInternal();

  /**
   * @brief Update all objects hooked into scene
   *
   */
  void updateInternal();

  /**
   * @brief Add game object to update and draw pool
   *
   * @tparam T Type of game object
   * @tparam Args Arguments to forward to T
   * @param args Argument values which will be forwarded to T when constructing
   * a new game object
   * @return Unique id of created object
   */
  template <typename T, typename... Args>
  ObjId add(Args&&... args) {
    std::unique_ptr<GameObject> obj =
        std::make_unique<T>(T(std::forward<Args>(args)...));
    const int id = obj.get()->getId();
    update_pool.push_back(std::move(obj));
    sortGameObjects();
    return id;
  }

  /**
   * @brief Add game object to update and draw pool, returns by reference
   *
   * @tparam T Type of game object
   * @tparam Args Arguments to forward to T
   * @param args Argument values which will be forwarded to T when constructing
   * a new game object
   * @return Reference to created game object
   */
  template <typename T, typename... Args>
  T& addObj(Args&&... args) {
    std::unique_ptr<GameObject> obj =
        std::make_unique<T>(T(std::forward<Args>(args)...));
    const int id = obj.get()->getId();
    update_pool.push_back(std::move(obj));
    sortGameObjects();
    return get<T>(id);
  }

  /**
   * @brief Removes a game object from the scene pool
   *
   * @param id Id of object to remove
   */
  void remove(const ObjId id);

  /**
   * @brief Gets a game object by id and casts to type T
   *
   * @tparam T Type of game object
   * @param id Id of game object to look up
   * @return Reference to game object if found
   * @throws KeyLookupException if game object could not be found
   */
  template <class T>
  T& get(const ObjId id) {
    try {
      unsigned int index = lookup_map[id];
      return dynamic_cast<T&>(*update_pool.at(index));
    } catch (...) {
      throw KeyLookupException("Could not find entity by id " +
                               std::to_string(id));
    }
  }

  /**
   * @brief Register collider between two game objects
   *
   * @param obj1 Game object 1
   * @param obj2 Game object 2
   */
  void addCollider(const ObjId obj1, const ObjId obj2);

  /**
   * @brief Set the next scene to be loaded in. Upon calling, deletes this scene
   *
   * @param scene_id Id of next scene to load
   */
  static void setNextScene(const std::string& scene_id);

  /// Current scene
  static std::string scene_id;

  /// Next scene to load
  static std::string next_scene;

  /**
   * @brief Get the AudioService registered with the game
   *
   * @return Reference to the audioservice
   */
  static AudioService& getAudio();

  /**
   * @brief Get the AssetManager registered with the game
   *
   * @return Reference to the asset manager
   */
  static AssetManager& getAsset();

  /**
   * @brief Get the Window registered with the game
   *
   * @return Reference to the window
   */
  static Window& getWindow();

  /**
   * @brief Get the SettingManager registered with the game
   *
   * @return Reference to the setting manager
   */
  static SettingManager& getSettings();

  /**
   * @brief Get the Input registered with the game
   *
   * @return Reference to the input
   */
  static Input& getInput();

 private:
  /**
   * @brief Sort game object by Z index
   *
   */
  void sortGameObjects();

  /// Holds game objects
  std::vector<std::unique_ptr<GameObject>> update_pool;

  /// Quick gameobject lookup
  std::map<ObjId, unsigned int> lookup_map;

  /// Quick collider lookup
  std::map<ObjId, std::vector<ObjId>> collider_map;
};

#endif  // ENGINE_SCENE_SCENE_H

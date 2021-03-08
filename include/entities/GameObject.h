#ifndef INCLUDE_ENTITIES_GAMEOBJECT_H_
#define INCLUDE_ENTITIES_GAMEOBJECT_H_

/// Unique id type alias
using ObjId = unsigned int;

namespace afk {

// Forward declare scene class
class Scene;

/**
 * @brief A collidable object! Parent class for many others
 *
 * @author Allan Legemaate
 * @date 03/01/2017
 */
class GameObject {
 public:
  /**
   * @brief Construct a new GameObject
   *
   * @param scene Reference to scene which is stored in game object
   * @param x X position
   * @param y Y position
   * @param z Z position (for sorting)
   */
  explicit GameObject(const Scene& scene,
                      const float x = 0.0f,
                      const float y = 0.0f,
                      const int z = 0);

  /**
   * @brief Destroy the GameObject
   *
   */
  virtual ~GameObject();

  /**
   * @brief Update loop to be overriden by derived classes. Automatically called
   * by Scene.
   *
   */
  virtual void update();

  /**
   * @brief Draw loop to be overriden by derived classes. Automatically called
   * by Scene.
   *
   */
  virtual void draw();

  /**
   * @brief Checks collision between this game object and itself.
   *
   * @param other Some other game object
   * @return True on collision, else false
   */
  bool colliding(const GameObject& other);

  /**
   * @brief Callback which is triggered on collision with another game object if
   * registered with the Scene.
   *
   * @param other The game object which is being collided with.
   */
  virtual void onCollide(const GameObject& other);

  /**
   * @brief Set the size of game object in pixels
   *
   */
  void setSize(const unsigned int width, const unsigned int height);

  /**
   * @brief Set the position of game object in pixels
   *
   */
  void setPosition(const float x, const float y);

  /**
   * @brief Get the width of the game object
   *
   * @return Width of game object
   */
  int getWidth() const;

  /**
   * @brief Get the height of the game object
   *
   * @return Height of game object
   */
  int getHeight() const;

  /**
   * @brief Get x position of game object
   *
   * @return X position
   */
  float getX() const;

  /**
   * @brief Get y position of game object
   *
   * @return Y position
   */
  float getY() const;

  /**
   * @brief Get z position of game object. Used for z sorting
   *
   * @return Z position
   */
  int getZ() const;

  /**
   * @brief Definition for < operator. Less than if z is less than the other
   * game object.
   *
   * @param obj Other game object
   * @return True if the z of this game object is less than the other
   */
  bool operator<(const GameObject& obj) const { return (z < obj.getZ()); }

  /**
   * @brief Get the unique id of game object
   *
   * @return Id of this game object
   */
  ObjId getId() const;

 protected:
  /// Reference to registered scene
  const Scene& scene;

  /// X position on x y plane
  float x;

  /// Y position on x y plane
  float y;

  /// Z position, used for sorting
  int z;

  /// Height in pixels of game object
  int height;

  /// Width in pixels of game object
  int width;

 private:
  /// Autoassigned unique id
  ObjId id;

  /// Static id counter
  static ObjId index;
};
}  // namespace afk

#endif  // INCLUDE_ENTITIES_GAMEOBJECT_H_

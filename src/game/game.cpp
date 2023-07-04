// Support Code written by Michael D. Shah
// Last Updated: 2/19/21
// Please do not redistribute without asking permission.

#include "core/ControllerComponent.hpp"
#include "core/Engine.hpp"  // The main engine
#include "core/GameObject.hpp"
#include "core/ResourceManager.hpp"
#include "core/SpriteAnimator.hpp"
#include "core/SpriteRenderer.hpp"
#include "core/TilemapComponent.hpp"
#include "core/TransformComponent.hpp"
#include "core/collision/SpriteColliderComponent.hpp"
#include "core/collision/TilemapColliderComponent.hpp"
#include "core/physics/Rigidbody.hpp"
#include "core/resources/Spritesheet.hpp"

#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
    // Create an instance of an object for our engine
    Engine engine;
    // Initialize the Engine Subsystems
    engine.InitializeGraphicsSubSystem();
    engine.InitializePhysicsEngine(1.f / 60.f);
    engine.InitializeInputSystem();
    // Once all subsystems have been initialized
    // Start the engine
    engine.Startup();

    // Setup our TileMap
    // This tile map is 20x11 in our game
    // It is using a 'reference' tilemap with 8x8 tiles
    // that are each 64x64 pixels.
    GameObject& tilemapObject = engine.InstantiateGameObject();
    const char* tilemapSpritesheetLoc =
        "./assets/mspj-engine/sprites/path/path-sheet.bmp";
    ResourceManager::instance().Spritesheets()->Load(tilemapSpritesheetLoc);
    std::shared_ptr<Spritesheet> tilemapTextureAtlas =
        ResourceManager::instance().Spritesheets()->Get(tilemapSpritesheetLoc);
    tilemapTextureAtlas->SetSpriteSize({32, 32});
    // Create the tilemap component
    TilemapComponent* tilemapComponent =
        engine.InstantiateComponent<TilemapComponent>(tilemapObject,
                                                      tilemapTextureAtlas);
    tilemapComponent->SetDisplayTileSize({64, 64});
    // Generate a a simple tilemap
    tilemapComponent->GenerateMapFromFile(
        "./assets/mspj-engine/tilemaps/level01");
    (void)engine.InstantiateComponent<TilemapColliderComponent>(tilemapObject);
    (void)engine.InstantiateComponent<Physics::Rigidbody>(tilemapObject, true);

    // Note: Player must be created after the tilemap to be rendered after
    // (above) the tilemap Create our player game object, all components created
    // here are to be deleted by the Player
    GameObject& player = engine.InstantiateGameObject();
    // Prepare the controller
    ControllerComponent* controller =
        engine.InstantiateComponent<ControllerComponent>(player);
    player.GetTransform().SetPosition({-16, -16});
    // Prepare the sprite
    SpriteAnimator* sprite =
        engine.InstantiateComponent<SpriteAnimator>(player);
    const char* playerSpriteheetLoc =
        "./assets/mspj-engine/sprites/walk-cycle/"
        "character-walk-spritesheet.bmp";
    ResourceManager::instance().Spritesheets()->Load(playerSpriteheetLoc);
    std::shared_ptr<Spritesheet> characterSpritesheet =
        ResourceManager::instance().Spritesheets()->Get(playerSpriteheetLoc);
    characterSpritesheet->SetSpriteSize({32, 32});
    sprite->UseSpritesheet(characterSpritesheet);
    sprite->SetSize({32, 32});
    sprite->SetAnimation("move_down", 0, 4);
    sprite->SetAnimation("move_up", 1, 4);
    sprite->SetAnimation("move_left", 2, 4);
    sprite->SetAnimation("move_right", 3, 4);
    sprite->SetAnimation("idle", 4, 2);
    (void)engine.InstantiateComponent<SpriteColliderComponent>(player);
    (void)engine.InstantiateComponent<Physics::Rigidbody>(player, false);

    int numMushrooms = 3;
    int collectedCount = 0;

    const char* mushroomSpriteLoc =
        "./assets/mspj-engine/sprites/objects/mushroom-coin.bmp";
    ResourceManager::instance().Spritesheets()->Load(mushroomSpriteLoc);
    std::shared_ptr<Spritesheet> mushroomSpritesheet =
        ResourceManager::instance().Spritesheets()->Get(mushroomSpriteLoc);

    GameObject& mushroom = engine.InstantiateGameObject();
    SpriteRenderer* mushroomSprite =
        engine.InstantiateComponent<SpriteRenderer>(mushroom);
    mushroomSprite->UseSpritesheet(mushroomSpritesheet);
    mushroomSprite->SetSize({32, 32});
    ColliderComponent* mushroomCollider =
        engine.InstantiateComponent<SpriteColliderComponent>(mushroom);
    mushroomCollider->SetIsTrigger(true);
    mushroom.GetTransform().SetPosition({144, 128});

    // An artifact of original engine that used python for scripting.
    /*
    engine.InstantiateBehaviorComponent(mushroom, "collectable",
      [](PythonComponent* _pyComp, UpdateContext* _updateCtx) { },
      [numMushrooms, &collectedCount](PythonComponent* component, const
    std::string& message) { if (message != "trigger_collided") return; std::cout
    << "You collected a mushroom!" << std::endl; GameObject& gameObj =
    component->GetGameObject(); gameObj.SetActive(false);

        collectedCount++;
        if (collectedCount == numMushrooms) std::cout << "You won the game!" <<
    std::endl;
      });
    */

    // Run our program forever
    engine.RunGameLoop();
    // Explicitly call Shutdown to terminate our engine
    engine.Shutdown();
    // When our program ends, it will exit scope,
    // the destructor will then be called
    // and clean up the program.
    return 0;
}

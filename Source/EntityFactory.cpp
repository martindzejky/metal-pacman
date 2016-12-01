#include "EntityFactory.hpp"

#include "TransformComponent.hpp"
#include "ModelComponent.hpp"
#include "CameraComponent.hpp"
#include "CameraControlComponent.hpp"
#include "PacmanAnimationComponent.hpp"
#include "LightComponent.hpp"
#include "MonsterArmAnimationComponent.hpp"
#include "RotatingComponent.hpp"
#include "PlayerMoveComponent.hpp"
#include "ColliderComponent.hpp"
#include "MonsterAIComponent.hpp"
#include "CollectibleComponent.hpp"
#include "CollectorComponent.hpp"
#include "DestroyOnDetachComponent.hpp"
#include "SurrenderAnimationComponent.hpp"
#include "VictoryAnimationComponent.hpp"


std::shared_ptr<Entity> EntityFactory::CreatePlayer(float x, float y, float z) {
    // root
    auto root = Entity::Create();
    auto rootTransform = std::make_shared<TransformComponent>(x, y, z);
    root->AttachComponent(rootTransform);
    root->AttachComponent(std::make_shared<PlayerMoveComponent>());
    root->AttachComponent(std::make_shared<CollectorComponent>());
    root->AttachComponent(std::make_shared<ColliderComponent>(.44f, 2, .44f, ColliderComponent::Group::Player));

    // camera
    auto cameraPivot = Entity::Create();
    auto cameraPivotTransform = std::make_shared<TransformComponent>(0, 1.6, 0);
    cameraPivotTransform->Pitch(-.8f);
    cameraPivotTransform->Attach(rootTransform);
    cameraPivot->AttachComponent(cameraPivotTransform);
    cameraPivot->AttachComponent(std::make_shared<CameraControlComponent>());

    auto camera = Entity::Create();
    auto cameraTransform = std::make_shared<TransformComponent>(0, 0, 5.f);
    cameraTransform->Attach(cameraPivotTransform);
    camera->AttachComponent(cameraTransform);
    camera->AttachComponent(std::make_shared<CameraComponent>());

    // model
    auto bottom = Entity::Create();
    auto bottomTransform = std::make_shared<TransformComponent>();
    bottomTransform->Pitch(-3.14f / 2.f);
    bottomTransform->Attach(rootTransform);
    bottom->AttachComponent(bottomTransform);
    bottom->AttachComponent(
        std::make_shared<ModelComponent>("PacmanBottomModel", "YellowMetalDiffuseTexture", "YellowMetalNormalTexture",
                                         "YellowMetalReflectionTexture"));

    auto teethBottom = Entity::Create();
    auto teethBottomTransform = std::make_shared<TransformComponent>();
    teethBottomTransform->Pitch(-3.14f / 2.f);
    teethBottomTransform->Attach(rootTransform);
    teethBottom->AttachComponent(teethBottomTransform);
    teethBottom->AttachComponent(
        std::make_shared<ModelComponent>("PacmanTeethBottomModel", "RustDiffuseTexture", "RustNormalTexture",
                                         "RustReflectionTexture"));

    auto teethTop = Entity::Create();
    auto teethTopTransform = std::make_shared<TransformComponent>();
    teethTopTransform->Pitch(-3.14f / 2.f);
    teethTopTransform->Attach(rootTransform);
    teethTop->AttachComponent(teethTopTransform);
    teethTop->AttachComponent(
        std::make_shared<ModelComponent>("PacmanTeethTopModel", "RustDiffuseTexture", "RustNormalTexture",
                                         "RustReflectionTexture"));
    teethTop->AttachComponent(std::make_shared<PacmanAnimationComponent>());

    auto top = Entity::Create();
    auto topTransform = std::make_shared<TransformComponent>();
    topTransform->Pitch(-3.14f / 2.f);
    topTransform->Attach(rootTransform);
    top->AttachComponent(topTransform);
    top->AttachComponent(
        std::make_shared<ModelComponent>("PacmanTopModel", "YellowMetalDiffuseTexture", "YellowMetalNormalTexture",
                                         "YellowMetalReflectionTexture"));
    top->AttachComponent(std::make_shared<PacmanAnimationComponent>());

    auto eyes = Entity::Create();
    auto eyesTransform = std::make_shared<TransformComponent>();
    eyesTransform->Pitch(-3.14f / 2.f);
    eyesTransform->Attach(rootTransform);
    eyes->AttachComponent(eyesTransform);
    eyes->AttachComponent(
        std::make_shared<ModelComponent>("PacmanEyesModel", "RedMetalDiffuseTexture", "RedMetalNormalTexture",
                                         "RedMetalReflectionTexture", 2));
    eyes->AttachComponent(std::make_shared<PacmanAnimationComponent>());

    // victory
    root->AttachComponent(std::make_shared<VictoryAnimationComponent>(camera, cameraPivot, top, teethTop, eyes));

    return root;
}

std::shared_ptr<Entity> EntityFactory::CreateMonster(float x, float y, float z) {
    // root
    auto root = Entity::Create();
    auto rootTransform = std::make_shared<TransformComponent>(x, y, z);
    root->AttachComponent(rootTransform);
    root->AttachComponent(std::make_shared<MonsterAIComponent>());
    root->AttachComponent(std::make_shared<ColliderComponent>(.44f, 2, .44f, ColliderComponent::Group::Enemy));

    // model
    auto body = Entity::Create();
    auto bodyTransform = std::make_shared<TransformComponent>();
    bodyTransform->Pitch(-3.14f / 2.f);
    bodyTransform->Attach(rootTransform);
    body->AttachComponent(bodyTransform);
    body->AttachComponent(
        std::make_shared<ModelComponent>("MonsterBodyModel", "BlueMetalDiffuseTexture", "BlueMetalNormalTexture",
                                         "BlueMetalReflectionTexture"));

    auto eyes = Entity::Create();
    auto eyesTransform = std::make_shared<TransformComponent>();
    eyesTransform->Pitch(-3.14f / 2.f);
    eyesTransform->Attach(rootTransform);
    eyes->AttachComponent(eyesTransform);
    eyes->AttachComponent(
        std::make_shared<ModelComponent>("MonsterEyesModel", "YellowMetalDiffuseTexture", "YellowMetalNormalTexture",
                                         "YellowMetalReflectionTexture", 2));

    auto teeth = Entity::Create();
    auto teethTransform = std::make_shared<TransformComponent>();
    teethTransform->Pitch(-3.14f / 2.f);
    teethTransform->Attach(rootTransform);
    teeth->AttachComponent(teethTransform);
    teeth->AttachComponent(
        std::make_shared<ModelComponent>("MonsterTeethModel", "RustDiffuseTexture", "RustNormalTexture",
                                         "RustReflectionTexture"));

    // arms
    auto rightArmOrigin = Entity::Create();
    auto rightArmOriginTransform = std::make_shared<TransformComponent>(-.47f, .5f, 0);
    rightArmOriginTransform->Yaw(-3.14f / 2.f);
    rightArmOriginTransform->Roll(3.14f / 2.f);
    rightArmOriginTransform->Attach(rootTransform);
    rightArmOrigin->AttachComponent(rightArmOriginTransform);

    auto rightArm = Entity::Create();
    auto rightArmTransform = std::make_shared<TransformComponent>();
    rightArmTransform->Attach(rightArmOriginTransform);
    rightArm->AttachComponent(rightArmTransform);
    rightArm->AttachComponent(
        std::make_shared<ModelComponent>("MonsterArmModel", "GrayMetalDiffuseTexture", "GrayMetalNormalTexture",
                                         "GrayMetalReflectionTexture"));
    rightArm->AttachComponent(std::make_shared<MonsterArmAnimationComponent>());

    auto leftArmOrigin = Entity::Create();
    auto leftArmOriginTransform = std::make_shared<TransformComponent>(.46f, .51f, 0);
    leftArmOriginTransform->Yaw(3.14f / 2.f);
    leftArmOriginTransform->Roll(-3.14f / 2.f);
    leftArmOriginTransform->Attach(rootTransform);
    leftArmOrigin->AttachComponent(leftArmOriginTransform);

    auto leftArm = Entity::Create();
    auto leftArmTransform = std::make_shared<TransformComponent>();
    leftArmTransform->Attach(leftArmOriginTransform);
    leftArm->AttachComponent(leftArmTransform);
    leftArm->AttachComponent(
        std::make_shared<ModelComponent>("MonsterArmModel", "GrayMetalDiffuseTexture", "GrayMetalNormalTexture",
                                         "GrayMetalReflectionTexture"));
    leftArm->AttachComponent(std::make_shared<MonsterArmAnimationComponent>());

    // surrender
    root->AttachComponent(std::make_shared<SurrenderAnimationComponent>(leftArm, rightArm));

    return root;
}

std::shared_ptr<Entity> EntityFactory::CreateFloor(float x, float y, float z) {
    // root
    auto root = Entity::Create();
    auto rootTransform = std::make_shared<TransformComponent>(x, y, z);
    root->AttachComponent(rootTransform);

    // model
    auto model = Entity::Create();
    auto modelTransform = std::make_shared<TransformComponent>();
    modelTransform->Pitch(-3.14f / 2.f);
    modelTransform->Attach(rootTransform);
    model->AttachComponent(modelTransform);
    model->AttachComponent(
        std::make_shared<ModelComponent>("FloorModel", "GrayMetalDiffuseTexture", "GrayMetalNormalTexture",
                                         "GrayMetalReflectionTexture"));

    return root;
}

std::shared_ptr<Entity> EntityFactory::CreateWall(int variant, float x, float y, float z) {
    // root
    auto root = Entity::Create();
    auto rootTransform = std::make_shared<TransformComponent>(x, y, z);
    root->AttachComponent(rootTransform);
    root->AttachComponent(std::make_shared<ColliderComponent>(.5f, 1, .5f, ColliderComponent::Group::Solid));

    // model
    std::string modelName;
    switch (variant) {
        default:
            modelName = "Wall1Model";
            break;

        case 2:
            modelName = "Wall2Model";
            break;

        case 3:
            modelName = "Wall3Model";
            break;
    }

    auto model = Entity::Create();
    auto modelTransform = std::make_shared<TransformComponent>();
    modelTransform->Pitch(-3.14f / 2.f);
    modelTransform->Attach(rootTransform);
    model->AttachComponent(modelTransform);
    model->AttachComponent(
        std::make_shared<ModelComponent>(modelName, "GrayMetalDiffuseTexture", "GrayMetalNormalTexture",
                                         "GrayMetalReflectionTexture"));

    return root;
}

std::shared_ptr<Entity> EntityFactory::CreateLight(int x, int y, int z, float r, float g, float b, float radius) {
    auto light = Entity::Create();
    auto lightTransform = std::make_shared<TransformComponent>(x, y, z);
    light->AttachComponent(lightTransform);
    light->AttachComponent(std::make_shared<LightComponent>(r, g, b, radius));

    return light;
}

std::shared_ptr<Entity> EntityFactory::CreateSpikes(float x, float y, float z) {
    // root
    auto root = Entity::Create();
    auto rootTransform = std::make_shared<TransformComponent>(x, y, z);
    root->AttachComponent(rootTransform);
    root->AttachComponent(std::make_shared<ColliderComponent>(.45f, 1, .45f, ColliderComponent::Group::FakeSolid));

    // model
    auto model = Entity::Create();
    auto modelTransform = std::make_shared<TransformComponent>();
    modelTransform->Pitch(-3.14f / 2.f);
    modelTransform->Attach(rootTransform);
    model->AttachComponent(modelTransform);
    model->AttachComponent(
        std::make_shared<ModelComponent>("SpikesModel", "BlackMetalDiffuseTexture", "BlackMetalNormalTexture",
                                         "BlackMetalReflectionTexture"));

    return root;
}

std::shared_ptr<Entity> EntityFactory::CreateBolt(float x, float y, float z) {
    // root
    auto root = Entity::Create();
    auto rootTransform = std::make_shared<TransformComponent>(x, y, z);
    root->AttachComponent(rootTransform);
    root->AttachComponent(std::make_shared<ColliderComponent>(.2f, 1, .2f, ColliderComponent::Group::Collectible));
    root->AttachComponent(std::make_shared<CollectibleComponent>());

    // pivot
    auto pivot = Entity::Create();
    auto pivotTransform = std::make_shared<TransformComponent>();
    pivotTransform->Attach(rootTransform);
    pivot->AttachComponent(pivotTransform);
    pivot->AttachComponent(std::make_shared<RotatingComponent>(Transform::Axis::Z, (dist(re) % 1000) / (float) 125 - 4));
    root->AttachComponent(std::make_shared<DestroyOnDetachComponent>(pivot->GetId()));


    // model
    auto model = Entity::Create();
    auto modelTransform = std::make_shared<TransformComponent>();
    modelTransform->Pitch(-3.14f / 2.f);
    modelTransform->Attach(pivotTransform);
    model->AttachComponent(modelTransform);
    model->AttachComponent(
        std::make_shared<ModelComponent>("BoltModel", "RedMetalDiffuseTexture", "RedMetalNormalTexture",
                                         "RedMetalReflectionTexture"));
    model->AttachComponent(std::make_shared<RotatingComponent>(Transform::Axis::X, (dist(re) % 1000) / (float) 125 - 4));
    pivot->AttachComponent(std::make_shared<DestroyOnDetachComponent>(model->GetId()));

    return root;
}

std::shared_ptr<Entity> EntityFactory::CreateHint(float x, float y, float z) {
    auto root = Entity::Create();
    auto rootTransform = std::make_shared<TransformComponent>(x, y, z);
    root->AttachComponent(rootTransform);
    root->AttachComponent(std::make_shared<ColliderComponent>(.5f, 1, .5f, ColliderComponent::Group::Hint));

    return root;
}

std::default_random_engine EntityFactory::re;
std::uniform_int_distribution<int> EntityFactory::dist;

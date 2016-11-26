#include "EntityFactory.hpp"

#include "TransformComponent.hpp"
#include "ModelComponent.hpp"
#include "CameraComponent.hpp"
#include "CameraControlComponent.hpp"
#include "PacmanAnimationComponent.hpp"
#include "LightComponent.hpp"
#include "MonsterArmAnimationComponent.hpp"


std::shared_ptr<Entity> EntityFactory::CreatePlayer(float x, float y, float z) {
    // root
    auto root = Entity::Create();
    auto rootTransform = std::make_shared<TransformComponent>(x, y, z);
    root->AttachComponent(rootTransform);

    // camera
    auto cameraPivot = Entity::Create();
    auto cameraPivotTransform = std::make_shared<TransformComponent>(0, .6f, 0);
    cameraPivotTransform->Attach(rootTransform);
    cameraPivot->AttachComponent(cameraPivotTransform);
    cameraPivot->AttachComponent(std::make_shared<CameraControlComponent>());

    auto camera = Entity::Create();
    auto cameraTransform = std::make_shared<TransformComponent>(0, 0, 6.f);
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

    return root;
}

std::shared_ptr<Entity> EntityFactory::CreateMonster(float x, float y, float z) {
    // root
    auto root = Entity::Create();
    auto rootTransform = std::make_shared<TransformComponent>(x, y, z);
    root->AttachComponent(rootTransform);

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
    rightArmOriginTransform->Attach(rootTransform);
    rightArmOrigin->AttachComponent(rightArmOriginTransform);

    auto rightArm = Entity::Create();
    auto rightArmTransform = std::make_shared<TransformComponent>();
    rightArmTransform->Yaw(-3.14f / 2.f);
    rightArmTransform->Roll(3.14f / 2.f);
    rightArmTransform->Attach(rightArmOriginTransform);
    rightArm->AttachComponent(rightArmTransform);
    rightArm->AttachComponent(
        std::make_shared<ModelComponent>("MonsterArmModel", "GrayMetalDiffuseTexture", "GrayMetalNormalTexture",
                                         "GrayMetalReflectionTexture"));
    rightArm->AttachComponent(std::make_shared<MonsterArmAnimationComponent>());

    auto leftArmOrigin = Entity::Create();
    auto leftArmOriginTransform = std::make_shared<TransformComponent>(.46f, .51f, 0);
    leftArmOriginTransform->Attach(rootTransform);
    leftArmOrigin->AttachComponent(leftArmOriginTransform);

    auto leftArm = Entity::Create();
    auto leftArmTransform = std::make_shared<TransformComponent>();
    leftArmTransform->Yaw(3.14f / 2.f);
    leftArmTransform->Roll(-3.14f / 2.f);
    leftArmTransform->Attach(leftArmOriginTransform);
    leftArm->AttachComponent(leftArmTransform);
    leftArm->AttachComponent(
        std::make_shared<ModelComponent>("MonsterArmModel", "GrayMetalDiffuseTexture", "GrayMetalNormalTexture",
                                         "GrayMetalReflectionTexture"));
    leftArm->AttachComponent(std::make_shared<MonsterArmAnimationComponent>());

    return root;
}

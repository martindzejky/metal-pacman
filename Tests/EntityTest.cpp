#include "EntityTest.hpp"


void EntityTest::SetUp() {
    mEntity = Entity::Create();
}

void ComponentMock::OnAttach(std::weak_ptr<Entity> entity) {
    Component::OnAttach(entity);
    mAttachCalled = true;
}

void ComponentMock::OnDetach() {
    Component::OnDetach();
    mDetachCalled = true;
}

std::string ComponentMock::GetType() const {
    return "ComponentMock";
}

bool ComponentMock::AttachCalled() const {
    return mAttachCalled;

}

bool ComponentMock::DetachCalled() const {
    return mDetachCalled;
}


TEST_F(EntityTest, Create) {
    EXPECT_NE(mEntity->GetId(), Entity::Invalid) << "Entity with invalid ID";
}


TEST_F(EntityTest, Get) {
    EXPECT_EQ(Entity::Get(mEntity->GetId()), mEntity) << "Entity not retrievable";
}


TEST_F(EntityTest, Destroy) {
    Entity::Destroy(mEntity->GetId());

    EXPECT_NE(Entity::Get(mEntity->GetId()), mEntity) << "Entity not destroyed";
}


TEST_F(EntityTest, Component) {
    std::shared_ptr<Component> component = std::make_shared<ComponentMock>();

    EXPECT_EQ(component->GetType(), "ComponentMock") << "Wrong component type";
    EXPECT_FALSE(component->IsAttached()) << "Component create as attached";
    EXPECT_FALSE(((ComponentMock*) component.get())->AttachCalled()) << "Wrong ComponentMock initialization";
    EXPECT_FALSE(((ComponentMock*) component.get())->DetachCalled()) << "Wrong ComponentMock initialization";

    mEntity->AttachComponent(component);

    EXPECT_TRUE(((ComponentMock*) component.get())->AttachCalled()) << "Component's OnAttached not called";
    EXPECT_EQ(mEntity->GetComponent(component->GetType()), component) << "Component not attached";

    mEntity->DetachComponent(component->GetType());

    EXPECT_TRUE(((ComponentMock*) component.get())->DetachCalled()) << "Component's OnDetached not called";
    EXPECT_NE(mEntity->GetComponent(component->GetType()), component) << "Component not detached";

    mEntity->AttachComponent(component);
    mEntity->DetachAllComponents();

    EXPECT_NE(mEntity->GetComponent(component->GetType()), component) << "Component not detached";
}

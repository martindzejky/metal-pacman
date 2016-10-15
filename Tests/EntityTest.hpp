#pragma once

#include <gtest/gtest.h>

#include "../Source/Entity.hpp"
#include "../Source/Component.hpp"


class EntityTest : public testing::Test {

public:

    virtual void SetUp() override;

    std::shared_ptr<Entity> mEntity;

};


class ComponentMock : public Component {

public:

    virtual void OnAttach(std::weak_ptr<Entity> entity) override;
    virtual void OnDetach() override;

    virtual std::string GetType() const override;
    bool AttachCalled() const;
    bool DetachCalled() const;


private:

    bool mAttachCalled = false;
    bool mDetachCalled = false;

};

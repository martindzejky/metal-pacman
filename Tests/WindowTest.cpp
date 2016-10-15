#include <GL/glew.h>
#include <gtest/gtest.h>

#include "../Source/Error.hpp"
#include "../Source/Window.hpp"


TEST(WindowTest, CreateHidden) {
    auto window = Window::CreateHidden();

    EXPECT_TRUE(window) << "Window is not created";
    EXPECT_FALSE(Window::GetSingleton()) << "Hidden window set as the singleton";
}


TEST(WindowTest, CreateAndDestroy) {
    auto window = Window::Create(400, 300, "");

    EXPECT_TRUE(window) << "Window is not created";
    EXPECT_TRUE(Window::GetSingleton()) << "Singleton not set";

    Window::Destroy();

    EXPECT_FALSE(Window::GetSingleton()) << "Singleton not destroyed";
}


TEST(WindowTest, DoubleCreate) {
    Window::Create(400, 300, "");

    EXPECT_THROW(Window::Create(200, 200, ""), Error) << "Allowed to create 2 windows";

    Window::Destroy();
}


TEST(WindowTest, Close) {
    auto window = Window::CreateHidden();

    EXPECT_FALSE(window->IsClosed()) << "Window not open";
    window->Close();
    EXPECT_TRUE(window->IsClosed()) << "Window not closed";
}

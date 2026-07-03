#include <Reef/Platform/EntryPoint.hpp>

#include <Reef/Platform/Application.hpp>

#include <Reef/Core/Entity.hpp>

#include <Reef/Component/CameraComponent.hpp>
#include <Reef/Component/MeshComponent.hpp>

//class CameraController : public Reef::SubclassOf<CameraController, Reef::ScriptableComponent>
//{
//public:
//
//	void onComponentCreated()
//	{
//		mPreviousCursorPos = engine().input().getCursorPosition();
//	}
//
//
//	void onFrameUpdate(const Reef::FrameTime& frameTime)
//	{
//		auto cursorPos = engine().input().getCursorPosition();
//		auto cursorDelta = glm::vec2(mPreviousCursorPos - cursorPos) / glm::vec2(engine().viewport().resolution);
//		mPreviousCursorPos = cursorPos;
//
//		auto& transform = owner().transform();
//
//
//		glm::vec3 velocity(0.f, 0.f, 0.f);
//
//		if (engine().input().getKeyState(Reef::Key::W) == Reef::KeyState::PRESSED)
//		{
//			velocity += transform.forward();
//		}
//
//		if (engine().input().getKeyState(Reef::Key::S) == Reef::KeyState::PRESSED)
//		{
//			velocity -= transform.forward();
//		}
//
//		if (engine().input().getKeyState(Reef::Key::A) == Reef::KeyState::PRESSED)
//		{
//			velocity -= transform.right();
//		}
//
//		if (engine().input().getKeyState(Reef::Key::D) == Reef::KeyState::PRESSED)
//		{
//			velocity += transform.right();
//		}
//		
//		float l = glm::length(velocity);
//
//		if (l > 0)
//		{
//			mVelocity = (velocity / l) * MoveSpeed;
//		}
//		else
//		{
//			mVelocity *= 0.9f;
//
//			if (glm::length(mVelocity) <= glm::epsilon<float>())
//			{
//				mVelocity = { 0.f, 0.f, 0.f };
//			}
//		}
//
//		transform.setWorldPosition(transform.worldPosition() + mVelocity * static_cast<float>(frameTime.deltaTime));
//
//		if (engine().input().getMouseButtonState(Reef::MouseButton::RIGHT) == Reef::KeyState::PRESSED)
//		{
//			mYaw   = std::fmod(mYaw + cursorDelta.x * glm::two_pi<float>(), 360.f);
//			mPitch = std::clamp(mPitch + cursorDelta.y * glm::pi<float>(), -85.f, 85.f);
//
//			auto q1 = glm::quat(glm::vec3(mPitch,mYaw, 0));
//			
//			transform.setWorldRotation(q1);
//		}
//	}
//
//	float RotationSpeed = 90.f;
//
//	float MoveSpeed = 5.f;
//
//private:
//
//	Reef::CameraComponent* mCameraComponent{ nullptr };
//
//	glm::ivec2 mPreviousCursorPos;
//
//	glm::vec3 mVelocity{ 0.f, 0.f, 0.f };
//
//	float mYaw{ 0 };
//	float mPitch{ 0 };
//};


void
Reef::onApplicationCreated(Reef::Application& application)
{
    class AppController : public Reef::UserData
    {
    public:

        AppController(Reef::Application& application)
            : mApplication(application)
            , mWindow(application.windowManager().createWindow("Reef Engine", 1280, 720, false, true))
        {
            mWindowEventHandle = mWindow->onWindowEvent().subscribe([&](WindowEvent event)
            {
                if (event == WindowEvent::CLOSED)
                {
                    application.quit(Reef::ReturnCode::SUCCESS);
                }
            });

            auto scene = application.sceneManager().createScene();
            scene->setView(mWindow);

            auto entity = scene->createEntity();
            auto camera = entity->addComponent<Reef::CameraComponent>();

            auto meshEntity    = scene->createEntity();
            auto meshComponent = entity->addComponent<Reef::MeshComponent>();
            auto mesh          = Mesh::Cube();
            meshComponent->setMesh(mesh);
        }

    private:

        Reef::Application& mApplication;
        Reef::Window* mWindow;
        Reef::EventHandle mWindowEventHandle;

    }; // class AppController

    application.addUserData(std::make_shared<AppController>(application));
}

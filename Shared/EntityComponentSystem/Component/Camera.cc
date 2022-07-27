#include <Shared/EntityComponentSystem/Component/Camera.hh>

#include <Shared/Coder/Reader.hh>
#include <Shared/Coder/Writer.hh>

namespace shared::ecs::component
{
    Camera::Camera(uint32_t ownerId)
        : ownerId(ownerId),
          updated(true)
    {
    }

    void Camera::WriteBinary(Writer &writer)
    {
    }

    void Camera::ReadBinary(Reader &reader)
    {
    }
}

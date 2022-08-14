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

    void Camera::Tick()
    {
    }

    DEFINE_COMPONENT_FIELD(float, Camera, x)
    DEFINE_COMPONENT_FIELD(float, Camera, y)
    DEFINE_COMPONENT_FIELD(float, Camera, fov)
    DEFINE_COMPONENT_FIELD(uint32_t, Camera, child)

    void Camera::WriteBinary(Writer &writer)
    {
        writer.Float(x);
        writer.Float(y);
        writer.Float(fov);
        writer.Vu(child);
    }

    void Camera::ReadBinary(Reader &reader)
    {
        x = reader.Float();
        y = reader.Float();
        fov = reader.Float();
        child = reader.Vu();
    }
}

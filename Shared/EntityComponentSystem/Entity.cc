#include <Shared/EntityComponentSystem/Entity.hh>

#include <Shared/Coder/Writer.hh>
#include <Shared/Coder/Reader.hh>

namespace shared::ecs
{
	Entity::Entity()
	{
	}

	void Entity::Reset()
	{
		if (camera)
			camera->updated = false;
		if (physics)
			physics->updated = false;
	}

	// used for both creations and updates
	void Entity::WriteBinary(Writer &writer)
	{
		uint32_t componentFlags = 0;

		componentFlags |= ((bool)camera && camera->updated) << component::Camera::ID;
		componentFlags |= ((bool)physics && physics->updated) << component::Physics::ID;

		writer.Vu(componentFlags);

		if (camera && camera->updated)
			camera->WriteBinary(writer);
		if (physics && physics->updated)
			physics->WriteBinary(writer);
	}

	void Entity::ReadBinary(Reader &reader, bool created)
	{
		uint32_t componentFlags = reader.Vu();

		if (componentFlags & (1 << component::Camera::ID))
		{
			if (created)
				camera.emplace(id);
			camera->ReadBinary(reader);
		}
		if (componentFlags & (1 << component::Physics::ID))
		{
			if (created)
				physics.emplace(id);
			physics->ReadBinary(reader);
		}
	}
}

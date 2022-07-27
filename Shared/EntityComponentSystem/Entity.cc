#include <Shared/EntityComponentSystem/Entity.hh>

#include <Shared/Coder/Writer.hh>
#include <Shared/Coder/Reader.hh>

namespace shared::ecs
{
	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
		if (Has<component::Camera>())
			delete &Get<component::Camera>();
		if (Has<component::Physics>())
			delete &Get<component::Physics>();
	}

	void Entity::Reset()
	{
		if (Has<component::Camera>())
			Get<component::Camera>().updated = false;
		if (Has<component::Physics>())
			Get<component::Physics>().updated = false;
	}

	void Entity::WriteComponents(Writer &writer)
	{
		if (Has<component::Camera>() && Get<component::Camera>().updated)
			Get<component::Camera>().WriteBinary(writer);
		if (Has<component::Physics>() && Get<component::Physics>().updated)
			Get<component::Physics>().WriteBinary(writer);
	}

	void Entity::WriteBinaryCreation(Writer &writer)
	{
		uint32_t componentFlags = 0;

		componentFlags |= (Has<component::Camera>() && Get<component::Camera>().updated) << component::Camera::ID;
		componentFlags |= (Has<component::Physics>() && Get<component::Physics>().updated) << component::Physics::ID;

		writer.Vu(componentFlags);

		WriteComponents(writer);
	}

	void Entity::WriteBinaryUpdate(Writer &writer)
	{
		WriteComponents(writer);
	}

	void Entity::ReadComponents(Reader &reader)
	{
		if (Has<component::Camera>())
			Get<component::Camera>().ReadBinary(reader);
		if (Has<component::Physics>())
			Get<component::Physics>().ReadBinary(reader);
	}

	void Entity::ReadBinaryCreation(Reader &reader)
	{
		uint32_t componentFlags = reader.Vu();
		if (componentFlags & (1 << component::Camera::ID))
			Append<component::Camera>();
		if (componentFlags & (1 << component::Physics::ID))
			Append<component::Physics>();

		ReadComponents(reader);
	}

	void Entity::ReadBinaryUpdate(Reader &reader)
	{
		ReadComponents(reader);
	}
}

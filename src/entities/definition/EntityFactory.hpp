#pragma once

#include "../bases/BaseEntity.hpp"
#include "../../utils/Concepts.hpp"

namespace entities {

	class BaseEntity;

	namespace definition {
		class EntityDB;


		struct IEntityFactory {
			virtual BaseEntity* create() const = 0;
		};


		template<Extends<BaseEntity> T>
		struct EntityFactory : public IEntityFactory {
			EntityFactory(const char* classname) {
				extern void register_entity_factory(const IEntityFactory& factory, const char* classname);
				register_entity_factory(*this, classname);
			}

			BaseEntity* create() const override {
				return new T();
			}
		};
	}

} // entities
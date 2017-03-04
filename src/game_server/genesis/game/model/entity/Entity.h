#ifndef GENESIS_GAME_MODEL_ENTITY_ENTITY_H
#define GENESIS_GAME_MODEL_ENTITY_ENTITY_H

namespace Genesis::Game::Model::Entity {
	class Entity {

		public:

			Entity(unsigned int index) : index(index) {}

			unsigned int get_index() const {
				return this->index;
			}

		private:
			unsigned int index;
			
	};
}
#endif
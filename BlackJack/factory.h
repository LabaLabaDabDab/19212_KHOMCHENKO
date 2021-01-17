#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <string>

template<class ID , class Creator>
class Factory {
	std::map < ID, Creator > creators;
public:
	Creator createStrategyByID(const ID & id) {
		auto it = creators.find(id);
		if (creators.end() == it) {
			return nullptr;
		}
		return it->second;
	}

	bool regStrategy(const ID & id, const Creator & creator) {
		Creator s = createStrategyByID(id);
		if (s == nullptr) {
			creators[id] = creator;
			return true;
		}
		return false;
	}

	static Factory * getInstance() {
		static Factory f;
		return &f;
	}
private:
	Factory() = default;
	Factory(const Factory &) = delete;
	Factory & operator=(const Factory &) = delete;

};
#endif
#ifndef FACTORY_H_
#define FACTORY_H_

#include <unordered_map>

template<class Divider, class Parent>
class Creator{
public:
    static Parent *create(){
        return (new Divider);
    }
};

template<class Product, class Creator, class ID>
class Factory {
public:
    Factory() {};

    static Factory* get_instance() {
        static Factory f;
        return &f;
    }

    bool register_strat(const ID& id, Creator creator) {
        creators.insert({id, creator});
        return isRegistered(id);
    }

    bool isRegistered(const ID& id){
        if(creators.find(id) == creators.end())
            return false;
        return true;
    }

    Product* create(const ID& id) {
        return creators[id]();
    }

    ~Factory(){}
private:
    std::unordered_map<ID, Creator> creators;
};

#endif

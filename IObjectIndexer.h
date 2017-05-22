//
// Created by merlinvn@gmail.com on 29/12/16.
//

#ifndef MODERNCPP_OBJECTINDEXER_H
#define MODERNCPP_OBJECTINDEXER_H

#include <vector>
#include <iostream>
#include <memory>

template<typename T, typename P>
class IObjectIndexer {

    virtual void add(T &object) =0;

    virtual void remove(T &object) =0;

    virtual void size() =0;

    virtual void update() =0;

    virtual void notify_change(T &object, const P &property, int oldValue, int newValue) = 0;
};


template<typename T, size_t dimension>
struct multidimensional_vector {
    using type = std::vector<typename multidimensional_vector<T, dimension - 1>::type>;
    using value_type = typename multidimensional_vector<T, dimension - 1>::type;


    static type create(std::initializer_list<int>::iterator it) {
        type object;
        object.assign(*it, multidimensional_vector<T, dimension - 1>::create(it + 1));
        return object;
    }

    template<typename Prop>
    static void add(const size_t &id, type &container, const std::vector<Prop> &v, int pos, T &object) {
        multidimensional_vector<T, dimension - 1>::add(id, container[object->getPropertyValue(v[pos])], v, pos + 1,
                                                       object);
    }

    template<typename Prop>
    static void remove(const size_t &id, type &container, const std::vector<Prop> &v, int pos, T &object) {
        multidimensional_vector<T, dimension - 1>::remove(id, container[object->getPropertyValue(v[pos])], v, pos + 1,
                                                          object);
    }
};

template<typename T>
struct multidimensional_vector<T, 2> {
    using type = std::vector<typename multidimensional_vector<T, 1>::type>;
    using value_type = typename multidimensional_vector<T, 1>::type;


    static type create(std::initializer_list<int>::iterator it) {
        type object;
        object.assign(*it, value_type());
        return object;
    }

    template<typename Prop>
    static void add(const size_t &id, type &container, const std::vector<Prop> &v, int pos, T &object) {
        multidimensional_vector<T, 1>::add(id, container[object->getPropertyValue(v[pos])], v, pos + 1, object);
    }

    template<typename Prop>
    static void remove(const size_t &id, type &container, const std::vector<Prop> &v, int pos, T &object) {
        multidimensional_vector<T, 1>::remove(id, container[object->getPropertyValue(v[pos])], v, pos + 1, object);
    }
};


template<typename T>
struct multidimensional_vector<T, 1> {
    using type = std::vector<typename multidimensional_vector<T, 0>::type>;
    using value_type = typename multidimensional_vector<T, 0>::type;

    template<typename Prop>
    static void add(const size_t &id, type &container, const std::vector<Prop> &v, int pos, T &object) {
        object->setPositionInDeepestNestedVector(container.size(), id);
        container.push_back(object);
    }

    template<typename Prop>
    static void remove(const size_t &id, type &container, const std::vector<Prop> &v, int pos, T &object) {
        size_t index = object->getPositionInDeepestNestedVector(id);
        container.back()->setPositionInDeepestNestedVector(index, id);
//        object->setPositionInDeepestNestedVector(SIZE_MAX, id);

        std::swap(container[index], container[container.size() -1]);

        container.pop_back();

    }
};

template<typename T>
struct multidimensional_vector<T, 0> {
    using type =T;
};


#endif //MODERNCPP_OBJECTINDEXER_H

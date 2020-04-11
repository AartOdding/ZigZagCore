#pragma once

#include <variant>
#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <type_traits>
#include <glm/glm.hpp>

#include <ZigZag/HeapValue.hpp>



namespace ZigZag
{


enum class VariantType
{
    Null = 0,
    VariantMap,

    Int64,
    Float64,
    String,
    Vec2,
    Vec3,
    Vec4,
    IVec2,
    IVec3,
    IVec4,
    Mat3,
    Mat4,

    Int64_Array,
    Float64_Array,
    String_Array,
    Vec2_Array,
    Vec3_Array,
    Vec4_Array,
    IVec2_Array,
    IVec3_Array,
    IVec4_Array,
    Mat3_Array,
    Mat4_Array,
};


class Variant;


class VariantMap
{
public:

    VariantMap() = default;

private:

    std::unordered_map<std::string, Variant> m_values;

};


class Variant
{
public:

    Variant() = default;

    Variant(const Variant& other)
        : m_storage(other.m_storage)
    { }

    Variant(Variant&& other)
        : m_storage(std::move(other.m_storage))
    { }

    template<typename T>
    Variant(const T& data)
    {
        using Type = typename std::remove_reference<T>::type;

        if constexpr(std::is_integral<Type>::value)
        {
            m_storage = static_cast<int64_t>(data);
        }
        else if constexpr (std::is_floating_point<Type>::value)
        {
            m_storage = static_cast<double>(data);
        }
        else if constexpr(sizeof(Type) > 3 * sizeof(void*))
        {
            m_storage = HeapValue<Type>(data);
        }
        else
        {
            m_storage = data;
        }
    }

    template<typename T>
    Variant(T&& data)
    {
        using Type = typename std::remove_reference<T>::type;

        if constexpr(std::is_integral<Type>::value)
        {
            m_storage = static_cast<int64_t>(data);
        }
        else if constexpr (std::is_floating_point<Type>::value)
        {
            m_storage = static_cast<double>(data);
        }
        else if constexpr(sizeof(Type) > 3 * sizeof(void*))
        {
            m_storage = HeapValue<Type>(std::move(data));
        }
        else
        {
            m_storage = std::move(data);
        }
    }
    
    Variant& operator=(const Variant& other)
    {
        m_storage = other.m_storage;
        return *this;
    }

    Variant& operator=(Variant&& other)
    {
        m_storage = std::move(other.m_storage);
        return *this;
    }

    template<typename T>
    Variant& operator=(const T& data)
    {
        using Type = typename std::remove_reference<T>::type;

        if constexpr(std::is_integral<Type>::value)
        {
            m_storage = static_cast<int64_t>(data);
        }
        else if constexpr (std::is_floating_point<Type>::value)
        {
            m_storage = static_cast<double>(data);
        }
        else
        {
            m_storage = data;
        }
        return *this;
    }

    template<typename T>
    Variant& operator=(T&& data)
    {
        using Type = typename std::remove_reference<T>::type;

        if constexpr(std::is_integral<Type>::value)
        {
            m_storage = static_cast<int64_t>(data);
        }
        else if constexpr (std::is_floating_point<Type>::value)
        {
            m_storage = static_cast<double>(data);
        }
        else
        {
            m_storage = std::move(data);
        }
        return *this;
    }

    bool isNull() const;

    void clear();

    VariantType getType() const;

    bool hasType(VariantType type) const;

    template<typename T>
    bool canGet() const
    {
        if constexpr(std::is_integral<T>::value)
        {
            return std::holds_alternative<int64_t>(m_storage);
        }
        else if constexpr (std::is_floating_point<T>::value)
        {
            return std::holds_alternative<double>(m_storage);
        }
        else if constexpr(sizeof(T) > 3 * sizeof(void*))
        {
            return std::holds_alternative<HeapValue<T>>(m_storage);
        }
        else
        {
            return std::holds_alternative<T>(m_storage);
        }
    }

    template<typename T>
    const T& get() const
    {
        if constexpr(std::is_integral<T>::value)
        {
            static T data;
            data = static_cast<T>(std::get<int64_t>(m_storage));
            return data;
        }
        else if constexpr (std::is_floating_point<T>::value)
        {
            static T data;
            data = static_cast<T>(std::get<int64_t>(m_storage));
            return data;
        }
        else if constexpr(sizeof(T) > 3 * sizeof(void*))
        {
            return std::get<HeapValue<T>>(m_storage).value();
        }
        else
        {
            return std::get<T>(m_storage);
        }
    }

private:

    using StorageType = std::variant // All types larger than 3 pointers should be HeapValue<type>
    <
        std::monostate, // Null type
        HeapValue<VariantMap>,

        int64_t,
        double,
        std::string,
        glm::vec2,
        glm::vec3,
        glm::vec4,
        glm::ivec2,
        glm::ivec3,
        glm::ivec4,
        HeapValue<glm::mat3>,
        HeapValue<glm::mat4>,

        std::vector<int64_t>,
        std::vector<double>,
        std::vector<std::string>,
        std::vector<glm::vec2>,
        std::vector<glm::vec3>,
        std::vector<glm::vec4>,
        std::vector<glm::ivec2>,
        std::vector<glm::ivec3>,
        std::vector<glm::ivec4>,
        std::vector<glm::mat3>,
        std::vector<glm::mat4>
    >;

    StorageType m_storage;

};


}

#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <ZigZag/ParentChildRelationship.hpp>


namespace ZigZag
{

class BaseParameter;


class Object : public ZigZagParent<Object, BaseParameter>
{
public:

    Object(Object* parent = nullptr, std::string_view name = std::string());

    virtual ~Object();

    /*
     * If there is a conflict with a sibling when renaming, then the next available name will be
     * taken, which would be the name with a number behind it.
     */
    void setName(std::string_view name);

    /*
     * When an object is reparented, and there is a naming conflict with one of the new siblings 
     * the object that is being reparented is the one that will have its name changed to keep all 
     * the names unique. This function will throw an exception if the reparenting were to create
     * a loop in the parent hierarchy.
     */
    virtual void setParent(Object* parent);

    
    const std::string& getName() const;
    const std::string& getFullName() const;

    
    Object* getParent() const;

    bool hasChildren() const;
    bool hasChildWithName(std::string_view childName) const;

    const std::vector<Object*>& getChildObjects() const;
    Object* getChildWithName(std::string_view childName) const;

    /*
     * Returns the root object of this tree of ZigZag Objects. If this is the root itself, then 
     * this is returned.
     */
    Object* getRootObject();
    const Object* getRootObject() const;

    /*
     * Will search in the tree of objects that this object is part of for an object that matches 
     * the full name.
     */
    Object* getObjectWithFullName(const std::string& objectFullName);
    const Object* getObjectWithFullName(const std::string& objectFullName) const;

    bool isChildOf(const Object* potentialParent, bool directOnly) const;
    bool isParentOf(const Object* potentialChild, bool directOnly) const;

    const std::vector<BaseParameter*>& getChildParameters() const;
    

    virtual const char* typeName() const { return "Object"; }

private:

    void updateFullName();
    bool removeFromParent();

    std::string m_name;
    std::string m_fullName;

    Object* m_parent;
    std::vector<Object*> m_children;

};

}

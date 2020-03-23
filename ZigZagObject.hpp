#pragma once

#include <string>
#include <vector>


class ZigZagObject
{
public:

    ZigZagObject(const std::string& name = std::string(), ZigZagObject* parent = nullptr);

    /*
     * If there is a conflict with a sibling when renaming, then the next available name will be
     * taken, (the name with a number after it). Returns true if the intended name could be used,
     * false if the name had to be adjusted.
     */ 
    bool setName(const std::string& name);

    /*
     * Reparenting is not guaranteed to be successful, because it is not allowed to create circles
     * in the parent hierarchy. Returns true on success, else false. When an object is reparented,
     * and there is a naming conflict with one of the new siblings the object that is being 
     * reparented is the one that will have its name changed to keep every name unique.
     */
    bool setParent(ZigZagObject* parent);

    
    const std::string& getName() const;
    const std::string& getFullName() const;
    
    ZigZagObject* getParent() const;

    bool hasChildren() const;
    bool hasChildWithName(const std::string& childName) const;
    const std::vector<ZigZagObject*>& getChildren() const;
    ZigZagObject* getChildWithName(const std::string& childName) const;

    /*
     * Returns the root object of this tree of ZigZag Objects. If this is the root itself, then 
     * this is returned.
     */
    ZigZagObject* getRootObject() const;

    /*
     * Will search in the tree of objects that this object is part of for an object that matches 
     * the full name.
     */
    ZigZagObject* findObjectWithFullName(const std::string& objectFullName);

private:

    std::string m_name;
    std::string m_fullName;

    ZigZagObject* m_parent;
    std::vector<ZigZagObject*> m_children;

};


#include <algorithm>
#include <array>
#include <tuple>
#include <stdexcept>

#include <ZigZag/Object.hpp>
#include <ZigZag/BaseParameter.hpp>


static constexpr std::array specialAllowedCharacters{ '_', '-', '*' };
static ZigZag::CallbackId nextCallbackId = 4567;

static constexpr bool isAlphaNumeric(char character)
{
    return (character >= '0' && character <= '9')
        || (character >= 'A' && character <= 'Z')
        || (character >= 'a' && character <= 'z');
}


static constexpr int getNumericValue(char character)
{
    if (character < '0' || character > '9')
    {
        return -1;
    }
    else
    {
        return character - '0';
    }
}


static constexpr bool isSpecialAllowedCharacter(char character)
{
    for (char allowedCharacter : specialAllowedCharacters)
    {
        if (character == allowedCharacter)
        {
            return true;
        }
    }
    return false;
}


static constexpr bool isCharacterAllowed(char character)
{
    return isAlphaNumeric(character) || isSpecialAllowedCharacter(character);
}


/*
 * Will clean given name such that it only contains the allowed characters, doesnt start
 * or end with a space, and doesnt have any consecutive spaces.
 * Can not be made constexpr because of the string allocation.
 */
static std::string cleanName(std::string_view name)
{
    // Better reserve a bit more space so no reallocation is necessary if the name ends up
    // already being taken.
    std::string cleaned;
    cleaned.reserve(name.size() + 3);

    // Start on true, so that if the string starts with spaces, they will be taken out.
    bool previousCharWasSpace = true;

    for (char character : name)
    {
        if (character == ' ')
        {
            if (!previousCharWasSpace)
            {
                cleaned.push_back(' ');
                previousCharWasSpace = true;
            }
            // If previous character was also a space we do nothing, and it will thus be
            // left out so we can never get more than two spaces in a row. in this case
            // previousCharWasSpace will simply remain true, until a none space character
            // is added, so that even more spaces will also be left out.
        }
        else if (isCharacterAllowed(character))
        {
            cleaned.push_back(character);
            previousCharWasSpace = false;
        }
        else
        {
            cleaned.push_back('*');
            previousCharWasSpace = false;
        }
    }
    if (!cleaned.empty() && previousCharWasSpace)
    {
        // If the cleaned string ends on a space we also remove it. 
        cleaned.pop_back();
    }
    if (cleaned.empty())
    {
        cleaned = "1";
    }
    return cleaned;
}


/*
 * This algorithm is specifically made to find numbers in Object names, where we assume
 * that the number is always separated from the name with a space. This results in the 
 * string "name123" not passing as a valid number while "name 123" is considered valid,
 * strings that only contain a number such as "123" are also considered valid, but all 
 * negative numbers are not considered valid.
 * 
 * Returns:
 * bool: Whether a number was found or not.
 * int:  The value of the number.
 * int:  The amount of characters in the non digit part of the string, excluding the space.
 */
static std::tuple<bool, int, int> getTrailingNumber(const std::string& string)
{
    int number = 0;
    int order = 1;
    int numDigits = 0;
    bool isNumberValid = false;

    for (int i = string.size() - 1; i >= 0; --i)
    {
        int digit = getNumericValue(string[i]);

        if (digit != -1)
        {
            number += digit * order;
            order *= 10;
            isNumberValid = true;
            ++numDigits;
        }
        else
        {
            // If the string only contains numbers "123" this part of the code will never
            // be reached, and thus isNumberValid will remain valid if the if part of this
            // if-else statement has been executed.
            if (string[i] == ' ')
            {
                // if there was a space before the number we increment numDigits so that the
                // size returned of the non number part of the name will be correct.
                ++numDigits;
            }
            else
            {
                // If there was no space then the number is considered invalid.
                numDigits = 0;
                isNumberValid = false;
            }
            break;
        }
    }
    return std::make_tuple(isNumberValid, number, string.size() - numDigits);
}


//---------------------------------------------------------------------------------


namespace ZigZag
{

Object::Object(Object* parent, std::string_view name)
    : m_parent(parent)
{
    setName(name);
    /*
     * Don't need to worry about creating parent loops here, because this object cannot
     * have any children yet, and thus it is impossible for the parent to be a child
     * of this. Thus there cannot be a loop in the hierarchy, which would cause an exception
     * to be thrown. This is something that has to be checked for in the setParent() function.
     */
    if (m_parent)
    {
        m_parent->m_children.push_back(this);
        m_parent->executeChildrenCallback(this, true);
    }
}


Object::~Object()
{
    removeFromParent();

    for (Object* child : m_children)
    {
        child->m_parent = nullptr;

        if (child->m_deleteByParent)
        {
            delete child;
        }
        else
        {
            child->updateFullName();
        }
    }
}


void Object::setName(std::string_view name)
{
    std::string newName = getClosestPotentialName(name);
    
    if (m_name != newName)
    {
        m_name.swap(newName);
        updateFullName();
    }
}


void Object::setParent(Object* parent)
{
    if (m_deleteByParent && !parent)
    {
        throw std::runtime_error("Setting parent to null is not allowed while deleteByParent is true.");
    }
    if (parent && parent->isChildOf(this, false))
    {
        throw std::runtime_error("Bad reparenting operation: Loops not allowed!");
    }
    if (m_parent != parent)
    {
        removeFromParent();

        if (parent)
        {
            m_parent = parent;
            m_parent->m_children.push_back(this);

            std::string oldName;
            m_name.swap(oldName);
            // m_name is now empty, oldName contains previous name.

            setName(oldName);
            m_parent->executeChildrenCallback(this, true);
        }
        else
        {
            m_parent = nullptr;
            updateFullName();
        }
    }
}


const std::string& Object::getName() const
{
    return m_name;
}


const std::string& Object::getFullName() const
{
    return m_fullName;
}


Object* Object::getParent() const
{
    return m_parent;
}


void Object::setDeleteByParent(bool deleteByParent)
{
    if (deleteByParent && !m_parent)
    {
        throw std::runtime_error("Setting deleteByParent to true without having a parent is illegal.");
    }
    m_deleteByParent = deleteByParent;
}


bool Object::getDeleteByParent() const
{
    return m_deleteByParent;
}


bool Object::hasChildren() const
{
    return !m_children.empty();
}


bool Object::hasChildWithName(std::string_view childName) const
{
    for (Object* child : m_children)
    {
        if (child->m_name == childName)
        {
            return true;
        }
    }
    return false;
}


const std::vector<Object*>& Object::getChildObjects() const
{
    return m_children;
}


Object* Object::getChildWithName(std::string_view childName) const
{
    for (Object* child : m_children)
    {
        if (child->m_name == childName)
        {
            return child;
        }
    }
    return nullptr;
}


Object* Object::getRootObject()
{
    Object* root = this;
    
    while(root->m_parent)
    {
        root = root->m_parent;
    }
    return root;
}


const Object* Object::getRootObject() const
{
    const Object* root = this;

    while(root->m_parent)
    {
        root = root->m_parent;
    }
    return root;
}


Object* Object::findObjectWithFullName(const std::string& objectFullName)
{
    /*
    Object* root = getRootObject();
    Object* current = root;
    int currentBegin = 0;

    do
    {

    }
    while (true);
    

    for (int i = 0; ; ++i) // no end condition
    {
        if (objectFullName[i] == '.' || objectFullName[i] == 0)
        {
        }
    }

    auto it = objectFullName.begin(); */
    return nullptr;
}


const Object* Object::findObjectWithFullName(const std::string& objectFullName) const
{
    return nullptr;
}


bool Object::isChildOf(const Object* potentialParent, bool directOnly) const
{
    if (!potentialParent) return false;
    if (directOnly) return potentialParent == m_parent;

    Object* myParent = m_parent;

    while(myParent)
    {
        if (myParent == potentialParent)
        {
            return true;
        }
        myParent = myParent->m_parent;
    }
    return false;
}


bool Object::isParentOf(const Object* potentialChild, bool directOnly) const
{
    if (potentialChild)
    {
        return potentialChild->isChildOf(this, directOnly);
    }
    return false;
}


const std::vector<BaseParameter*>& Object::getChildParameters() const
{
    return ZigZagParent<Object, BaseParameter>::getChildren();
}


CallbackId Object::registerChildrenCallback(std::function<void(Object* child, bool added)> callback)
{
    m_childrenCallbacks.push_back({ nextCallbackId, callback });
    return nextCallbackId++;
}


void Object::deregisterChildrenCallback(CallbackId callackId)
{
    for (auto it = m_childrenCallbacks.begin(); it != m_childrenCallbacks.end(); ++it)
    {
        if (it->id == callackId)
        {
            m_childrenCallbacks.erase(it);
            return;
        }
    }
    assert(false);
}


std::string Object::getClosestPotentialName(std::string_view desiredName) const
{
    std::string cleanedName = cleanName(desiredName);

    if (m_name == cleanedName || !m_parent)
    {
        // If the object already has the given name, it is returned qithout modification 
        // because this function should only be used to find a suitable name for this object.
        // If there is no parent the name is also valid because there are no competing siblings. 
    }
    else if (m_parent->hasChildWithName(cleanedName))
    {
        // If the name is already taken we start appending numbers to it, until we 
        // find a free name. 
        auto [isNumber, number, nameSize] = getTrailingNumber(cleanedName);
        do
        {
            if (isNumber)
            {
                cleanedName.resize(nameSize == 0 ? 0 : nameSize + 1);
                cleanedName.append(std::to_string(++number));
            }
            else
            {
                number = 1;
                isNumber = true;

                cleanedName.resize(nameSize);
                cleanedName.append(" ");
                cleanedName.append(std::to_string(number));
            }
        } while (m_parent->hasChildWithName(cleanedName));
    }

    return cleanedName;
}


/* 
 * Updates the full name of the object, but assumes the name is already valid.
 * We do not contain this whole function in a big if statement to check whether the full
 * name actually needs to be updated, because that would be quite costly, and this function
 * is private, which means we can make sure to only call it when we know the full name 
 * needs to be updated. 
 */
void Object::updateFullName()
{
    if (m_parent)
    {
        m_fullName.reserve(m_parent->getFullName().size() + m_name.size() + 2);
        m_fullName = m_parent->getFullName();
        m_fullName.append("/");
        m_fullName.append(m_name);
    }
    else
    {
        m_fullName.reserve(m_name.size() + 2);
        m_fullName = "/";
        m_fullName.append(m_name);
    }
    for (Object* child : m_children)
    {
        child->updateFullName();
    }
}


bool Object::removeFromParent()
{
    if (m_parent)
    {
        auto parent = m_parent;
        m_parent = nullptr;

        auto pos = std::find(parent->m_children.begin(), parent->m_children.end(), this);

        assert(pos != parent->m_children.end());
        if (pos != parent->m_children.end())
        {
            parent->m_children.erase(pos);
            parent->executeChildrenCallback(this, false);
            return true;
        }
    }
    return false;
}


void Object::executeChildrenCallback(Object* child, bool added)
{
    for (const auto& cb : m_childrenCallbacks)
    {
        cb.function(child, added);
    }
}

}

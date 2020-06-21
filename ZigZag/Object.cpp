#include <algorithm>
#include <tuple>
#include <stdexcept>

#include <ZigZag/Object.hpp>
#include <ZigZag/BaseParameter.hpp>


static std::string specialAllowedCharacters = "_-*";


static bool isAlphaNumeric(char character)
{
    return (character >= '0' && character <= '9')
        || (character >= 'A' && character <= 'Z')
        || (character >= 'a' && character <= 'z');
}


static int getNumericValue(char character)
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


static bool isSpecialAllowedCharacter(char character)
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


static bool isCharacterAllowed(char character)
{
    return isAlphaNumeric(character) || isSpecialAllowedCharacter(character);
}


static std::string cleanName(std::string_view name)
{
    std::string cleaned;
    cleaned.reserve(name.size() + 1);

    // Start on true, so that if the string starts with spaces, they will be ignored.
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
    if (!cleaned.empty() && cleaned.back() == ' ')
    {
        cleaned.pop_back();
    }
    if (cleaned.empty())
    {
        cleaned = "1";
    }
    return cleaned;
}


/*
 * Returns:
 * bool: Whether a number was found or not.
 * int:  The value of the number.
 * int:  The amount of characters in the non digit part of the string.
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
            if (string[i] != ' ')
            {
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
    /*
     * Don't need to worry about creating parent loops here, because this object cannot
     * have any children yet, and thus it is also impossible for the parent to be a child
     * of this. Thus there cannot be a loop.
     */

    // Set name before 'this' is added as a child in the parent. m_parent has already been set at this point!
    setName(name);

    if (m_parent)
    {
        m_parent->m_children.push_back(this);
    }

    // In this case initializes m_fullName
    updateFullName();
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
    setNameImplementation(name, false);
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
            setNameImplementation(m_name, true);
            m_parent->m_children.push_back(this);
        }
        updateFullName();
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


void Object::setNameImplementation(std::string_view name, bool reparented)
{
    std::string cleanedName = cleanName(name);

    if (m_name != cleanedName || reparented)
    {
        // Safe bacause, if parent is null, the second part will not be evaluated.
        // If there is no parent or no sibling has the desired name, take it.
        if (!m_parent || !m_parent->hasChildWithName(cleanedName))
        {
            m_name = cleanedName;
        }
        else
        {
            auto [isNumber, number, nameSize] = getTrailingNumber(cleanedName);
            do
            {
                if (isNumber)
                {
                    cleanedName.resize(nameSize);
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

            m_name = cleanedName;
        }
        for (Object* child : m_children)
        {
            child->updateFullName();
        }
    }
}


void Object::updateFullName()
{
    if (m_parent)
    {
        m_fullName.clear();
        m_fullName.reserve(m_parent->getFullName().size() + m_name.size() + 2);
        m_fullName.append(m_parent->getFullName());
        m_fullName.append(".");
        m_fullName.append(m_name);
    }
    else
    {
        m_fullName = m_name;
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
        auto pos = std::find(m_parent->m_children.begin(), m_parent->m_children.end(), this);

        if (pos != m_parent->m_children.end())
        {
            m_parent->m_children.erase(pos);
            return true;
        }
    }
    return false;
}

}

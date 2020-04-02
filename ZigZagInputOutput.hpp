#pragma once

#include <vector>


template<typename OUTPUT_TYPE, typename INPUT_TYPE>
class ZigZagOutput;

template<typename INPUT_TYPE, typename OUTPUT_TYPE>
class ZigZagInput;

template<typename OUTPUT_TYPE, typename INPUT_TYPE>
bool connect(ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>* output, ZigZagInput<INPUT_TYPE, OUTPUT_TYPE>* input);

template<typename OUTPUT_TYPE, typename INPUT_TYPE>
bool disconnect(ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>* output, ZigZagInput<INPUT_TYPE, OUTPUT_TYPE>* input);

/*
 *  No virtual destructors because these classes should not be used polymorphically.
 */


template<typename INPUT_TYPE, typename OUTPUT_TYPE>
class ZigZagInput
{
public:

    ~ZigZagInput();

    bool isConnected();
    bool isConnectedWith(const OUTPUT_TYPE* output) const;

    const OUTPUT_TYPE* getConnectedOutput() const;


private:

    friend bool connect(ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>* output, ZigZagInput<INPUT_TYPE, OUTPUT_TYPE>* input);
    friend bool disconnect(ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>* output, ZigZagInput<INPUT_TYPE, OUTPUT_TYPE>* input);

    OUTPUT_TYPE* m_connectedOutput = nullptr;

};




template<typename OUTPUT_TYPE, typename INPUT_TYPE>
class ZigZagOutput
{
public:

    ~ZigZagOutput();

    bool isConnected();
    bool isConnectedWith(const INPUT_TYPE* input) const;

    const std::vector<INPUT_TYPE*>& getConnectedInputs() const;


private:

    friend bool connect(ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>* output, ZigZagInput<INPUT_TYPE, OUTPUT_TYPE>* input);
    friend bool disconnect(ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>* output, ZigZagInput<INPUT_TYPE, OUTPUT_TYPE>* input);

    std::vector<INPUT_TYPE*> m_connectedInputs;

};




template<typename OUTPUT_TYPE, typename INPUT_TYPE>
bool connect(ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>* output, ZigZagInput<INPUT_TYPE, OUTPUT_TYPE>* input)
{
    if (input && output && !input->isConnectedWith(output))
    {
        if (input->isConnected())
        {
            disconnect(static_cast<ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>*>(input->m_connectedOutput), input);
        }
    }
}


template<typename OUTPUT_TYPE, typename INPUT_TYPE>
bool disconnect(ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>* output, ZigZagInput<INPUT_TYPE, OUTPUT_TYPE>* input)
{
    if (input->isConnectedWith(output))
    {
        input->m_connectedOutput = nullptr;
        output->m_connectedInputs.erase(
            std::find(
                output->m_connectedInputs.begin(), 
                output->m_connectedInputs.end(), 
                static_cast<INPUT_TYPE*>(input)));
    }
}




template<typename INPUT_TYPE, typename OUTPUT_TYPE>
ZigZagInput<INPUT_TYPE, OUTPUT_TYPE>::~ZigZagInput()
{
    using CorrespondingOutput = ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>;

    if (m_connectedOutput)
    {
        disconnect(static_cast<CorrespondingOutput*>(m_connectedOutput), this);
    }
}


template<typename INPUT_TYPE, typename OUTPUT_TYPE>
bool ZigZagInput<INPUT_TYPE, OUTPUT_TYPE>::isConnected()
{
    return m_connectedOutput != nullptr;
}


template<typename INPUT_TYPE, typename OUTPUT_TYPE>
bool ZigZagInput<INPUT_TYPE, OUTPUT_TYPE>::isConnectedWith(const OUTPUT_TYPE* output) const
{
    return m_connectedOutput == output;
}


template<typename INPUT_TYPE, typename OUTPUT_TYPE>
const OUTPUT_TYPE* ZigZagInput<INPUT_TYPE, OUTPUT_TYPE>::getConnectedOutput() const
{
    return m_connectedOutput;
}




template<typename OUTPUT_TYPE, typename INPUT_TYPE>
ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>::~ZigZagOutput()
{
    using CorrespondingInput = ZigZagInput<INPUT_TYPE, OUTPUT_TYPE>;

    for (auto input : m_connectedInputs)
    {
        disconnect(this, static_cast<CorrespondingInput*>(input));
    }
}


template<typename OUTPUT_TYPE, typename INPUT_TYPE>
bool ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>::isConnected()
{
    return !m_connectedInputs.empty();
}


template<typename OUTPUT_TYPE, typename INPUT_TYPE>
bool ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>::isConnectedWith(const INPUT_TYPE* input) const
{
    return std::find(m_connectedInputs.begin(), m_connectedInputs.end(), input) != m_connectedInputs.end();
}


template<typename OUTPUT_TYPE, typename INPUT_TYPE>
const std::vector<INPUT_TYPE*>& ZigZagOutput<OUTPUT_TYPE, INPUT_TYPE>::getConnectedInputs() const
{
    return m_connectedInputs;
}

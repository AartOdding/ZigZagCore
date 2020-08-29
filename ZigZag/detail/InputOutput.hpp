#pragma once

#include <algorithm>
#include <type_traits>
#include <vector>


namespace ZigZag
{
    namespace detail
    {
        template<typename OUTPUT_TYPE, typename INPUT_TYPE>
        class Output;

        template<typename INPUT_TYPE, typename OUTPUT_TYPE>
        class Input;
    }

    template<typename OUTPUT_TYPE, typename INPUT_TYPE>
    bool connect(ZigZag::detail::Output<OUTPUT_TYPE, INPUT_TYPE>* output, ZigZag::detail::Input<INPUT_TYPE, OUTPUT_TYPE>* input);

    template<typename OUTPUT_TYPE, typename INPUT_TYPE>
    bool disconnect(ZigZag::detail::Output<OUTPUT_TYPE, INPUT_TYPE>* output, ZigZag::detail::Input<INPUT_TYPE, OUTPUT_TYPE>* input);

    namespace detail
    {

        template<typename INPUT_TYPE, typename OUTPUT_TYPE>
        class Input
        {
        public:

            ~Input(); // Non-virtual: Class should not be used polymorphically.

            bool isConnected();
            bool isConnectedTo(const OUTPUT_TYPE* output) const;

            OUTPUT_TYPE* getConnectedOutput() const;

        private:

            friend bool ZigZag::connect<OUTPUT_TYPE, INPUT_TYPE>(Output<OUTPUT_TYPE, INPUT_TYPE>* output, Input<INPUT_TYPE, OUTPUT_TYPE>* input);
            friend bool ZigZag::disconnect<OUTPUT_TYPE, INPUT_TYPE>(Output<OUTPUT_TYPE, INPUT_TYPE>* output, Input<INPUT_TYPE, OUTPUT_TYPE>* input);

            OUTPUT_TYPE* m_connectedOutput = nullptr;

        };



        template<typename OUTPUT_TYPE, typename INPUT_TYPE>
        class Output
        {
        public:

            ~Output(); // Non-virtual: Class should not be used polymorphically.

            bool isConnected();
            bool isConnectedTo(const INPUT_TYPE* input) const;

            const std::vector<INPUT_TYPE*>& getConnectedInputs() const;

        private:

            friend bool ZigZag::connect<OUTPUT_TYPE, INPUT_TYPE>(Output<OUTPUT_TYPE, INPUT_TYPE>* output, Input<INPUT_TYPE, OUTPUT_TYPE>* input);
            friend bool ZigZag::disconnect<OUTPUT_TYPE, INPUT_TYPE>(Output<OUTPUT_TYPE, INPUT_TYPE>* output, Input<INPUT_TYPE, OUTPUT_TYPE>* input);

            std::vector<INPUT_TYPE*> m_connectedInputs;

        };

    }


    template<typename OUTPUT_TYPE, typename INPUT_TYPE>
    bool connect(detail::Output<OUTPUT_TYPE, INPUT_TYPE>* output, detail::Input<INPUT_TYPE, OUTPUT_TYPE>* input)
    {
        static_assert(std::is_base_of<detail::Output<OUTPUT_TYPE, INPUT_TYPE>, OUTPUT_TYPE>::value);
        static_assert(std::is_base_of<detail::Input<INPUT_TYPE, OUTPUT_TYPE>, INPUT_TYPE>::value);

        if (input && output && !input->isConnectedTo(static_cast<OUTPUT_TYPE*>(output)))
        {
            if (input->isConnected())
            {
                disconnect(static_cast<detail::Output<OUTPUT_TYPE, INPUT_TYPE>*>(input->m_connectedOutput), input);
            }
            input->m_connectedOutput = static_cast<OUTPUT_TYPE*>(output);
            output->m_connectedInputs.push_back(static_cast<INPUT_TYPE*>(input));
            return true;
        }
        return false;
    }


    template<typename OUTPUT_TYPE, typename INPUT_TYPE>
    bool disconnect(detail::Output<OUTPUT_TYPE, INPUT_TYPE>* output, detail::Input<INPUT_TYPE, OUTPUT_TYPE>* input)
    {
        static_assert(std::is_base_of<detail::Output<OUTPUT_TYPE, INPUT_TYPE>, OUTPUT_TYPE>::value);
        static_assert(std::is_base_of<detail::Input<INPUT_TYPE, OUTPUT_TYPE>, INPUT_TYPE>::value);
    
        if (input && output && input->isConnectedTo(static_cast<OUTPUT_TYPE*>(output)))
        {
            input->m_connectedOutput = nullptr;
            output->m_connectedInputs.erase(
                std::find(
                    output->m_connectedInputs.begin(), 
                    output->m_connectedInputs.end(), 
                    static_cast<INPUT_TYPE*>(input)));
            return true;
        }
        return false;
    }

}


#include <ZigZag/detail/Input.inl>
#include <ZigZag/detail/Output.inl>

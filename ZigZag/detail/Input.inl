
namespace ZigZag
{
	namespace detail
	{

        template<typename INPUT_TYPE, typename OUTPUT_TYPE>
        Input<INPUT_TYPE, OUTPUT_TYPE>::~Input()
        {
            using CorrespondingOutput = Output<OUTPUT_TYPE, INPUT_TYPE>;

            if (m_connectedOutput)
            {
                ZigZag::disconnect(static_cast<CorrespondingOutput*>(m_connectedOutput), this);
            }
        }


        template<typename INPUT_TYPE, typename OUTPUT_TYPE>
        bool Input<INPUT_TYPE, OUTPUT_TYPE>::isConnected()
        {
            return m_connectedOutput != nullptr;
        }


        template<typename INPUT_TYPE, typename OUTPUT_TYPE>
        bool Input<INPUT_TYPE, OUTPUT_TYPE>::isConnectedTo(const OUTPUT_TYPE* output) const
        {
            return m_connectedOutput == output;
        }


        template<typename INPUT_TYPE, typename OUTPUT_TYPE>
        OUTPUT_TYPE* Input<INPUT_TYPE, OUTPUT_TYPE>::getConnectedOutput() const
        {
            return m_connectedOutput;
        }

	}
}

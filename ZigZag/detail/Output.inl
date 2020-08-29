
namespace ZigZag
{
	namespace detail
	{

        template<typename OUTPUT_TYPE, typename INPUT_TYPE>
        Output<OUTPUT_TYPE, INPUT_TYPE>::~Output()
        {
            using CorrespondingInput = Input<INPUT_TYPE, OUTPUT_TYPE>;

            for (auto input : m_connectedInputs)
            {
                ZigZag::disconnect(this, static_cast<CorrespondingInput*>(input));
            }
        }


        template<typename OUTPUT_TYPE, typename INPUT_TYPE>
        bool Output<OUTPUT_TYPE, INPUT_TYPE>::isConnected()
        {
            return !m_connectedInputs.empty();
        }


        template<typename OUTPUT_TYPE, typename INPUT_TYPE>
        bool Output<OUTPUT_TYPE, INPUT_TYPE>::isConnectedTo(const INPUT_TYPE* input) const
        {
            return std::find(m_connectedInputs.begin(), m_connectedInputs.end(), input) != m_connectedInputs.end();
        }


        template<typename OUTPUT_TYPE, typename INPUT_TYPE>
        const std::vector<INPUT_TYPE*>& Output<OUTPUT_TYPE, INPUT_TYPE>::getConnectedInputs() const
        {
            return m_connectedInputs;
        }

	}
}

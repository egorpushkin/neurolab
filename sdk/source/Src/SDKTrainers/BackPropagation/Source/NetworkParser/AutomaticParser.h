#ifndef AUTOMATICPARSER_H__BPFANN__INCLUDED_
#define AUTOMATICPARSER_H__BPFANN__INCLUDED_

namespace Trainer
{

	class AutomaticParser
	{
	public:

		AutomaticParser(GenericNetworkRef network);

		// Public interface
		result DoConstructNetwork(); 

	private:

		// Private interface
		NiKit::IElementPtr FindRoot();
		void ContinueChain(NiKit::IElementRef node);

	private:

		GenericNetworkPtr network_;

	};

	typedef Loki::SmartPtr<	AutomaticParser > AutomaticParserPtr;
	typedef const AutomaticParserPtr& AutomaticParserRef;

} // namespace Trainer

#endif // !AUTOMATICPARSER_H__BPFANN__INCLUDED_

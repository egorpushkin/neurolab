#include "Includes.h"

#include "BasicFunctor.h"

namespace Simple2dCharting
{

	// BasicParameters
	BasicFunctor::BasicParameters::BasicParameters()
	{
	}
	
	BasicFunctor::BasicParameters::~BasicParameters()
	{
	}

	// BasicFunctor
	BasicFunctor::BasicFunctor()
		: pParams_()
	{
	}

	BasicFunctor::~BasicFunctor()
	{
		delete pParams_;
	}

	// Public interface
	void BasicFunctor::SetParameters(const BasicFunctor::BasicParameters& params)
	{
		delete pParams_;        
		pParams_ = params.Clone();
	}
	
	const BasicFunctor::BasicParameters& BasicFunctor::GetParameters() const
	{
		return *pParams_;
	}


} // Simple2dCharting

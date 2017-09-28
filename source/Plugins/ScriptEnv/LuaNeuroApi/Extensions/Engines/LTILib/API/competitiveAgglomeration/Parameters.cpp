#include "stdafx.h"

#include "../../Common/Includes.h"

#include "competitiveAgglomeration.h"

namespace LTILib
{

	IMPLEMENT_SETPARAM_FUNC(
		compagglom_setCardinalityFactor, CompAgglomApiSngl, 
		double, cardinalityFactor);

	IMPLEMENT_SETPARAM_FUNC(
		compagglom_setTimeConstant, CompAgglomApiSngl, 
		double, timeConstant);

	IMPLEMENT_SETPARAM_FUNC(
		compagglom_setClustersCount, CompAgglomApiSngl, 
		int, initialNumberOfClusters);

	IMPLEMENT_SETPARAM_FUNC(
		compagglom_setInitialIterations, CompAgglomApiSngl, 
		int, initialIterations);

	IMPLEMENT_SETPARAM_FUNC(
		compagglom_setMinimumCardinality, CompAgglomApiSngl, 
		double, minimumCardinality);

	IMPLEMENT_SETPARAM_FUNC(
		compagglom_setFuzzifier, CompAgglomApiSngl, 
		double, fuzzifier);

	IMPLEMENT_SETPARAM_FUNC(
		compagglom_setMaxIterations, CompAgglomApiSngl, 
		int, maxIterations);

	IMPLEMENT_SETPARAM_FUNC(
		compagglom_setConvergenceThreshold, CompAgglomApiSngl, 
		double, convergenceThreshold);

	class CompAgglomParams
	{
	public:
		CompAgglomParams()
		{
			CompAgglomApiSngl::Instance().AddMethod("setCardinalityFactor", compagglom_setCardinalityFactor);
			CompAgglomApiSngl::Instance().AddMethod("setTimeConstant", compagglom_setTimeConstant);
			CompAgglomApiSngl::Instance().AddMethod("setClustersCount", compagglom_setClustersCount);
			CompAgglomApiSngl::Instance().AddMethod("setInitialIterations", compagglom_setInitialIterations);
			CompAgglomApiSngl::Instance().AddMethod("setMinimumCardinality", compagglom_setMinimumCardinality);
			CompAgglomApiSngl::Instance().AddMethod("setFuzzifier", compagglom_setFuzzifier);
			CompAgglomApiSngl::Instance().AddMethod("setMaxIterations", compagglom_setMaxIterations);
			CompAgglomApiSngl::Instance().AddMethod("setConvergenceThreshold", compagglom_setConvergenceThreshold);
		}
	};

	CompAgglomParams compAgglomParams;

} // namespace LTILib

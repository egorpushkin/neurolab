#ifndef BASICFUNCTOR_H__S2DCHARTING__INCLUDED_
#define BASICFUNCTOR_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class BasicFunctor
	{
	public:

		class BasicParameters
		{
		public:
			BasicParameters();
			virtual ~BasicParameters();

			// Pure interface
			virtual BasicParameters* Clone() const = 0;

		}; // BasicParameters		 

		BasicFunctor();
		virtual ~BasicFunctor();

		// Public interface
		virtual void SetParameters(const BasicParameters& params);
		virtual const BasicParameters& GetParameters() const;

	protected:

		BasicParameters* pParams_;



	}; // BasicFunctor

	//typedef Loki::StrongPtr< BasicRenderer > BasicRendererPtr;
	//typedef const BasicRendererPtr& BasicRendererRef;

} // Simple2dCharting

#endif // !BASICFUNCTOR_H__S2DCHARTING__INCLUDED_

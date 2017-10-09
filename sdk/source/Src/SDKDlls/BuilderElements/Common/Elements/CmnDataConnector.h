#ifndef CMNDATACONNECTOR_H__BUILDERELEMENTS__INCLUDED_
#define CMNDATACONNECTOR_H__BUILDERELEMENTS__INCLUDED_

class CCmnDataConnector 
	: public NetworkImportingKit::IDataConnector
	, public IStorageController
{
public:
	CCmnDataConnector();
	virtual ~CCmnDataConnector();

protected:
	// IStorageController declarations section
	virtual result			Serialize(FILEDev& fileDev, bool loading);

	// IDataConnector implementations section
	virtual result			AddConnectionTo(NetworkImportingKit::IElement* piElement, uint factoryType);
	virtual void			RemoveConnection(
		NetworkImportingKit::CConnection* pConnection);

	virtual	void			SetAddConnectionState(uint state, uint count);
	virtual result			ProcessAddConnection(NetworkImportingKit::IElement* piElement);

	virtual	bool			MoveConnection(
		const NetworkImportingKit::CConnection* pConnection, bool moveUp = false);

	virtual NetworkImportingKit::IConnectionsFactory* 
		GetConnectionsFactory(uint factoryType) const;

	virtual	NetworkImportingKit::CConnection*	
		FindConnectionByPrevPtr(dword_ptr connection);

protected:       
	NetworkImportingKit::IConnectionsFactory*	piInputsFactory_;
	NetworkImportingKit::IConnectionsFactory*	piOutputsFactory_;

	int						addConnectionState_;
	int						connectionsCount_;
};

#endif // !CMNDATACONNECTOR_H__BUILDERELEMENTS__INCLUDED_

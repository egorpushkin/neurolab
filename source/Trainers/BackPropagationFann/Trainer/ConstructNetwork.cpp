#include "stdafx.h"

#include "BackProp.h"

#include "ConstructNetwork.h"

#include "../UI/NetConstructDlg.h"

#include "AutomaticParser.h"

ConstructNetwork::ConstructNetwork(
	sBPSettings* pSettings, 
	IElementsCollection* piElementsCollection,
	IDataFile* piDataFile,
	ILogProvider* piLogProvider,
	GenericNetwork* pNetwork)
	: pSettings_(pSettings) 
	, piElementsCollection_(piElementsCollection)
	, piDataFile_(piDataFile)
	, piLogProvider_(piLogProvider)
	, pNetwork_(pNetwork)
{
}

bool ConstructNetwork::DoConstructNetwork()
{
	if ( !pSettings_ || !piElementsCollection_ || !piDataFile_ || !piLogProvider_ || !pNetwork_ )
		return false;

	if ( pSettings_->iNetStruct == NSA_AUTOMATIC )
	{
		if ( !PrivateAutomaticConstruct() )
			return false;		

		if ( !pNetwork_->CompliteVerification() )
			return false;
	} 
	else if ( pSettings_->iNetStruct == NSA_CUSTOM )
	{
		int res = IDNO;

		if ( !pNetwork_->IsEmpty() )
		{
			res = AfxMessageBox(_T("Do you want to use previously constructed network?"), MB_YESNO);
		}

		if ( !PrivateCustomConstruct( ( res != IDYES ) ? ( true ) : ( false ) ) ) 
			return false;
	}

	piLogProvider_->AddLogMessage(CString("N"), 
		CString("Network pattern constructed successfully."), 
		CString("Constructor"));

	return true;    
}

// Private interface
bool ConstructNetwork::PrivateCustomConstruct(bool skipInitialCheck)
{
	if ( !skipInitialCheck )
	{		
		if ( pNetwork_->CompliteVerification() )
			return true;

		int res = AfxMessageBox(_T("Network pattern constructed incorrectly.\nDo you want to reconstruct it?"), MB_YESNO);
		if ( res != IDYES )
			return false;
	}

    // Display construct tool
	CNetConstructDlg constructDlg(piElementsCollection_, pNetwork_);
	INT_PTR res = constructDlg.DoModal();
	if ( res != IDOK )
		return false;

	// Final check
	return PrivateCustomConstruct(false);
}

bool ConstructNetwork::PrivateAutomaticConstruct()
{
	AutomaticParser parser(piElementsCollection_, piLogProvider_, pNetwork_);
	
	return parser.DoConstructNetwork();
}


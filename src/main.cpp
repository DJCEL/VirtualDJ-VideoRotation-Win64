#include "VideoRotation8.h"


HRESULT VDJ_API DllGetClassObject(const GUID &rclsid,const GUID &riid,void** ppObject)
{
	// This is the standard DLL loader for COM object.

	if (memcmp(&rclsid, &CLSID_VdjPlugin8, sizeof(GUID))==0 && memcmp(&riid, &IID_IVdjPluginVideoFx8, sizeof(GUID))==0) 
	{
		// if CLSID_VdjPlugin8 and IID_IVdjPluginVideoFx8 are requested, we create an instance of CVideoRotation8.
	    *ppObject = new CVideoRotation8();
	}
	else 
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}

	return NO_ERROR;
}

#pragma once

class CObject;

class CObjectSP
{
    public:

        CObject* pObject;
        s32 ObjectType;

        CObjectSP()
        {
            pObject = NULL;
        }
        ~CObjectSP()
        {
			//Kitty::Base object should support release method
			//		 but i do not know hot to do that.
			//       commented for know
            //if (pObject)
              //    pObject->Release(__FUNCTION__, __LINE__, ObjectType);
            pObject = NULL;
        }
};

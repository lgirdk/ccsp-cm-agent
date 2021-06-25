/*********************************************************************
 * Copyright 2017-2019 ARRIS Enterprises, LLC.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **********************************************************************/

#include "cosa_lgi_cablemodem_internal.h"

PCOSA_DATAMODEL_LGI_CABLEMODEM g_pLgiCM;
PCOSA_DATAMODEL_LGI_CABLEMODEM_QOS Lgi_QosSF;

/**********************************************************************

    caller:     owner of the object

    prototype:

        ANSC_HANDLE
        CosaLgiCableModemCreate
            (
            );

    description:

        This function constructs cosa LgiCableModem object and return handle.

    argument:

    return:     newly created LgiCableModem object.

**********************************************************************/

ANSC_HANDLE
CosaLgiCableModemCreate
    (
        VOID
    )
{
    PCOSA_DATAMODEL_LGI_CABLEMODEM  pMyObject = NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PCOSA_DATAMODEL_LGI_CABLEMODEM)AnscAllocateMemory(sizeof(COSA_DATAMODEL_LGI_CABLEMODEM));

    if ( !pMyObject )
    {
        return  (ANSC_HANDLE)NULL;
    }

    /*
     * Initialize the common variables and functions for a container object.
     */
    pMyObject->Oid               = COSA_DATAMODEL_LGI_CABLEMODEM_OID;
    pMyObject->Create            = CosaLgiCableModemCreate;
    pMyObject->Remove            = CosaLgiCableModemRemove;
    pMyObject->Initialize        = CosaLgiCableModemInitialize;

    pMyObject->Initialize   ((ANSC_HANDLE)pMyObject);

    g_pLgiCM = pMyObject;

    return  (ANSC_HANDLE)pMyObject;
}

/**********************************************************************

    caller:     self

    prototype:

        ANSC_STATUS
        CosaLgiCableModemInitialize
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function initiate  cosa LgiCableModem object and return handle.

    argument:   ANSC_HANDLE                 hThisObject
            This handle is actually the pointer of this object
            itself.

    return:     operation status.

**********************************************************************/

ANSC_STATUS
CosaLgiCableModemInitialize
    (
        ANSC_HANDLE                 hThisObject
    )
{
    return ANSC_STATUS_SUCCESS;
}

/**********************************************************************

    caller:     self

    prototype:

        ANSC_STATUS
        CosaLgiCableModemRemove
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function initiate  cosa LgiCableModem object and return handle.

    argument:   ANSC_HANDLE                 hThisObject
            This handle is actually the pointer of this object
            itself.

    return:     operation status.

**********************************************************************/

ANSC_STATUS
CosaLgiCableModemRemove
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PCOSA_DATAMODEL_LGI_CABLEMODEM     pMyObject    = (PCOSA_DATAMODEL_LGI_CABLEMODEM)hThisObject;

    g_pLgiCM = NULL;

    /* Remove necessary resource */
    if ( NULL != pMyObject->pOfdmChannel )
    {
        AnscFreeMemory((ANSC_HANDLE)pMyObject->pOfdmChannel);
    }

    if ( NULL != pMyObject->pOfdmaChannel )
    {
        AnscFreeMemory((ANSC_HANDLE)pMyObject->pOfdmaChannel);
    }

    if(NULL != pMyObject)
    {
        /* Remove self */
        AnscFreeMemory((ANSC_HANDLE)pMyObject);
    }

    return ANSC_STATUS_SUCCESS;
}

/**********************************************************************

    caller:     owner of the object

    prototype:

        ANSC_HANDLE
        CosaLgiCableModemQosCreate
            (
            );

    description:

        This function constructs cosa LgiCableModem object and return handle.

    argument:

    return:     newly created LgiCableModem object.

**********************************************************************/
ANSC_HANDLE
CosaLgiCableModemQosCreate
    (
        VOID
    )
{
    PCOSA_DATAMODEL_LGI_CABLEMODEM_QOS  pMyObject = NULL;

    /*
     * We create object by first allocating memory for holding the variables and member functions.
     */
    pMyObject = (PCOSA_DATAMODEL_LGI_CABLEMODEM_QOS)AnscAllocateMemory(sizeof(COSA_DATAMODEL_LGI_CABLEMODEM_QOS));

    if ( !pMyObject )
    {
        return  (ANSC_HANDLE)NULL;
    }

    /*
     * Initialize the common variables and functions for a container object.
     */
    pMyObject->Oid               = COSA_DATAMODEL_LGI_CABLEMODEM_OID;
    pMyObject->Create            = CosaLgiCableModemQosCreate;
    pMyObject->Remove            = CosaLgiCableModemQosRemove;
    pMyObject->Initialize        = CosaLgiCableModemQosInitialize;

    pMyObject->Initialize   ((ANSC_HANDLE)pMyObject);

    Lgi_QosSF = pMyObject;

    return  (ANSC_HANDLE)pMyObject;
}

/**********************************************************************

    caller:     self

    prototype:

        ANSC_STATUS
        CosaLgiCableModemQosInitialize
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function initiate  cosa LgiCableModem object and return handle.

    argument:   ANSC_HANDLE                 hThisObject
            This handle is actually the pointer of this object
            itself.

    return:     operation status.

**********************************************************************/

ANSC_STATUS
CosaLgiCableModemQosInitialize
    (
        ANSC_HANDLE                 hThisObject
    )
{
    return ANSC_STATUS_SUCCESS;
}

/**********************************************************************

    caller:     self

    prototype:

        ANSC_STATUS
        CosaLgiCableModemQosRemove
            (
                ANSC_HANDLE                 hThisObject
            );

    description:

        This function initiate  cosa LgiCableModem object and return handle.

    argument:   ANSC_HANDLE                 hThisObject
            This handle is actually the pointer of this object
            itself.

    return:     operation status.

**********************************************************************/

ANSC_STATUS
CosaLgiCableModemQosRemove
    (
        ANSC_HANDLE                 hThisObject
    )
{
    PCOSA_DATAMODEL_LGI_CABLEMODEM_QOS  pMyObject = (PCOSA_DATAMODEL_LGI_CABLEMODEM_QOS)hThisObject;

    if ( NULL != pMyObject->pServiceUsFlowChannel )
    {
        AnscFreeMemory((ANSC_HANDLE)pMyObject->pServiceUsFlowChannel);
    }

    if ( NULL != pMyObject->pServiceDsFlowChannel )
    {
        AnscFreeMemory((ANSC_HANDLE)pMyObject->pServiceDsFlowChannel);
    }

    if ( NULL != pMyObject->pSfUsParamset )
    {
        AnscFreeMemory((ANSC_HANDLE)pMyObject->pSfUsParamset);
    }

    if ( NULL != pMyObject->pSfDsParamset )
    {
        AnscFreeMemory((ANSC_HANDLE)pMyObject->pSfDsParamset);
    }

    /* Remove self */
    if (NULL != pMyObject)
    {
        AnscFreeMemory((ANSC_HANDLE)pMyObject);
    }

    Lgi_QosSF = NULL;
    return ANSC_STATUS_SUCCESS;
}


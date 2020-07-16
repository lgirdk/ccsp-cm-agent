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

#ifndef  _COSA_LGI_CABLEMODEM_DML_H
#define  _COSA_LGI_CABLEMODEM_DML_H

#include "cosa_lgi_cablemodem_apis.h"

/***********************************************************************

 APIs for Object:

    CableModemInfo.

    *  LgiCableModem_GetParamBoolValue
    *  LgiCableModem_GetParamIntValue
    *  LgiCableModem_GetParamUlongValue
    *  LgiCableModem_GetParamStringValue

***********************************************************************/

/**************************************************************************/
/*                  Types of service flows                                */
/**************************************************************************/
#define SF_RESERVED                0
#define SF_TYPE_UNDEFINED          1
#define SF_BEST_EFFORT             2  /* best effort */
#define SF_NON_REALTIME_PS         3  /* non real time polling service */
#define SF_REALTIME_PL             4  /* real time polling service */
#define SF_UNSOLICIT_GRANT_AD      5  /* unsolicited grant service with AD */
#define SF_UNSOLICIT_GRANT         6  /* unsolicited grant service */
#define SF_NOT_APPLICABLE          256

/***************************************************************************/

BOOL
LgiCableModem_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    );

BOOL
LgiCableModem_GetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int*                        pInt
    );

BOOL
LgiCableModem_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      pUlong
    );

ULONG
LgiCableModem_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pUlSize
    );

BOOL
LgiCableModem_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        pBool
    );

BOOL
LgiCableModem_SetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG                       vUlong
    );

BOOL
LgiCableModem_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
  );


ULONG
LgiCableModem_Commit
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
LgiCableModem_Rollback
    (
        ANSC_HANDLE                 hInsContext
    );

BOOL
LgiUpstreamChannel_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      puLong
    );


/* Upstream Service */
ULONG
Lgi_US_QosServiceFlow_Synchronize
    (
        ANSC_HANDLE                 hInsContext
    );

BOOL
Lgi_US_QosServiceFlow_IsUpdated
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
Lgi_US_QosServiceFlow_GetEntryCount
    (
        ANSC_HANDLE                 hInsContext
    );

ANSC_HANDLE
Lgi_US_QosServiceFlow_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    );

//Paramset API's
ULONG
Lgi_US_QosParamSet_GetEntryCount
    (
         ANSC_HANDLE                 hInsContext
    );

ANSC_HANDLE
Lgi_US_QosParamSet_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    );

/* Downstream Service */
ULONG
Lgi_DS_QosServiceFlow_Synchronize
    (
        ANSC_HANDLE                 hInsContext
    );

BOOL
Lgi_DS_QosServiceFlow_IsUpdated
    (
        ANSC_HANDLE                 hInsContext
    );

ULONG
Lgi_DS_QosServiceFlow_GetEntryCount
    (
        ANSC_HANDLE                 hInsContext
    );

ANSC_HANDLE
Lgi_DS_QosServiceFlow_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    );

//Paramset API's
ULONG
Lgi_DS_QosParamSet_GetEntryCount
    (
         ANSC_HANDLE                 hInsContext
    );

ANSC_HANDLE
Lgi_DS_QosParamSet_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    );

/* Comman GET param API's for Upstream and Downstream Service */
BOOL
Lgi_QosServiceFlow_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      puLong
    );

BOOL
Lgi_QosParamSet_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      puLong
    );

#endif


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

#ifndef  _COSA_LGI_CABLEMEDOM_INTERNAL_H
#define  _COSA_LGI_CABLEMODEM_INTERNAL_H

#include "cosa_apis.h"
#include "plugin_main_apis.h"
#include "cosa_lgi_cablemodem_apis.h"
#include "cosa_x_cisco_com_cablemodem_apis.h"

#define  COSA_DATAMODEL_LGI_CABLEMODEM_CLASS_CONTENT    \
    /* duplication of the base object class content */ \
    COSA_BASE_CONTENT                                  \
    ULONG              UpstreamChannelNumber;          \
    PCOSA_CM_US_CHANNEL    pUpstreamChannel;           \
    ULONG              UpstreamChannelUpdateTime;      \
                  

#define  COSA_DATAMODEL_LGI_CABLEMODEM_CLASS_CONTENT_QOS   \
    /* duplication of the base object class content */     \
    COSA_BASE_CONTENT                                      \
    uint32_t                pServiceFlowCount;             \
    uint32_t                pServiceParamCount;            \
    cm_ds_qos_sflow_t*      pServiceFlowChannel;           \
    ULONG                   ServiceFlowUpdateTime;         \
    cm_ds_qos_paramset_t*   pSfParamset;                   \
    ULONG                   SfParamUpdateTime;             \
    uint32_t                pServiceUsFlowCount;           \
    uint32_t                pServiceDsFlowCount;           \
    uint32_t                pServiceUsParamCount;          \
    uint32_t                pServiceDsParamCount;          \
    cm_lgi_qos_sflow_t*     pServiceUsFlowChannel;         \
    cm_lgi_qos_sflow_t*     pServiceDsFlowChannel;         \
    cm_lgi_qos_paramset_t*  pSfUsParamset;                 \
    cm_lgi_qos_paramset_t*  pSfDsParamset;                 \
    ULONG                   ServiceUsFlowUpdateTime;       \
    ULONG                   ServiceDsFlowUpdateTime;       \


typedef  struct
_COSA_DATAMODEL_LGI_CABLEMODEM_CLASS_CONTENT
{
    COSA_DATAMODEL_LGI_CABLEMODEM_CLASS_CONTENT
    /* start of LgiCableModem object class content */
}
COSA_DATAMODEL_LGI_CABLEMODEM, *PCOSA_DATAMODEL_LGI_CABLEMODEM;

typedef  struct
_COSA_DATAMODEL_LGI_CABLEMODEM_CLASS_CONTENT_QOS
{
    COSA_DATAMODEL_LGI_CABLEMODEM_CLASS_CONTENT_QOS
    /* start of LgiCableModem object class content */
}
COSA_DATAMODEL_LGI_CABLEMODEM_QOS, *PCOSA_DATAMODEL_LGI_CABLEMODEM_QOS;

/*
    Standard function declaration
*/
ANSC_HANDLE
CosaLgiCableModemCreate
    (
        VOID
    );

ANSC_STATUS
CosaLgiCableModemInitialize
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
CosaLgiCableModemRemove
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_HANDLE
CosaLgiCableModemQosCreate
    (
        VOID
    );

ANSC_STATUS
CosaLgiCableModemQosInitialize
    (
        ANSC_HANDLE                 hThisObject
    );

ANSC_STATUS
CosaLgiCableModemQosRemove
    (
        ANSC_HANDLE                 hThisObject
    );

#endif


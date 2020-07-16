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

#ifndef  _COSA_LGI_CABLEMODEM_APIS_H
#define  _COSA_LGI_CABLEMODEM_APIS_H

#include "../middle_layer_src/cosa_apis.h"

#define DOWNSTREAM_INDEX 1
#define UPSTREAM_INDEX   2

typedef enum
{
    DOCSIS_CM_STAT_PARAMS_OTHER = 1,
    DOCSIS_CM_STAT_PARAMS_NOT_READY = 2,
    DOCSIS_CM_STAT_PARAMS_NOT_SYNCHRONIZED = 3,
    DOCSIS_CM_STAT_PARAMS_PHY_SYNCHRONIZED = 4,
    DOCSIS_CM_STAT_PARAMS_US_PARAMETERS_ACQUIRED = 5,
    DOCSIS_CM_STAT_PARAMS_RANGING_COMPLETE = 6,  
    DOCSIS_CM_STAT_PARAMS_DHCPV4_COMPLETE = 7,
    DOCSIS_CM_STAT_PARAMS_TOD_ESTABLISHED = 8,
    DOCSIS_CM_STAT_PARAMS_SECURITY_ESTABLISHED = 9,
    DOCSIS_CM_STAT_PARAMS_CONFIG_FILE_DOWNLOAD_COMPLETE = 10,
    DOCSIS_CM_STAT_PARAMS_REGISTRATION_COMPLETE = 11,
    DOCSIS_CM_STAT_PARAMS_OPERATIONAL = 12,
    DOCSIS_CM_STAT_PARAMS_ACCESS_DENIED = 13,
    DOCSIS_CM_STAT_PARAMS_EAE_IN_PROGRESS = 14,
    DOCSIS_CM_STAT_PARAMS_DHCPV4_IN_PROGRESS = 15,
    DOCSIS_CM_STAT_PARAMS_DHCPV6_IN_PROGRESS = 16,
    DOCSIS_CM_STAT_PARAMS_DHCPV6_COMPLETE = 17,
    DOCSIS_CM_STAT_PARAMS_REGISTRATION_IN_PROGRESS = 18,
    DOCSIS_CM_STAT_PARAMS_BPI_INIT  = 19,
    DOCSIS_CM_STAT_PARAMS_FORWARDING_DISABLED = 20,
    DOCSIS_CM_STAT_PARAMS_DS_TOPOLOGY_RESOLUTION_IN_PROGRESS = 21,
    DOCSIS_CM_STAT_PARAMS_RANGING_IN_PROGRESS = 22,
    DOCSIS_CM_STAT_PARAMS_RF_MUTE_ALL = 23
} CmMacParamsStatus_e;

typedef enum
{
    UNESTABLISHED = 1,
    ESTABLISHED
}TodStatus_e;

typedef struct cm_ds_qos_sflow_t {
    int32_t FlowSID;
    int32_t FlowDirection;
} cm_ds_qos_sflow_t;

typedef struct cm_ds_qos_paramset_t {
    int32_t SFID;
    int32_t MaxTrafficRate;
    int32_t MaxTrafficBurst;
    int32_t MinReservedRate;
    int32_t MaxConcatBurst;
    int32_t SchedulingType;
} cm_ds_qos_paramset_t;

/* Used to get Service Flow and Paramset for both upstream and downstream */
typedef struct cm_lgi_qos_sflow_t {
    int32_t FlowSID;
    int32_t FlowDirection;
} cm_lgi_qos_sflow_t;

typedef struct cm_lgi_qos_paramset_t {
    int32_t SFID;
    int32_t MaxTrafficRate;
    int32_t MaxTrafficBurst;
    int32_t MinReservedRate;
    int32_t MaxConcatBurst;
    int32_t SchedulingType;
} cm_lgi_qos_paramset_t;

/**********************************************************************
                FUNCTION PROTOTYPES
**********************************************************************/

ANSC_STATUS
CosaDmlGiGetCmDoc30SwRegistrationState
(
    ANSC_HANDLE                 hContext,
    ULONG                       *pValue
);

ANSC_STATUS
CosaDmlGiGetT1Timeouts
(
    ANSC_HANDLE                 hContext,
    ULONG                       *pValue
);

ANSC_STATUS
CosaDmlGiGetHorizOvertempProtModeState
(
    ANSC_HANDLE                 hContext,
    ULONG                       *pValue
);

ANSC_STATUS
CosaDmlGiGetLgiCMStatus
(
    ANSC_HANDLE                 hContext,
    ULONG                       *pValue
);

ANSC_STATUS
CosaDmlGiGetLgiSoftwareOperStatus
(
    ANSC_HANDLE                 hContext,
    ULONG                       *pValue
);

ANSC_STATUS
CosaDmlGiGetLgiToDStatus
(
    ANSC_HANDLE                 hContext,
    ULONG                       *pValue
);

ANSC_STATUS
CosaDmlGiGetLgiEnergyMgtOperStatus
(
    ANSC_HANDLE                 hContext,
    ULONG                       *pValue
);

ANSC_STATUS
CosaDmlGiGetPartServiceFallback20
(
    ANSC_HANDLE                 hContext,
    ULONG                       *pValue
);

ANSC_STATUS 
CosaDmlGiGetQosServiceflow
(
    int serviceFlowCount, 
    cm_lgi_qos_sflow_t **serviceFlowChannel
);

ANSC_STATUS CosaDmlGiGetQosServiceflowParamset
(
    int serviceFlowCount,
    cm_lgi_qos_sflow_t **serviceFlowChannel,
    cm_lgi_qos_paramset_t **serviceFlowParamset
);

ANSC_STATUS
CosaDmlGiGetLgiDownstreamPrimaryChannelID
(
    ANSC_HANDLE                 hContext,
    ULONG                       *pValue
);
#endif


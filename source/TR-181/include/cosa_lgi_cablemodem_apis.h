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
#include "cm_hal.h"

#define DOWNSTREAM_INDEX 1
#define UPSTREAM_INDEX   2

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

ANSC_STATUS
CosaDmlGiGetOFDMChannelDetails
(
    uint32_t                    ds_ofdm_count,
    cm_ds_ofdm_chan_t           *ofdmChan
);

ANSC_STATUS
CosaDmlGiGetOFDMAChannelDetails
(
    uint32_t                   us_ofdma_count,
    cm_us_ofdma_chan_t         *ofdmaChan  
);
#endif


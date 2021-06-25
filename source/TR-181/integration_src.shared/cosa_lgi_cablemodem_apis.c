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

#include "cosa_lgi_cablemodem_apis.h"
#include "cosa_x_cisco_com_cablemodem_apis.h"

/*
   Warning: include cm_hal.h after the cosa_*.h headers above to avoid build
   failures due to definition of BOOLEAN from both ansc_platform.h (which
   defines it via a typedef) and cm_hal.h (which defines it via #define).
   Fixme: this needs a bigger cleanup...
*/
#include <cm_hal.h>

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetCmDoc30SwRegistrationState(ANSC_HANDLE hContext,
        ULONG *pValue)                                       
 **************************************************************************
 *  \brief get CM registration status: docsis-DownstreamScanning(1),
 *         docsis-DownstreamRanging(2), docsis-UpstreamRanging(3),
 *         docsis-DHCP(4),docsis-TFTP(5),docsis-DataRegComplete(6)
 *  \param[in] hContext
 *  \param[out] pValue
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS
CosaDmlGiGetCmDoc30SwRegistrationState
    (
        ANSC_HANDLE                 hContext,
        ULONG                       *pValue
    )
{
    int swRegState = CM_REGSTATE_UNKNOWN;

    if ((pValue == NULL) || (docsis_getCmDoc30SwRegistrationState(&swRegState) != RETURN_OK))
    {
        return ANSC_STATUS_FAILURE;
    }

    *pValue = (ULONG)swRegState;

    return ANSC_STATUS_SUCCESS;
}

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetT1Timeouts(ANSC_HANDLE hContext,
        ULONG *pValue)                                       
 **************************************************************************
 *  \brief get CM T1 Timeout: 
 *  \param[in] hContext
 *  \param[out] pValue
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS
CosaDmlGiGetT1Timeouts
    (
        ANSC_HANDLE                 hContext,
        ULONG                       *pValue
    )
{
    int timeouts = 0;

    if ((pValue == NULL) || (docsis_getCmT1Timeouts(&timeouts) != RETURN_OK))
    {
        return ANSC_STATUS_FAILURE;
    }
    *pValue = (ULONG)timeouts;

    return ANSC_STATUS_SUCCESS;
}

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetHorizOvertempProtModeState(ANSC_HANDLE hContext,
        ULONG *pValue)                                       
 **************************************************************************
 *  \brief To indicate whether the CM is currently operating in over 
 *         temperature protected mode.
 *  \param[in] hContext
 *  \param[out] pValue
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS
CosaDmlGiGetHorizOvertempProtModeState
    (
        ANSC_HANDLE                 hContext,
        ULONG                       *pValue
    )
{
    int hotStatus = 0;
    
    if ((pValue == NULL) || (docsis_getHorizOvertempProtModeState(&hotStatus) != RETURN_OK))
    {
        AnscTraceWarning(("Processing failed  %s, %d\n", __FUNCTION__, __LINE__));
        return ANSC_STATUS_FAILURE;
    }

    /*Temperature status :Normal(0),Too high(1)*/
    *pValue = (ULONG)hotStatus;
    
    return ANSC_STATUS_SUCCESS;
}

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetLgiCMStatus(ANSC_HANDLE hContext,
        ULONG *pValue)                                       
 **************************************************************************
 *  \brief get CM operation status
 *  \param[in] hContext
 *  \param[out] pValue
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS
CosaDmlGiGetLgiCMStatus
    (
        ANSC_HANDLE                 hContext,
        ULONG                       *pValue
    )
{
    int retVal = ANSC_STATUS_SUCCESS;
    int cmStatus = 0;

    if ((pValue == NULL) || (docsis_getCMOperationStatus(&cmStatus) != RETURN_OK))
    {
        AnscTraceWarning(("Processing failed  %s, %d\n", __FUNCTION__, __LINE__));
        return ANSC_STATUS_FAILURE;
    }

    *pValue = (ULONG)cmStatus;

    return retVal;
}

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetLgiSoftwareOperStatus(ANSC_HANDLE hContext,
        ULONG *pValue)                                       
 **************************************************************************
 *  \brief get CM software operation status
 *  \param[in] hContext
 *  \param[out] pValue
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS
CosaDmlGiGetLgiSoftwareOperStatus
    (
        ANSC_HANDLE                 hContext,
        ULONG                       *pValue
    )
{
    int swOperStatus = 0;

    if ((pValue == NULL) || (cm_getSoftwareOperStatus(&swOperStatus) != RETURN_OK))
    {
        AnscTraceWarning(("Processing failed  %s, %d\n", __FUNCTION__, __LINE__));
        return ANSC_STATUS_FAILURE;
    }
    *pValue = (ULONG)swOperStatus;

    return ANSC_STATUS_SUCCESS;
}

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetLgiToDStatus(ANSC_HANDLE hContext,
        ULONG *pValue)                                       
 **************************************************************************
 *  \brief get CM ToD status
 *  \param[in] hContext
 *  \param[out] pValue
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS
CosaDmlGiGetLgiToDStatus
    (
        ANSC_HANDLE                 hContext,
        ULONG                       *pValue
    )
{
    TodStatus_e todStatus = UNESTABLISHED;
    COSA_CM_DOCSIS_INFO   DInfo;
    memset(&DInfo, 0, sizeof(DInfo));

    if ((pValue == NULL) || (CosaDmlCMGetDOCSISInfo(NULL, &DInfo) != ANSC_STATUS_SUCCESS))
    {
        AnscTraceWarning(("Processing failed  %s, %d\n", __FUNCTION__, __LINE__));
        return ANSC_STATUS_FAILURE;
    }

    if (strcmp(DInfo.ToDStatus, "Complete") == 0)
    {
        todStatus = ESTABLISHED;
    }

    *pValue = (ULONG)todStatus;

    return ANSC_STATUS_SUCCESS;
}

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetLgiEnergyMgtOperStatus(ANSC_HANDLE hContext,
        ULONG *pValue)                                       
 **************************************************************************
 *  \brief Get CM Energy Management Mode. 
 *         Disabled(0),1x1(1)
 *  \param[in] hContext
 *  \param[out] pValue
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS
CosaDmlGiGetLgiEnergyMgtOperStatus
    (
        ANSC_HANDLE                 hContext,
        ULONG                       *pValue
    )
{
    int energyMgtOperStatus = 0;
    
    if ((pValue == NULL) || (docsis_getEnergyMode(&energyMgtOperStatus) != RETURN_OK))
    {
        AnscTraceWarning(("Processing failed  %s, %d\n", __FUNCTION__, __LINE__));
        return ANSC_STATUS_FAILURE;
    }
    *pValue = (ULONG)energyMgtOperStatus;

    return ANSC_STATUS_SUCCESS;
}

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetPartServiceFallback20(ANSC_HANDLE hContext,
        ULONG *pValue)                                       
 **************************************************************************
 *  \brief get CM Partial service fallback
 *  \param[in] hContext
 *  \param[out] pValue
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS
CosaDmlGiGetPartServiceFallback20
    (
        ANSC_HANDLE                 hContext,
        ULONG                       *pValue
    )
{
    int partServiceFallback = 0;
    
    if ((pValue == NULL) || (docsis_getPartServiceFallback20(&partServiceFallback) != RETURN_OK))
    {
        AnscTraceWarning(("Processing failed  %s, %d\n", __FUNCTION__, __LINE__));
        return ANSC_STATUS_FAILURE;
    }
    *pValue = (ULONG)partServiceFallback;

    return ANSC_STATUS_SUCCESS;
}

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetQosServiceflow (int serviceFlowCount,
    cm_lgi_qos_sflow_t **serviceFlowChannel)                     
 **************************************************************************
 *  \brief get QoS service flow
 *  \param[in] serviceFlowCount
 *  \param[out] serviceFlowChannel
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS CosaDmlGiGetQosServiceflow
(
    int serviceFlowCount,
    cm_lgi_qos_sflow_t **serviceFlowChannel
)
{
    int32_t sf_index;
    int32_t flow_sid, direction;
    int rc;
    ANSC_STATUS result = ANSC_STATUS_SUCCESS;
    cm_lgi_qos_sflow_t *sfChannel=*serviceFlowChannel;

    for (sf_index = 0; sf_index < serviceFlowCount; sf_index++)
    {       
        rc = qos_getServiceFlowParam(sf_index,&flow_sid,&direction);
        if(rc == RETURN_OK)
        {
            if(sfChannel)
            {
                sfChannel->FlowSID = flow_sid;
                sfChannel->FlowDirection = direction;
            }
            sfChannel++;
        }    
        else
        {
            result = ANSC_STATUS_FAILURE;
            break;
        }
    }
    return result;
}

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetQosServiceflowParamset (int serviceFlowCount,
    cm_lgi_qos_sflow_t **serviceFlowChannel,cm_lgi_qos_paramset_t **serviceFlowParamset)                     
 **************************************************************************
 *  \brief get QoS service flow parameter set
 *  \param[in] serviceFlowCount
 *             serviceFlowChannel
 *  \param[out] serviceFlowParamset
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS CosaDmlGiGetQosServiceflowParamset
(
    int serviceFlowCount,
    cm_lgi_qos_sflow_t **serviceFlowChannel,
    cm_lgi_qos_paramset_t **serviceFlowParamset
)
{
    int sf_index;
    int sf_id;
    int MaxTrafficRate, MaxTrafficBurst, MinReservedRate, MaxConcatBurst, SchedulingType;
    int status;
    ANSC_STATUS result = ANSC_STATUS_SUCCESS;
    cm_lgi_qos_paramset_t *sfParamSet = *serviceFlowParamset;
    cm_lgi_qos_sflow_t *sfChannel=*serviceFlowChannel;
    if(sfChannel==NULL || sfParamSet==NULL)
    {
        return ANSC_STATUS_FAILURE;
    }

    for (sf_index = 0; sf_index < serviceFlowCount; sf_index++)
    {
        if(sfChannel)
        {
            sf_id = sfChannel->FlowSID;
            MaxTrafficRate = MaxTrafficBurst = MinReservedRate = MaxConcatBurst = SchedulingType = 0;
            status = qos_getServiceFlowParamsetDetails(sf_id, &MaxTrafficRate, &MaxTrafficBurst, &MinReservedRate, &MaxConcatBurst, &SchedulingType);
            if (RETURN_OK == status)
            {
                if(sfParamSet)
                {
                    sfParamSet->SFID = sf_id;
                    sfParamSet->MaxTrafficRate = MaxTrafficRate;
                    sfParamSet->MaxTrafficBurst = MaxTrafficBurst;
                    sfParamSet->MaxConcatBurst = MaxConcatBurst;
                    sfParamSet->MinReservedRate = MinReservedRate;
                    sfParamSet->SchedulingType = SchedulingType;
                    sfParamSet++; 
                }
            }
            else
            {
                result = ANSC_STATUS_FAILURE;
                break;
            }
            sfChannel++;       
        }
    }
    return result;
}

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetLgiDownstreamPrimaryChannelID(ANSC_HANDLE hContext,
        ULONG *pValue)                                       
 **************************************************************************
 *  \brief get downstream primary channel ID
 *  \param[in] hContext
 *  \param[out] pValue
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS
CosaDmlGiGetLgiDownstreamPrimaryChannelID
    (
        ANSC_HANDLE                 hContext,
        ULONG                       *pValue
    )
{
    int downstreamPriChannelId = 0;

    if ((pValue == NULL) || (docsis_getDownstreamPrimaryChannelID(&downstreamPriChannelId) != RETURN_OK))
    {
        AnscTraceWarning(("Processing failed  %s, %d\n", __FUNCTION__, __LINE__));
        return ANSC_STATUS_FAILURE;
    }
    *pValue = (ULONG)downstreamPriChannelId;

    return ANSC_STATUS_SUCCESS;
}

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetT2Timeouts(ANSC_HANDLE hContext,
        ULONG *pValue)
 **************************************************************************
 *  \brief get CM T2 Timeouts
 *  \param[in] hContext
 *  \param[out] pValue
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS
CosaDmlGiGetT2Timeouts
    (
        ANSC_HANDLE                 hContext,
        ULONG                       *pValue
    )
{
    int timeouts = 0;

    if ((pValue == NULL) || (docsis_getCmT2Timeouts(&timeouts) != ANSC_STATUS_SUCCESS))
    {
        return ANSC_STATUS_FAILURE;
    }
    *pValue = (ULONG)timeouts;

    return ANSC_STATUS_SUCCESS;
}

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetOFDMChannelDetails(uint32_t ds_ofdm_count,
        cm_ds_ofdm_chan_t *ofdmChan)
 **************************************************************************
 *  \brief get ODFM Channel Details
 *  \param[in] ds_ofdm_count
 *  \param[in] ofdmChan
 *  \param[out] ofdmChan
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS CosaDmlGiGetOFDMChannelDetails (uint32_t ds_ofdm_count, cm_ds_ofdm_chan_t *ofdmChan)
{
    int st;

    if ( ds_ofdm_count <= 0 || ofdmChan == NULL )
    {
        return ANSC_STATUS_FAILURE;
    }

    st = docsis_getDsOFDMChannelDetails (ds_ofdm_count, ofdmChan);

    return (st == RETURN_OK) ? ANSC_STATUS_SUCCESS : ANSC_STATUS_FAILURE;
}

/**************************************************************************/
/*! \fn ANSC_STATUS CosaDmlGiGetOFDMAChannelDetails(uint32_t us_ofdma_count,
        cm_us_ofdma_chan_t *ofdmaChan)
 **************************************************************************
 *  \brief get ODFM Channel Details
 *  \param[in] us_ofdma_count
 *  \param[in] ofdmaChan
 *  \param[out] ofdmaChan
 *  \return STATUS
 **************************************************************************/
ANSC_STATUS CosaDmlGiGetOFDMAChannelDetails (uint32_t us_ofdma_count, cm_us_ofdma_chan_t *ofdmaChan)
{
    int st;

    if ( us_ofdma_count <= 0 || ofdmaChan == NULL )
    {
        return ANSC_STATUS_FAILURE;
    }

    st = docsis_getUsOFDMAChannelDetails (us_ofdma_count, ofdmaChan);

    return (st == RETURN_OK) ? ANSC_STATUS_SUCCESS : ANSC_STATUS_FAILURE;
}


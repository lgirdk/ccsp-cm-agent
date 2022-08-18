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

#include "ansc_platform.h"
#include "cosa_lgi_cablemodem_apis.h"
#include "cosa_lgi_cablemodem_dml.h"
#include "cosa_lgi_cablemodem_internal.h"
#include "cosa_x_cisco_com_cablemodem_internal.h"

extern PCOSA_DATAMODEL_LGI_CABLEMODEM g_pLgiCM;
extern PCOSA_DATAMODEL_LGI_CABLEMODEM_QOS Lgi_QosSF;

extern int Ccsp_cm_clnt_lock(void);
extern int Ccsp_cm_clnt_unlock(void);

#define CM_REFRESH_INTERVAL                    20
#define TIME_NO_NEGATIVE(x) ((long)(x) < 0 ? 0 : (x))

/***********************************************************************
 IMPORTANT NOTE:

 According to TR69 spec:
 On successful receipt of a SetParameterValues RPC, the CPE MUST apply
 the changes to all of the specified Parameters atomically. That is, either
 all of the value changes are applied together, or none of the changes are
 applied at all. In the latter case, the CPE MUST return a fault response
 indicating the reason for the failure to apply the changes.

 The CPE MUST NOT apply any of the specified changes without applying all
 of them.

 In order to set parameter values correctly, the back-end is required to
 hold the updated values until "Validate" and "Commit" are called. Only after
 all the "Validate" passed in different objects, the "Commit" will be called.
 Otherwise, "Rollback" will be called instead.

 The sequence in COSA Data Model will be:

 SetParamBoolValue/SetParamIntValue/SetParamUlongValue/SetParamStringValue
 -- Backup the updated values;

 if( Validate_XXX())
 {
     Commit_XXX();    -- Commit the update all together in the same object
 }
 else
 {
     Rollback_XXX();  -- Remove the update at backup;
 }

***********************************************************************/
/***********************************************************************

 APIs for Object:

    CableModemInfo.

    *  LgiCableModem_GetParamBoolValue
    *  LgiCableModem_GetParamIntValue
    *  LgiCableModem_GetParamUlongValue
    *  LgiCableModem_GetParamStringValue
    *  LgiCableModem_SetParamBoolValue

***********************************************************************/
/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL
        LgiCableModem_GetParamBoolValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                BOOL*                       pBool
            );

    description:

        This function is called to retrieve Boolean parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                BOOL*                       pBool
                The buffer of returned boolean value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
LgiCableModem_GetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL*                       pBool
    )
{
    /* CcspTraceWarning(("Unsupported parameter '%s'\n", ParamName)); */
    return FALSE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL
        LgiCableModem_GetParamIntValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                int*                        pInt
            );

    description:

        This function is called to retrieve integer parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                int*                        pInt
                The buffer of returned integer value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
LgiCableModem_GetParamIntValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        int*                        pInt
    )
{
    /* CcspTraceWarning(("Unsupported parameter '%s'\n", ParamName)); */
    return FALSE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL
        LgiCableModem_GetParamUlongValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                ULONG*                      puLong
            );

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
LgiCableModem_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      puLong
    )
{
    /* check the parameter name and return the corresponding value */
    if (strcmp(ParamName, "CmDoc30SwRegistrationState") == 0)
    {
        CosaDmlGiGetCmDoc30SwRegistrationState(NULL, puLong);
        return TRUE;
    }
    if (strcmp(ParamName, "T1Timeouts") == 0)
    {
        if (ANSC_STATUS_SUCCESS != CosaDmlGiGetT1Timeouts(NULL, puLong))
        {
            *puLong = 0;
        }
        return TRUE;
    }
    if (strcmp(ParamName, "T2Timeouts") == 0)
    {
        if (ANSC_STATUS_SUCCESS != CosaDmlGiGetT2Timeouts(NULL, puLong))
        {
            *puLong = 0;
        }
        return TRUE;
    }
    if (strcmp(ParamName, "CMStatus") == 0)
    {
        if (ANSC_STATUS_SUCCESS != CosaDmlGiGetLgiCMStatus(NULL, puLong))
        {
            *puLong = 0;
        }
        return TRUE;
    }
    if (strcmp(ParamName, "SoftwareOperStatus") == 0)
    {
        if (ANSC_STATUS_SUCCESS != CosaDmlGiGetLgiSoftwareOperStatus(NULL, puLong))
        {
            *puLong = 0;
        }
        return TRUE;
    }
    if (strcmp(ParamName, "ToDStatus") == 0)
    {
        if (ANSC_STATUS_SUCCESS != CosaDmlGiGetLgiToDStatus(NULL, puLong))
        {
            *puLong = 0;
        }
        return TRUE;
    }

    if (strcmp(ParamName, "OvertempProtModeState") == 0)
    {
        if (ANSC_STATUS_SUCCESS != CosaDmlGiGetHorizOvertempProtModeState(NULL, puLong))
        {
            *puLong = 0;
        }
        else
        {
            // status HOT_STATUS_NORMAL is Normal(0) otherwise, its Toohigh(1)
            if (*puLong != 0)
            {
                *puLong = 1;
            }
        }
        return TRUE;
    }

    if (strcmp(ParamName, "EnergyMgtOperStatus") == 0)
    {
        if (ANSC_STATUS_SUCCESS != CosaDmlGiGetLgiEnergyMgtOperStatus(NULL, puLong))
        {
            *puLong = 0;
        }
        return TRUE;
    }
    if (strcmp(ParamName, "PartServiceFallback20") == 0)
    {
        if (ANSC_STATUS_SUCCESS != CosaDmlGiGetPartServiceFallback20(NULL, puLong))
        {
            *puLong = 0;
        }
        return TRUE;
    }
    if (strcmp(ParamName, "DownstreamPrimaryChannelID") == 0)
    {
        if (ANSC_STATUS_SUCCESS != CosaDmlGiGetLgiDownstreamPrimaryChannelID(NULL, puLong))
        {
            *puLong = 0;
        }
        return TRUE;
    }
    if (strcmp(ParamName, "DownstreamPrimaryChannelType") == 0)
    {
        if(CosaDmlGiGetLgiDownstreamPrimaryChannelType(NULL,puLong) != ANSC_STATUS_SUCCESS)
        {
            *puLong = 0;
        }
        return TRUE;
    }
    /* CcspTraceWarning(("Unsupported parameter '%s'\n", ParamName)); */
    return FALSE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        LgiCableModem_GetParamStringValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                char*                       pValue,
                ULONG*                      pUlSize
            );

    description:

        This function is called to retrieve string parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                char*                       pValue,
                The string value buffer;

                ULONG*                      pUlSize
                The buffer of length of string value;
                Usually size of 1023 will be used.
                If it's not big enough, put required size here and return 1;

    return:     0 if succeeded;
                1 if short of buffer size; (*pUlSize = required size)
                -1 if not supported.

**********************************************************************/
ULONG
LgiCableModem_GetParamStringValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        char*                       pValue,
        ULONG*                      pulSize
    )
{
    /* CcspTraceWarning(("Unsupported parameter '%s'\n", ParamName)); */
    return -1;
}

BOOL
LgiCableModem_SetParamBoolValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        BOOL                        pBool
    )
{
    return FALSE;
}

BOOL
LgiCableModem_SetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG                       vUlong
    )
{
    return FALSE;
}

BOOL
LgiCableModem_Validate
    (
        ANSC_HANDLE                 hInsContext,
        char*                       pReturnParamName,
        ULONG*                      puLength
    )
{
    return TRUE;
}

ULONG
LgiCableModem_Commit
    (
        ANSC_HANDLE                 hInsContext
    )
{
    return 0;
}

ULONG
LgiCableModem_Rollback
    (
        ANSC_HANDLE                 hInsContext
    )
{
    return 0;
}

/***********************************************************************
 APIs for Object:

    X_LGI-COM_CableModem.OfdmChannel.{i}.

    *  LgiOfdmChannel_GetEntryCount
    *  LgiOfdmChannel_GetEntry
    *  LgiOfdmChannel_IsUpdated
    *  LgiOfdmChannel_Synchronize
    *  LgiOfdmChannel_GetParamUlongValue
    *  LgiOfdmChannel_GetParamStringValue
***********************************************************************/

ULONG LgiOfdmChannel_GetEntryCount ( ANSC_HANDLE hInsContext )
{
    if (g_pLgiCM != NULL)
    {
        return g_pLgiCM->OfdmChannelNumber;
    }

    return 0;
}

ANSC_HANDLE LgiOfdmChannel_GetEntry ( ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber )
{
    if (g_pLgiCM != NULL)
    {
        if (nIndex < g_pLgiCM->OfdmChannelNumber)
        {
            *pInsNumber  = nIndex + 1;
            return &g_pLgiCM->pOfdmChannel[nIndex];
        }
    }

    return NULL; /* return the handle */
}

BOOL LgiOfdmChannel_IsUpdated ( ANSC_HANDLE hInsContext )
{
    if (g_pLgiCM == NULL)
    {
        return FALSE;
    }

    if ( !g_pLgiCM->OfdmChannelUpdateTime )
    {
        g_pLgiCM->OfdmChannelUpdateTime = AnscGetTickInSeconds();

        return TRUE;
    }

    if ( g_pLgiCM->OfdmChannelUpdateTime >= TIME_NO_NEGATIVE(AnscGetTickInSeconds() - CM_REFRESH_INTERVAL) )
    {
        return FALSE;
    }
    else
    {
        g_pLgiCM->OfdmChannelUpdateTime = AnscGetTickInSeconds();

        return TRUE;
    }
}

ULONG LgiOfdmChannel_Synchronize ( ANSC_HANDLE hInsContext )
{
    int ret = -1;
     
    if (g_pLgiCM == NULL)
    {
        return -1;
    }

    Ccsp_cm_clnt_lock();

    if ( g_pLgiCM->pOfdmChannel )
    {
        AnscFreeMemory(g_pLgiCM->pOfdmChannel);
        g_pLgiCM->pOfdmChannel = NULL;
    }

    ret = docsis_getDsOFDMChannelCount(&g_pLgiCM->OfdmChannelNumber);

    if ((!ret) && (g_pLgiCM->OfdmChannelNumber > 0))
    {
        g_pLgiCM->pOfdmChannel = AnscAllocateMemory( sizeof(cm_ds_ofdm_chan_t) * g_pLgiCM->OfdmChannelNumber );
    }

    if (NULL != g_pLgiCM->pOfdmChannel)
    {
        ret = CosaDmlGiGetOFDMChannelDetails(g_pLgiCM->OfdmChannelNumber, g_pLgiCM->pOfdmChannel);
        if ( ret )
        {
            AnscFreeMemory(g_pLgiCM->pOfdmChannel);
            g_pLgiCM->pOfdmChannel = NULL;
            g_pLgiCM->OfdmChannelNumber = 0;
        }
    }
    
    Ccsp_cm_clnt_unlock();

    return 0;
}

BOOL LgiOfdmChannel_GetParamUlongValue ( ANSC_HANDLE hInsContext, char *ParamName, ULONG *puLong )
{
    cm_ds_ofdm_chan_t *pConf = (cm_ds_ofdm_chan_t *) hInsContext;

    if (strcmp(ParamName, "ChannelID") == 0)
    {
        *puLong = pConf->channelID;
        return TRUE;
    }

    if (strcmp(ParamName, "ChannelWidth") == 0)
    {
        *puLong = pConf->channelWidth;
        return TRUE;
    }

    if (strcmp(ParamName, "NumActiveSubcarrier") == 0)
    {
        *puLong = pConf->numActSubcarrier;
        return TRUE;
    }

    if (strcmp(ParamName, "FirstActiveSubcarrier") == 0)
    {
        *puLong = pConf->firstActSubcarrier;
        return TRUE;
    }

    if (strcmp(ParamName, "LastActiveSubcarrier") == 0)
    {
        *puLong = pConf->lastActSubcarrier;
        return TRUE;
    }

    if (strcmp(ParamName, "PilotScAvgMer") == 0)
    {
        *puLong = pConf->pilotScAvgMer;
        return TRUE;
    }

    if (strcmp(ParamName, "PlcScAvgMer") == 0)
    {
        *puLong = pConf->plcScAvgMer;
        return TRUE;
    }

    if (strcmp(ParamName, "DataScAvgMer") == 0)
    {
        *puLong = pConf->dataScAvgMer;
        return TRUE;
    }

    if (strcmp(ParamName, "LockStatus") == 0)
    {
        *puLong = pConf->lockStatus;
        return TRUE;
    }

    if (strcmp(ParamName, "FftType") == 0)
    {
        *puLong = pConf->fftType;
        return TRUE;
    }

    if (strcmp(ParamName, "Modulation") == 0)
    {
        *puLong = pConf->modulation_high;
        return TRUE;
    }

    if (strcmp(ParamName, "Correcteds") == 0)
    {
        *puLong = pConf->correcteds;
        return TRUE;
    }

    if (strcmp(ParamName, "Uncorrectables") == 0)
    {
        *puLong = pConf->uncorrectables;
        return TRUE;
    }

    /* CcspTraceWarning(("Unsupported parameter '%s'\n", ParamName)); */
    return FALSE;
}

static format_result_float (char *pValue, ULONG *pUlSize, float value)
{
    int len;
    char pVal[32];

    len = snprintf (pVal, sizeof(pVal), "%.1f", value);

    if ( len >= *pUlSize )
    {
	*pUlSize = len + 1;
	return 1;
    }

    memcpy (pValue, pVal, len + 1);

    return 0;
}

ULONG LgiOfdmChannel_GetParamStringValue ( ANSC_HANDLE hInsContext, char* ParamName, char *pValue, ULONG *pUlSize )
{
    cm_ds_ofdm_chan_t *pConf = (cm_ds_ofdm_chan_t *) hInsContext;

    if (strcmp(ParamName, "PowerLevel") == 0)
    {
        return format_result_float (pValue, pUlSize, pConf->power);
    }

    /* CcspTraceWarning(("Unsupported parameter '%s'\n", ParamName)); */
    return -1;
}

/***********************************************************************
 APIs for Object:

    X_LGI-COM_CableModem.OfdmaChannel.{i}.

    *  LgiOfdmaChannel_GetEntryCount
    *  LgiOfdmaChannel_GetEntry
    *  LgiOfdmaChannel_IsUpdated
    *  LgiOfdmaChannel_Synchronize
    *  LgiOfdmaChannel_GetParamUlongValue
    *  LgiOfdmaChannel_GetParamStringValue
***********************************************************************/

ULONG LgiOfdmaChannel_GetEntryCount ( ANSC_HANDLE hInsContext )
{
    if (g_pLgiCM != NULL)
    {
        return g_pLgiCM->OfdmaChannelNumber;
    }

    return 0;
}

ANSC_HANDLE LgiOfdmaChannel_GetEntry ( ANSC_HANDLE hInsContext, ULONG nIndex, ULONG* pInsNumber )
{
    if (g_pLgiCM != NULL)
    {
        if (nIndex < g_pLgiCM->OfdmaChannelNumber)
        {
            *pInsNumber  = nIndex + 1;
            return &g_pLgiCM->pOfdmaChannel[nIndex];
        }
    }

    return NULL; /* return the handle */
}

BOOL LgiOfdmaChannel_IsUpdated ( ANSC_HANDLE hInsContext )
{
    if (g_pLgiCM == NULL)
    {
        return FALSE;
    }

    if ( !g_pLgiCM->OfdmaChannelUpdateTime )
    {
        g_pLgiCM->OfdmaChannelUpdateTime = AnscGetTickInSeconds();

        return TRUE;
    }

    if ( g_pLgiCM->OfdmaChannelUpdateTime >= TIME_NO_NEGATIVE(AnscGetTickInSeconds() - CM_REFRESH_INTERVAL) )
    {
        return FALSE;
    }
    else
    {
        g_pLgiCM->OfdmaChannelUpdateTime = AnscGetTickInSeconds();

        return TRUE;
    }
}

ULONG LgiOfdmaChannel_Synchronize ( ANSC_HANDLE hInsContext )
{
    int ret = -1;

    if (g_pLgiCM == NULL)
    {
        return -1;
    }

    Ccsp_cm_clnt_lock();

    if ( g_pLgiCM->pOfdmaChannel )
    {
        AnscFreeMemory(g_pLgiCM->pOfdmaChannel);
        g_pLgiCM->pOfdmaChannel = NULL;
    }

    ret = docsis_getUsOFDMAChannelCount(&g_pLgiCM->OfdmaChannelNumber);

    if ((!ret) && (g_pLgiCM->OfdmaChannelNumber > 0))
    {
        g_pLgiCM->pOfdmaChannel = AnscAllocateMemory( sizeof(cm_us_ofdma_chan_t) * g_pLgiCM->OfdmaChannelNumber );
    }

    if (NULL != g_pLgiCM->pOfdmaChannel)
    {
        ret = CosaDmlGiGetOFDMAChannelDetails(g_pLgiCM->OfdmaChannelNumber, g_pLgiCM->pOfdmaChannel);
        if ( ret )
        {
            AnscFreeMemory(g_pLgiCM->pOfdmaChannel);
            g_pLgiCM->pOfdmaChannel = NULL;
            g_pLgiCM->OfdmaChannelNumber = 0;
        }
    }

    Ccsp_cm_clnt_unlock();

    return 0;
}

BOOL LgiOfdmaChannel_GetParamUlongValue ( ANSC_HANDLE hInsContext, char *ParamName, ULONG *puLong )
{
    cm_us_ofdma_chan_t *pConf = (cm_us_ofdma_chan_t *) hInsContext;

    if (strcmp(ParamName, "ChannelID") == 0)
    {
        *puLong = pConf->channelID;
        return TRUE;
    }

    if (strcmp(ParamName, "ChannelType") == 0)
    {
        *puLong = pConf->channelType;
        return TRUE;
    }

    if (strcmp(ParamName, "NumActiveSubcarrier") == 0)
    {
        *puLong = pConf->numActSubcarrier;
        return TRUE;
    }

    if (strcmp(ParamName, "LockStatus") == 0)
    {
        /*LockStatus[]: {"FAIL", "RANGING", "SUCCESS", "RANGING" }*/
        *puLong = (pConf->lockStatus == 2) ? 1 : 0;
        return TRUE;
    }

    if (strcmp(ParamName, "FftType") == 0)
    {
        *puLong = pConf->fftType;
        return TRUE;
    }

    if (strcmp(ParamName, "Modulation") == 0)
    {
        *puLong = pConf->modulation;
        return TRUE;
    }

    if (strcmp(ParamName, "T3Timeouts") == 0)
    {
        *puLong = pConf->t3Timeouts;
        return TRUE;
    }

    if (strcmp(ParamName, "T4Timeouts") == 0)
    {
        *puLong = pConf->t4Timeouts;
        return TRUE;
    }

    /* CcspTraceWarning(("Unsupported parameter '%s'\n", ParamName)); */
    return FALSE;
}

ULONG LgiOfdmaChannel_GetParamStringValue ( ANSC_HANDLE hInsContext, char* ParamName, char *pValue, ULONG *pUlSize )
{
    cm_us_ofdma_chan_t *pConf = (cm_us_ofdma_chan_t *) hInsContext;

    if (strcmp(ParamName, "PowerLevel") == 0)
    {
        return format_result_float (pValue, pUlSize, pConf->power);
    }

    if (strcmp(ParamName, "FirstActiveSubcarrier") == 0)
    {
        return format_result_float (pValue, pUlSize, pConf->freqMIN);
    }

    if (strcmp(ParamName, "LastActiveSubcarrier") == 0)
    {
        return format_result_float (pValue, pUlSize, pConf->freqMAX);
    }

    if (strcmp(ParamName, "ChannelWidth") == 0)
    {
        return format_result_float (pValue, pUlSize, pConf->channelWidth);
    }

    /* CcspTraceWarning(("Unsupported parameter '%s'\n", ParamName)); */
    return -1;
}

/***********************************************************************
 APIs for Object:

    X_LGI-COM_CableModem.QosServiceFlow.Upstream{i}.
    *  Lgi_US_QosServiceFlow_IsUpdated
    *  Lgi_US_QosServiceFlow_Synchronize
    *  Lgi_US_QosServiceFlow_GetEntryCount
    *  Lgi_US_QosServiceFlow_GetEntry

    X_LGI-COM_CableModem.QosServiceFlow.Upstream{i}.QosParamSet.{i}
    *  Lgi_US_QosParamSet_GetEntryCount
    *  Lgi_US_QosParamSet_GetEntry
***********************************************************************/
/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL
        Lgi_US_QosServiceFlow_IsUpdated
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/
BOOL
Lgi_US_QosServiceFlow_IsUpdated
    (
        ANSC_HANDLE                 hInsContext
    )
{
    if (NULL == Lgi_QosSF)
    {
        return FALSE;
    }

    if ( !Lgi_QosSF->ServiceUsFlowUpdateTime )
    {
        Lgi_QosSF->ServiceUsFlowUpdateTime = AnscGetTickInSeconds();
        return TRUE;
    }

    if ( Lgi_QosSF->ServiceUsFlowUpdateTime >= TIME_NO_NEGATIVE(AnscGetTickInSeconds() - CM_REFRESH_INTERVAL) )
    {
        return FALSE;
    }
    else
    {
        Lgi_QosSF->ServiceUsFlowUpdateTime = AnscGetTickInSeconds();
        return TRUE;
    }
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        Lgi_US_QosServiceFlow_Synchronize
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG
Lgi_US_QosServiceFlow_Synchronize
    (
        ANSC_HANDLE                 hInsContext
    )
{
    int ret = -1; 

    /* Local Struct use to get the all the data */
    cm_lgi_qos_sflow_t *serviceFlowChannel = (cm_lgi_qos_sflow_t *)NULL;
    uint32_t serviceFlowCount = 0;
    uint32_t serviceUSParamCount = 0;
    uint32_t index = 0, chIndex = 0;

    if ( NULL == Lgi_QosSF )
    {
        return ret;
    }

    Ccsp_cm_clnt_lock();

    /* Clear the previous data */
    if ( Lgi_QosSF->pServiceUsFlowChannel )
    {
        AnscFreeMemory(Lgi_QosSF->pServiceUsFlowChannel);
        Lgi_QosSF->pServiceUsFlowChannel = NULL;
    }

    if ( Lgi_QosSF->pSfUsParamset )
    {
        AnscFreeMemory(Lgi_QosSF->pSfUsParamset);
        Lgi_QosSF->pSfUsParamset = NULL;
    }

    Lgi_QosSF->pServiceUsFlowCount = 0;
    Lgi_QosSF->pServiceUsParamCount  = 0;

    /* Get QOS ServiceFlow and Paramset count */
    ret = qos_getServiceFlowCount(&serviceFlowCount) || qos_getServiceFlowParamCount(&serviceUSParamCount);
    /* Allocate memory for local structure to store QOS Service Flow */
    if ((!ret) && (serviceFlowCount != 0))
    {
        Lgi_QosSF->pServiceUsParamCount = serviceUSParamCount;
        serviceFlowChannel = (cm_lgi_qos_sflow_t*) AnscAllocateMemory( sizeof(cm_lgi_qos_sflow_t) * serviceFlowCount );
        Lgi_QosSF->pSfUsParamset = (cm_lgi_qos_paramset_t*) AnscAllocateMemory( sizeof(cm_lgi_qos_paramset_t) * Lgi_QosSF->pServiceUsParamCount);
        if (NULL != serviceFlowChannel)
        {
            ret = CosaDmlGiGetQosServiceflow(serviceFlowCount, &serviceFlowChannel);
            if (!ret)
            {
                /* Used to allocate buffers only for number of Upstream services */
                for (index = 0; index < serviceFlowCount; index++)
                {
                    if (serviceFlowChannel[index].FlowDirection == UPSTREAM_INDEX )
                        Lgi_QosSF->pServiceUsFlowCount++;
                }
                
                Lgi_QosSF->pServiceUsFlowChannel = (cm_lgi_qos_sflow_t*) AnscAllocateMemory( sizeof(cm_lgi_qos_sflow_t) * Lgi_QosSF->pServiceUsFlowCount );
                if ((NULL != Lgi_QosSF->pServiceUsFlowChannel) && (NULL != serviceFlowChannel))
                {
                    chIndex = 0;
                    for(index = 0; index < serviceFlowCount; index++)
                    {
                        if((chIndex < Lgi_QosSF->pServiceUsFlowCount) && (serviceFlowChannel[index].FlowDirection == UPSTREAM_INDEX))
                        {
                            Lgi_QosSF->pServiceUsFlowChannel[chIndex].FlowSID = serviceFlowChannel[index].FlowSID;
                            Lgi_QosSF->pServiceUsFlowChannel[chIndex].FlowDirection = serviceFlowChannel[index].FlowDirection;
                            chIndex++;
                        }
                    }
                }

                if (NULL != Lgi_QosSF->pSfUsParamset)
                {
                    ret = CosaDmlGiGetQosServiceflowParamset(Lgi_QosSF->pServiceUsParamCount, &serviceFlowChannel, &Lgi_QosSF->pSfUsParamset);
                }
            }

            /* Free memory for local structure for QOS Service Flow */
            AnscFreeMemory(serviceFlowChannel);
            serviceFlowChannel = NULL;
        }
    }

    if (ret && (Lgi_QosSF->pServiceUsFlowChannel != NULL) &&
        (Lgi_QosSF->pSfUsParamset != NULL))
    {
        AnscFreeMemory(Lgi_QosSF->pServiceUsFlowChannel);
        Lgi_QosSF->pServiceUsFlowChannel = NULL;
        Lgi_QosSF->pServiceUsFlowCount = 0;

        AnscFreeMemory(Lgi_QosSF->pSfUsParamset);
        Lgi_QosSF->pSfUsParamset = NULL;
        Lgi_QosSF->pServiceUsParamCount = 0;
    }

    Ccsp_cm_clnt_unlock();
    return 0;
}
/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        Lgi_US_QosParamSet_GetEntryCount
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG
Lgi_US_QosServiceFlow_GetEntryCount
    (
        ANSC_HANDLE                 hInsContext
    )
{
    if (NULL != Lgi_QosSF)
    {
        return Lgi_QosSF->pServiceUsFlowCount;
    }
    
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE
        Lgi_US_QosServiceFlow_GetEntry
            (
                ANSC_HANDLE                 hInsContext,
                ULONG                       nIndex,
                ULONG*                      pInsNumber
            );

    description:

        This function is called to retrieve the entry specified by the index.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                ULONG                       nIndex,
                The index of this entry;

                ULONG*                      pInsNumber
                The output instance number;

    return:     The handle to identify the entry

**********************************************************************/

ANSC_HANDLE
Lgi_US_QosServiceFlow_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    )
{
    if (NULL != Lgi_QosSF)
    {
        *pInsNumber  = nIndex + 1;
        return &Lgi_QosSF->pServiceUsFlowChannel[nIndex];
    }

    return NULL;
}

/**********************************************************************
    caller:     owner of this object

    prototype:

        ULONG
        Lgi_US_QosParamSet_GetEntryCount
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG
Lgi_US_QosParamSet_GetEntryCount
    (
         ANSC_HANDLE                 hInsContext
    )
{
    if (NULL != Lgi_QosSF)
    {
        return 1; // Currently showing only the Active paramset values per service flow
    }
    
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE
        Lgi_US_QosParamSet_GetEntry
            (
                ANSC_HANDLE                 hInsContext,
                ULONG                       nIndex,
                ULONG*                      pInsNumber
            );

    description:

        This function is called to retrieve the entry specified by the index.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                ULONG                       nIndex,
                The index of this entry;

                ULONG*                      pInsNumber
                The output instance number;

    return:     The handle to identify the entry

**********************************************************************/
ANSC_HANDLE
Lgi_US_QosParamSet_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    )
{
    cm_lgi_qos_sflow_t*     pConf  = (cm_lgi_qos_sflow_t*)hInsContext;
    uint32_t index = 0;

    if (NULL != Lgi_QosSF)
    {
        for(index = 0 ; index < Lgi_QosSF->pServiceUsParamCount ; index++)
        {
            if(Lgi_QosSF->pSfUsParamset[index].SFID == pConf->FlowSID)
            {
               *pInsNumber  = nIndex + 1;
                return &Lgi_QosSF->pSfUsParamset[index];
            }
        }
    }

    return NULL; /* return the handle */
}

/***********************************************************************
 APIs for Object:

    X_LGI-COM_CableModem.QosServiceFlow.Downstream{i}.
    *  Lgi_DS_QosServiceFlow_IsUpdated
    *  Lgi_DS_QosServiceFlow_Synchronize
    *  Lgi_DS_QosServiceFlow_GetEntryCount
    *  Lgi_Ds_QosServiceFlow_GetEntry

    X_LGI-COM_CableModem.QosServiceFlow.Downstream{i}.QosParamSet.{i}
    *  Lgi_DS_QosParamSet_GetEntryCount
    *  Lgi_DS_QosParamSet_GetEntry
***********************************************************************/
/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL
        Lgi_DS_QosServiceFlow_IsUpdated
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is checking whether the table is updated or not.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     TRUE or FALSE.

**********************************************************************/
BOOL
Lgi_DS_QosServiceFlow_IsUpdated
    (
        ANSC_HANDLE                 hInsContext
    )
{

    if (NULL == Lgi_QosSF)
    {
        return FALSE;
    }

    if ( !Lgi_QosSF->ServiceDsFlowUpdateTime )
    {
        Lgi_QosSF->ServiceDsFlowUpdateTime = AnscGetTickInSeconds();
        return TRUE;
    }

    if ( Lgi_QosSF->ServiceDsFlowUpdateTime >= TIME_NO_NEGATIVE(AnscGetTickInSeconds() - CM_REFRESH_INTERVAL) )
    {
        return FALSE;
    }
    else
    {
        Lgi_QosSF->ServiceDsFlowUpdateTime = AnscGetTickInSeconds();
        return TRUE;
    }
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        Lgi_DS_QosServiceFlow_Synchronize
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is called to synchronize the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The status of the operation.

**********************************************************************/

ULONG
Lgi_DS_QosServiceFlow_Synchronize
    (
        ANSC_HANDLE                 hInsContext
    )
{
    int ret = -1; 

    /* Local Struct use to get the all the data */
    cm_lgi_qos_sflow_t *serviceFlowChannel = (cm_lgi_qos_sflow_t *)NULL;
    uint32_t serviceFlowCount = 0;
    uint32_t serviceDsParamCount = 0;
    uint32_t index = 0, chIndex = 0;

    if ( NULL == Lgi_QosSF )
    {
        return ret;
    }

    Ccsp_cm_clnt_lock();

    /* Clear the previous data */
    if ( Lgi_QosSF->pServiceDsFlowChannel )
    {
        AnscFreeMemory(Lgi_QosSF->pServiceDsFlowChannel);
        Lgi_QosSF->pServiceDsFlowChannel = NULL;
    }

    if ( Lgi_QosSF->pSfDsParamset )
    {
        AnscFreeMemory(Lgi_QosSF->pSfDsParamset);
        Lgi_QosSF->pSfDsParamset = NULL;
    }

    Lgi_QosSF->pServiceDsFlowCount = 0;
    Lgi_QosSF->pServiceDsParamCount  = 0;

    /* Get QOS ServiceFlow and Paramset count */
    
    ret = qos_getServiceFlowCount(&serviceFlowCount) || qos_getServiceFlowParamCount(&serviceDsParamCount);
    /* Allocate memory for local structure to store QOS Service Flow */
    if ((!ret) && (serviceFlowCount != 0))
    {
        Lgi_QosSF->pServiceDsParamCount = serviceDsParamCount;
        serviceFlowChannel = (cm_lgi_qos_sflow_t*) AnscAllocateMemory( sizeof(cm_lgi_qos_sflow_t) * serviceFlowCount );
        Lgi_QosSF->pSfDsParamset = (cm_lgi_qos_paramset_t*) AnscAllocateMemory( sizeof(cm_lgi_qos_paramset_t) * Lgi_QosSF->pServiceDsParamCount );
        if (NULL != serviceFlowChannel)
        {
            ret = CosaDmlGiGetQosServiceflow(serviceFlowCount, &serviceFlowChannel);
            if (!ret)
            {
                /* Used to allocate buffers only for number of Upstream services */
                for(index = 0; index < serviceFlowCount; index++)
                {
                    if ( serviceFlowChannel[index].FlowDirection == DOWNSTREAM_INDEX )
                        Lgi_QosSF->pServiceDsFlowCount++;
                }

                Lgi_QosSF->pServiceDsFlowChannel = (cm_lgi_qos_sflow_t*) AnscAllocateMemory( sizeof(cm_lgi_qos_sflow_t) * Lgi_QosSF->pServiceDsFlowCount );
                if ((NULL != Lgi_QosSF->pServiceDsFlowChannel) && (NULL != serviceFlowChannel))
                {
                    chIndex = 0;
                    for(index = 0; index < serviceFlowCount; index++)
                    {
                        if((chIndex < Lgi_QosSF->pServiceDsFlowCount) && (serviceFlowChannel[index].FlowDirection == DOWNSTREAM_INDEX))
                        {
                            Lgi_QosSF->pServiceDsFlowChannel[chIndex].FlowSID = serviceFlowChannel[index].FlowSID;
                            Lgi_QosSF->pServiceDsFlowChannel[chIndex].FlowDirection = serviceFlowChannel[index].FlowDirection;
                            chIndex++;
                        }
                    }
                }

                if (NULL != Lgi_QosSF->pSfDsParamset)
                {
                    ret = CosaDmlGiGetQosServiceflowParamset(Lgi_QosSF->pServiceDsParamCount,&serviceFlowChannel, &Lgi_QosSF->pSfDsParamset);
                }

                /* Free memory for local structure for QOS Service Flow */
                AnscFreeMemory(serviceFlowChannel);
                serviceFlowChannel = NULL;
            }
        }
    }

    if (ret && (Lgi_QosSF->pServiceDsFlowChannel != NULL) &&
         (Lgi_QosSF->pSfDsParamset != NULL))
    {
        AnscFreeMemory(Lgi_QosSF->pServiceDsFlowChannel);
        Lgi_QosSF->pServiceDsFlowChannel = NULL;
        Lgi_QosSF->pServiceDsFlowCount = 0;

        AnscFreeMemory(Lgi_QosSF->pSfDsParamset);
        Lgi_QosSF->pSfDsParamset = NULL;
        Lgi_QosSF->pServiceDsParamCount = 0;
    }

    Ccsp_cm_clnt_unlock();
    return 0;
}
/**********************************************************************

    caller:     owner of this object

    prototype:

        ULONG
        Lgi_DS_QosParamSet_GetEntryCount
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG
Lgi_DS_QosServiceFlow_GetEntryCount
    (
        ANSC_HANDLE                 hInsContext
    )
{
    if (NULL != Lgi_QosSF)
    {
       return Lgi_QosSF->pServiceDsFlowCount;
    }
    
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE
        Lgi_DS_QosServiceFlow_GetEntry
            (
                ANSC_HANDLE                 hInsContext,
                ULONG                       nIndex,
                ULONG*                      pInsNumber
            );

    description:

        This function is called to retrieve the entry specified by the index.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                ULONG                       nIndex,
                The index of this entry;

                ULONG*                      pInsNumber
                The output instance number;

    return:     The handle to identify the entry

**********************************************************************/

ANSC_HANDLE
Lgi_DS_QosServiceFlow_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    )
{
    if (NULL != Lgi_QosSF)
    {
        *pInsNumber  = nIndex + 1;
        return &Lgi_QosSF->pServiceDsFlowChannel[nIndex];
    }
    
    return NULL;
}

/**********************************************************************
    caller:     owner of this object

    prototype:

        ULONG
        Lgi_DS_QosParamSet_GetEntryCount
            (
                ANSC_HANDLE                 hInsContext
            );

    description:

        This function is called to retrieve the count of the table.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

    return:     The count of the table

**********************************************************************/
ULONG
Lgi_DS_QosParamSet_GetEntryCount
    (
         ANSC_HANDLE                 hInsContext
    )
{
    if (NULL != Lgi_QosSF)
    {
        return 1; // Currently showing only the Active paramset values per service flow
    }
    
    return 0;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        ANSC_HANDLE
        Lgi_QosParamSet_GetEntry
            (
                ANSC_HANDLE                 hInsContext,
                ULONG                       nIndex,
                ULONG*                      pInsNumber
            );

    description:

        This function is called to retrieve the entry specified by the index.

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                ULONG                       nIndex,
                The index of this entry;

                ULONG*                      pInsNumber
                The output instance number;

    return:     The handle to identify the entry

**********************************************************************/
ANSC_HANDLE
Lgi_DS_QosParamSet_GetEntry
    (
        ANSC_HANDLE                 hInsContext,
        ULONG                       nIndex,
        ULONG*                      pInsNumber
    )
{
    cm_lgi_qos_sflow_t*     pConf  = (cm_lgi_qos_sflow_t*)hInsContext;
    uint32_t index = 0;

    if (NULL != Lgi_QosSF)
    {
        for(index = 0 ; index < Lgi_QosSF->pServiceDsParamCount ; index++)
        {
            if(Lgi_QosSF->pSfDsParamset[index].SFID == pConf->FlowSID)
            {
               *pInsNumber  = nIndex + 1;
                return &Lgi_QosSF->pSfDsParamset[index];
            }
        }
    }
    
    return NULL; /* return the handle */
}

/*********************************************************************
Common API's to GET Param values for Upstream and Downstram Service.

   *  Lgi_QosServiceFlow_GetParamUlongValue
   *  Lgi_QosParamSet_GetParamUlongValue
*********************************************************************/
/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL
        Lgi_QosServiceFlow_GetParamUlongValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                ULONG*                      puLong
            );

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
Lgi_QosServiceFlow_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      puLong
    )
{
    cm_lgi_qos_sflow_t* pConf = (cm_lgi_qos_sflow_t*)hInsContext;

    if (strcmp(ParamName, "FlowSID") == 0)
    {
         *puLong = pConf->FlowSID;
         return TRUE;
    }
    return FALSE;
}

/**********************************************************************

    caller:     owner of this object

    prototype:

        BOOL
        Lgi_QosParamSet_GetParamUlongValue
            (
                ANSC_HANDLE                 hInsContext,
                char*                       ParamName,
                ULONG*                      puLong
            );

    description:

        This function is called to retrieve ULONG parameter value;

    argument:   ANSC_HANDLE                 hInsContext,
                The instance handle;

                char*                       ParamName,
                The parameter name;

                ULONG*                      puLong
                The buffer of returned ULONG value;

    return:     TRUE if succeeded.

**********************************************************************/
BOOL
Lgi_QosParamSet_GetParamUlongValue
    (
        ANSC_HANDLE                 hInsContext,
        char*                       ParamName,
        ULONG*                      puLong
    )
{
    cm_lgi_qos_paramset_t* pConf = (cm_lgi_qos_paramset_t*)hInsContext;

    if (strcmp(ParamName, "MaxTrafficRate") == 0)
    {
        *puLong =  pConf->MaxTrafficRate;
        return TRUE;
    }

    if (strcmp(ParamName, "MaxTrafficBurst") == 0)
    {
        if((pConf->SchedulingType == SF_TYPE_UNDEFINED)||
           (pConf->SchedulingType == SF_BEST_EFFORT)||
           (pConf->SchedulingType == SF_NON_REALTIME_PS)||
           (pConf->SchedulingType == SF_REALTIME_PL))
        {
            *puLong = pConf->MaxTrafficBurst;
        }
        else
        {
            *puLong = 0;
        }

        return TRUE;
    }

    if (strcmp(ParamName, "MinReservedRate") == 0)
    {
        *puLong =  pConf->MinReservedRate;
        return TRUE;
    }
    if (strcmp(ParamName, "MaxConcatBurst") == 0)
    {
        if((pConf->SchedulingType == SF_BEST_EFFORT)||
           (pConf->SchedulingType == SF_NON_REALTIME_PS)||
           (pConf->SchedulingType == SF_REALTIME_PL))
        {
            *puLong = pConf->MaxConcatBurst;
        }
        else
        {
            *puLong = 0;
        }

        return TRUE;
    }
    if (strcmp(ParamName, "SchedulingType") == 0)
    {
        *puLong =  pConf->SchedulingType;
        return TRUE;
    }

    return FALSE;
}


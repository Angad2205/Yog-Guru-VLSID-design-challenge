/*
 * FreeRTOS PKCS #11 PAL for LPC54018 IoT Module V1.0.3
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 * Copyright 2018-2022 NXP
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/**
 * @file iot_pkcs11_pal.c
 * @brief NXP LPC54018 IoT module file save and read implementation
 * for PKCS#11  based on mbedTLS with for software keys. This
 * file deviates from the FreeRTOS style standard for some function names and
 * data types in order to maintain compliance with the PKCS#11 standard.
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "FreeRTOSIPConfig.h"
#include "iot_crypto.h"
#include "task.h"
#include "core_pkcs11.h"
#include "core_pkcs11_config.h"

/* Flash write */
#include "sln_flash_fs_ops.h"
#include "sln_flash_files.h"

/* C runtime includes. */
#include <stdio.h>
#include <string.h>

/* Filenames from config file take precedence */
#define pkcs11palFILE_NAME_CLIENT_CERTIFICATE clientcredentialCLIENT_CERTIFICATE_PEM
#define pkcs11palFILE_NAME_KEY                clientcredentialCLIENT_PRIVATE_KEY_PEM

#define pkcs11palFILE_CODE_SIGN_PUBLIC_KEY "FreeRTOS_P11_CodeSignKey.dat"

enum eObjectHandles
{
    eInvalidHandle       = 0, /* According to PKCS #11 spec, 0 is never a valid object handle. */
    eAwsDevicePrivateKey = 1,
    eAwsDevicePublicKey,
    eAwsDeviceCertificate,
    eAwsCodeSigningKey
};

/*-----------------------------------------------------------*/

/* Converts a label to its respective filename and handle. */
void prvLabelToFilenameHandle(uint8_t *pcLabel, char **pcFileName, CK_OBJECT_HANDLE_PTR pHandle)
{
    if (pcLabel != NULL)
    {
        /* Translate from the PKCS#11 label to local storage file name. */
        if (0 == memcmp(pcLabel, &pkcs11configLABEL_DEVICE_CERTIFICATE_FOR_TLS,
                        sizeof(pkcs11configLABEL_DEVICE_CERTIFICATE_FOR_TLS)))
        {
            *pcFileName = pkcs11palFILE_NAME_CLIENT_CERTIFICATE;
            *pHandle    = eAwsDeviceCertificate;
        }
        else if (0 == memcmp(pcLabel, &pkcs11configLABEL_DEVICE_PRIVATE_KEY_FOR_TLS,
                             sizeof(pkcs11configLABEL_DEVICE_PRIVATE_KEY_FOR_TLS)))
        {
            *pcFileName = pkcs11palFILE_NAME_KEY;
            *pHandle    = eAwsDevicePrivateKey;
        }
        else if (0 == memcmp(pcLabel, &pkcs11configLABEL_DEVICE_PUBLIC_KEY_FOR_TLS,
                             sizeof(pkcs11configLABEL_DEVICE_PUBLIC_KEY_FOR_TLS)))
        {
            *pcFileName = pkcs11palFILE_NAME_KEY;
            *pHandle    = eAwsDevicePublicKey;
        }
        else if (0 == memcmp(pcLabel, &pkcs11configLABEL_CODE_VERIFICATION_KEY,
                             sizeof(pkcs11configLABEL_CODE_VERIFICATION_KEY)))
        {
            *pcFileName = pkcs11palFILE_CODE_SIGN_PUBLIC_KEY;
            *pHandle    = eAwsCodeSigningKey;
        }
        else
        {
            *pcFileName = NULL;
            *pHandle    = eInvalidHandle;
        }
    }
}

/**
 * @brief Writes a file to local storage.
 *
 * Port-specific file write for crytographic information.
 *
 * @param[in] pxLabel       Label of the object to be saved.
 * @param[in] pucData       Data buffer to be written to file
 * @param[in] ulDataSize    Size (in bytes) of data to be saved.
 *
 * @return The file handle of the object that was stored.
 */
CK_OBJECT_HANDLE PKCS11_PAL_SaveObject(CK_ATTRIBUTE_PTR pxLabel, CK_BYTE_PTR pucData, CK_ULONG ulDataSize)
{
    CK_OBJECT_HANDLE xHandle = eInvalidHandle;
    char *pcFileName         = NULL;

    /* Translate from the PKCS#11 label to local storage file name. */
    prvLabelToFilenameHandle(pxLabel->pValue, &pcFileName, &xHandle);

    if (xHandle != eInvalidHandle)
    {
        if (SLN_FLASH_FS_OK != sln_flash_fs_ops_save(pcFileName, pucData, ulDataSize))
        {
            xHandle = eInvalidHandle;
        }
    }

    return xHandle;
}

/*-----------------------------------------------------------*/

/**
 * @brief Translates a PKCS #11 label into an object handle.
 *
 * Port-specific object handle retrieval.
 *
 *
 * @param[in] pxLabel         Pointer to the label of the object
 *                           who's handle should be found.
 * @param[in] usLength       The length of the label, in bytes.
 *
 * @return The object handle if operation was successful.
 * Returns eInvalidHandle if unsuccessful.
 */
CK_OBJECT_HANDLE PKCS11_PAL_FindObject(CK_BYTE_PTR pxLabel, CK_ULONG usLength)
{
    CK_OBJECT_HANDLE xHandle = eInvalidHandle;
    char *pcFileName         = NULL;
    uint8_t *pFile           = NULL;
    uint32_t xFileLength     = 0;

    /* Translate from the PKCS#11 label to local storage file name. */
    prvLabelToFilenameHandle(pxLabel, &pcFileName, &xHandle);

    /* Check if the file exists. */
    if (SLN_FLASH_FS_OK != sln_flash_fs_ops_read(pcFileName, NULL, 0, &xFileLength))
    {
        xHandle = eInvalidHandle;
    }

    return xHandle;
}

/*-----------------------------------------------------------*/

/**
 * @brief Gets the value of an object in storage, by handle.
 *
 * Port-specific file access for cryptographic information.
 *
 * This call dynamically allocates the buffer which object value
 * data is copied into.  PKCS11_PAL_GetObjectValueCleanup()
 * should be called after each use to free the dynamically allocated
 * buffer.
 *
 * @sa PKCS11_PAL_GetObjectValueCleanup
 *
 * @param[in] pcFileName    The name of the file to be read.
 * @param[out] ppucData     Pointer to buffer for file data.
 * @param[out] pulDataSize  Size (in bytes) of data located in file.
 * @param[out] pIsPrivate   Boolean indicating if value is private (CK_TRUE)
 *                          or exportable (CK_FALSE)
 *
 * @return CKR_OK if operation was successful.  CKR_KEY_HANDLE_INVALID if
 * no such object handle was found, CKR_DEVICE_MEMORY if memory for
 * buffer could not be allocated, CKR_FUNCTION_FAILED for device driver
 * error.
 */
CK_RV PKCS11_PAL_GetObjectValue(CK_OBJECT_HANDLE xHandle,
                                CK_BYTE_PTR *ppucData,
                                uint32_t *pulDataSize,
                                CK_BBOOL *pIsPrivate)
{
    char *pcFileName = NULL;
    CK_RV ulReturn   = CKR_OK;

    if (pulDataSize == NULL)
    {
        return CKR_FUNCTION_FAILED;
    }

    if (xHandle == eAwsDeviceCertificate)
    {
        pcFileName  = pkcs11palFILE_NAME_CLIENT_CERTIFICATE;
        *pIsPrivate = CK_FALSE;
    }
    else if (xHandle == eAwsDevicePrivateKey)
    {
        pcFileName  = pkcs11palFILE_NAME_KEY;
        *pIsPrivate = CK_TRUE;
    }
    else if (xHandle == eAwsDevicePublicKey)
    {
        /* Public and private key are stored together in same file. */
        pcFileName  = pkcs11palFILE_NAME_KEY;
        *pIsPrivate = CK_FALSE;
    }
    else if (xHandle == eAwsCodeSigningKey)
    {
        pcFileName  = pkcs11palFILE_CODE_SIGN_PUBLIC_KEY;
        *pIsPrivate = CK_FALSE;
    }
    else
    {
        ulReturn = CKR_KEY_HANDLE_INVALID;
    }

    /* Copy memory from NVM to RAM */
    if (CKR_OK == ulReturn)
    {
        if (SLN_FLASH_FS_OK != sln_flash_fs_ops_read(pcFileName, NULL, 0, pulDataSize))
        {
            ulReturn = CKR_FUNCTION_FAILED;
        }
        else
        {
            if (*ppucData == NULL)
            {
                *ppucData = (uint8_t *)pvPortMalloc(*pulDataSize + 1);
                if (*ppucData == NULL)
                {
                    ulReturn = CKR_FUNCTION_FAILED;
                }
                else
                {
                    /* Wipe out memory here */
                    memset(*ppucData, 0x00, *pulDataSize);
                }
            }
            else
            {
                ulReturn = CKR_FUNCTION_FAILED;
            }
        }
    }

    if (CKR_OK == ulReturn)
    {
        if (SLN_FLASH_FS_OK != sln_flash_fs_ops_read(pcFileName, *ppucData, 0, pulDataSize))
        {
            ulReturn = CKR_FUNCTION_FAILED;
            memset(*ppucData, 0x00, *pulDataSize);
            vPortFree(*ppucData);
            *ppucData = NULL;
        }
    }

    return ulReturn;
}

/**
 * @brief Cleanup after PKCS11_GetObjectValue().
 *
 * @param[in] pucData       The buffer to free.
 *                          (*ppucData from PKCS11_PAL_GetObjectValue())
 * @param[in] ulDataSize    The length of the buffer to free.
 *                          (*pulDataSize from PKCS11_PAL_GetObjectValue())
 */
void PKCS11_PAL_GetObjectValueCleanup(CK_BYTE_PTR pucData, CK_ULONG ulDataSize)
{
    if (NULL != pucData)
    {
        memset(pucData, 0x00, ulDataSize);
    }
    vPortFree(pucData);
    pucData = NULL;
}

CK_RV PKCS11_PAL_Initialize(void)
{
    CK_RV xResult = CKR_OK;
    CRYPTO_Init();

    if (SLN_FLASH_FS_OK != sln_flash_fs_ops_init(false))
    {
        xResult = CKR_OPERATION_NOT_INITIALIZED;
    }

    return xResult;
}

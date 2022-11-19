//
// Created by Erhan Kurnaz on 17/08/2022.
//
// Got code from https://github.com/sipsorcery/mediafoundationsamples/blob/master/Common/MFUtility.h

#pragma once
#include <iostream>
#include <mfapi.h>
#include <mfidl.h>
#include <mferror.h>
#include <mfreadwrite.h>

#include <string>

template <class T> void SAFE_RELEASE(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

template <class T> inline void SAFE_RELEASE(T*& pT)
{
    if (pT != NULL)
    {
        pT->Release();
        pT = NULL;
    }
}

#ifndef IF_EQUAL_RETURN
#define IF_EQUAL_RETURN(param, val) if(val == param) return #val
#endif

#define CHECKHR_GOTO(x, y) if(FAILED(x)) goto y

LPCSTR GetGUIDNameConst(const GUID& guid)
{
    IF_EQUAL_RETURN(guid, MF_MT_MAJOR_TYPE);
    IF_EQUAL_RETURN(guid, MF_MT_MAJOR_TYPE);
    IF_EQUAL_RETURN(guid, MF_MT_SUBTYPE);
    IF_EQUAL_RETURN(guid, MF_MT_ALL_SAMPLES_INDEPENDENT);
    IF_EQUAL_RETURN(guid, MF_MT_FIXED_SIZE_SAMPLES);
    IF_EQUAL_RETURN(guid, MF_MT_COMPRESSED);
    IF_EQUAL_RETURN(guid, MF_MT_SAMPLE_SIZE);
    IF_EQUAL_RETURN(guid, MF_MT_WRAPPED_TYPE);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_NUM_CHANNELS);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_SAMPLES_PER_SECOND);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_FLOAT_SAMPLES_PER_SECOND);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_AVG_BYTES_PER_SECOND);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_BLOCK_ALIGNMENT);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_BITS_PER_SAMPLE);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_VALID_BITS_PER_SAMPLE);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_SAMPLES_PER_BLOCK);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_CHANNEL_MASK);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_FOLDDOWN_MATRIX);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_WMADRC_PEAKREF);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_WMADRC_PEAKTARGET);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_WMADRC_AVGREF);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_WMADRC_AVGTARGET);
    IF_EQUAL_RETURN(guid, MF_MT_AUDIO_PREFER_WAVEFORMATEX);
    IF_EQUAL_RETURN(guid, MF_MT_AAC_PAYLOAD_TYPE);
    IF_EQUAL_RETURN(guid, MF_MT_AAC_AUDIO_PROFILE_LEVEL_INDICATION);
    IF_EQUAL_RETURN(guid, MF_MT_FRAME_SIZE);
    IF_EQUAL_RETURN(guid, MF_MT_FRAME_RATE);
    IF_EQUAL_RETURN(guid, MF_MT_FRAME_RATE_RANGE_MAX);
    IF_EQUAL_RETURN(guid, MF_MT_FRAME_RATE_RANGE_MIN);
    IF_EQUAL_RETURN(guid, MF_MT_PIXEL_ASPECT_RATIO);
    IF_EQUAL_RETURN(guid, MF_MT_DRM_FLAGS);
    IF_EQUAL_RETURN(guid, MF_MT_PAD_CONTROL_FLAGS);
    IF_EQUAL_RETURN(guid, MF_MT_SOURCE_CONTENT_HINT);
    IF_EQUAL_RETURN(guid, MF_MT_VIDEO_CHROMA_SITING);
    IF_EQUAL_RETURN(guid, MF_MT_INTERLACE_MODE);
    IF_EQUAL_RETURN(guid, MF_MT_TRANSFER_FUNCTION);
    IF_EQUAL_RETURN(guid, MF_MT_VIDEO_PRIMARIES);
    IF_EQUAL_RETURN(guid, MF_MT_CUSTOM_VIDEO_PRIMARIES);
    IF_EQUAL_RETURN(guid, MF_MT_YUV_MATRIX);
    IF_EQUAL_RETURN(guid, MF_MT_VIDEO_LIGHTING);
    IF_EQUAL_RETURN(guid, MF_MT_VIDEO_NOMINAL_RANGE);
    IF_EQUAL_RETURN(guid, MF_MT_GEOMETRIC_APERTURE);
    IF_EQUAL_RETURN(guid, MF_MT_MINIMUM_DISPLAY_APERTURE);
    IF_EQUAL_RETURN(guid, MF_MT_PAN_SCAN_APERTURE);
    IF_EQUAL_RETURN(guid, MF_MT_PAN_SCAN_ENABLED);
    IF_EQUAL_RETURN(guid, MF_MT_AVG_BITRATE);
    IF_EQUAL_RETURN(guid, MF_MT_AVG_BIT_ERROR_RATE);
    IF_EQUAL_RETURN(guid, MF_MT_MAX_KEYFRAME_SPACING);
    IF_EQUAL_RETURN(guid, MF_MT_DEFAULT_STRIDE);
    IF_EQUAL_RETURN(guid, MF_MT_PALETTE);
    IF_EQUAL_RETURN(guid, MF_MT_USER_DATA);
    IF_EQUAL_RETURN(guid, MF_MT_AM_FORMAT_TYPE);
    IF_EQUAL_RETURN(guid, MF_MT_MPEG_START_TIME_CODE);
    IF_EQUAL_RETURN(guid, MF_MT_MPEG2_PROFILE);
    IF_EQUAL_RETURN(guid, MF_MT_MPEG2_LEVEL);
    IF_EQUAL_RETURN(guid, MF_MT_MPEG2_FLAGS);
    IF_EQUAL_RETURN(guid, MF_MT_MPEG_SEQUENCE_HEADER);
    IF_EQUAL_RETURN(guid, MF_MT_DV_AAUX_SRC_PACK_0);
    IF_EQUAL_RETURN(guid, MF_MT_DV_AAUX_CTRL_PACK_0);
    IF_EQUAL_RETURN(guid, MF_MT_DV_AAUX_SRC_PACK_1);
    IF_EQUAL_RETURN(guid, MF_MT_DV_AAUX_CTRL_PACK_1);
    IF_EQUAL_RETURN(guid, MF_MT_DV_VAUX_SRC_PACK);
    IF_EQUAL_RETURN(guid, MF_MT_DV_VAUX_CTRL_PACK);
    IF_EQUAL_RETURN(guid, MF_MT_ARBITRARY_HEADER);
    IF_EQUAL_RETURN(guid, MF_MT_ARBITRARY_FORMAT);
    IF_EQUAL_RETURN(guid, MF_MT_IMAGE_LOSS_TOLERANT);
    IF_EQUAL_RETURN(guid, MF_MT_MPEG4_SAMPLE_DESCRIPTION);
    IF_EQUAL_RETURN(guid, MF_MT_MPEG4_CURRENT_SAMPLE_ENTRY);
    IF_EQUAL_RETURN(guid, MF_MT_ORIGINAL_4CC);
    IF_EQUAL_RETURN(guid, MF_MT_ORIGINAL_WAVE_FORMAT_TAG);

    // Media types

    IF_EQUAL_RETURN(guid, MFMediaType_Audio);
    IF_EQUAL_RETURN(guid, MFMediaType_Video);
    IF_EQUAL_RETURN(guid, MFMediaType_Protected);
    IF_EQUAL_RETURN(guid, MFMediaType_SAMI);
    IF_EQUAL_RETURN(guid, MFMediaType_Script);
    IF_EQUAL_RETURN(guid, MFMediaType_Image);
    IF_EQUAL_RETURN(guid, MFMediaType_HTML);
    IF_EQUAL_RETURN(guid, MFMediaType_Binary);
    IF_EQUAL_RETURN(guid, MFMediaType_FileTransfer);

    IF_EQUAL_RETURN(guid, MFVideoFormat_AI44); //     FCC('AI44')
    IF_EQUAL_RETURN(guid, MFVideoFormat_ARGB32); //   D3DFMT_A8R8G8B8
    IF_EQUAL_RETURN(guid, MFVideoFormat_AYUV); //     FCC('AYUV')
    IF_EQUAL_RETURN(guid, MFVideoFormat_DV25); //     FCC('dv25')
    IF_EQUAL_RETURN(guid, MFVideoFormat_DV50); //     FCC('dv50')
    IF_EQUAL_RETURN(guid, MFVideoFormat_DVH1); //     FCC('dvh1')
    IF_EQUAL_RETURN(guid, MFVideoFormat_DVSD); //     FCC('dvsd')
    IF_EQUAL_RETURN(guid, MFVideoFormat_DVSL); //     FCC('dvsl')
    IF_EQUAL_RETURN(guid, MFVideoFormat_H264); //     FCC('H264')
    IF_EQUAL_RETURN(guid, MFVideoFormat_I420); //     FCC('I420')
    IF_EQUAL_RETURN(guid, MFVideoFormat_IYUV); //     FCC('IYUV')
    IF_EQUAL_RETURN(guid, MFVideoFormat_M4S2); //     FCC('M4S2')
    IF_EQUAL_RETURN(guid, MFVideoFormat_MJPG);
    IF_EQUAL_RETURN(guid, MFVideoFormat_MP43); //     FCC('MP43')
    IF_EQUAL_RETURN(guid, MFVideoFormat_MP4S); //     FCC('MP4S')
    IF_EQUAL_RETURN(guid, MFVideoFormat_MP4V); //     FCC('MP4V')
    IF_EQUAL_RETURN(guid, MFVideoFormat_MPG1); //     FCC('MPG1')
    IF_EQUAL_RETURN(guid, MFVideoFormat_MSS1); //     FCC('MSS1')
    IF_EQUAL_RETURN(guid, MFVideoFormat_MSS2); //     FCC('MSS2')
    IF_EQUAL_RETURN(guid, MFVideoFormat_NV11); //     FCC('NV11')
    IF_EQUAL_RETURN(guid, MFVideoFormat_NV12); //     FCC('NV12')
    IF_EQUAL_RETURN(guid, MFVideoFormat_P010); //     FCC('P010')
    IF_EQUAL_RETURN(guid, MFVideoFormat_P016); //     FCC('P016')
    IF_EQUAL_RETURN(guid, MFVideoFormat_P210); //     FCC('P210')
    IF_EQUAL_RETURN(guid, MFVideoFormat_P216); //     FCC('P216')
    IF_EQUAL_RETURN(guid, MFVideoFormat_RGB24); //    D3DFMT_R8G8B8
    IF_EQUAL_RETURN(guid, MFVideoFormat_RGB32); //    D3DFMT_X8R8G8B8
    IF_EQUAL_RETURN(guid, MFVideoFormat_RGB555); //   D3DFMT_X1R5G5B5
    IF_EQUAL_RETURN(guid, MFVideoFormat_RGB565); //   D3DFMT_R5G6B5
    IF_EQUAL_RETURN(guid, MFVideoFormat_RGB8);
    IF_EQUAL_RETURN(guid, MFVideoFormat_UYVY); //     FCC('UYVY')
    IF_EQUAL_RETURN(guid, MFVideoFormat_v210); //     FCC('v210')
    IF_EQUAL_RETURN(guid, MFVideoFormat_v410); //     FCC('v410')
    IF_EQUAL_RETURN(guid, MFVideoFormat_WMV1); //     FCC('WMV1')
    IF_EQUAL_RETURN(guid, MFVideoFormat_WMV2); //     FCC('WMV2')
    IF_EQUAL_RETURN(guid, MFVideoFormat_WMV3); //     FCC('WMV3')
    IF_EQUAL_RETURN(guid, MFVideoFormat_WVC1); //     FCC('WVC1')
    IF_EQUAL_RETURN(guid, MFVideoFormat_Y210); //     FCC('Y210')
    IF_EQUAL_RETURN(guid, MFVideoFormat_Y216); //     FCC('Y216')
    IF_EQUAL_RETURN(guid, MFVideoFormat_Y410); //     FCC('Y410')
    IF_EQUAL_RETURN(guid, MFVideoFormat_Y416); //     FCC('Y416')
    IF_EQUAL_RETURN(guid, MFVideoFormat_Y41P);
    IF_EQUAL_RETURN(guid, MFVideoFormat_Y41T);
    IF_EQUAL_RETURN(guid, MFVideoFormat_YUY2); //     FCC('YUY2')
    IF_EQUAL_RETURN(guid, MFVideoFormat_YV12); //     FCC('YV12')
    IF_EQUAL_RETURN(guid, MFVideoFormat_YVYU);

    IF_EQUAL_RETURN(guid, MFAudioFormat_PCM); //              WAVE_FORMAT_PCM
    IF_EQUAL_RETURN(guid, MFAudioFormat_Float); //            WAVE_FORMAT_IEEE_FLOAT
    IF_EQUAL_RETURN(guid, MFAudioFormat_DTS); //              WAVE_FORMAT_DTS
    IF_EQUAL_RETURN(guid, MFAudioFormat_Dolby_AC3_SPDIF); //  WAVE_FORMAT_DOLBY_AC3_SPDIF
    IF_EQUAL_RETURN(guid, MFAudioFormat_DRM); //              WAVE_FORMAT_DRM
    IF_EQUAL_RETURN(guid, MFAudioFormat_WMAudioV8); //        WAVE_FORMAT_WMAUDIO2
    IF_EQUAL_RETURN(guid, MFAudioFormat_WMAudioV9); //        WAVE_FORMAT_WMAUDIO3
    IF_EQUAL_RETURN(guid, MFAudioFormat_WMAudio_Lossless); // WAVE_FORMAT_WMAUDIO_LOSSLESS
    IF_EQUAL_RETURN(guid, MFAudioFormat_WMASPDIF); //         WAVE_FORMAT_WMASPDIF
    IF_EQUAL_RETURN(guid, MFAudioFormat_MSP1); //             WAVE_FORMAT_WMAVOICE9
    IF_EQUAL_RETURN(guid, MFAudioFormat_MP3); //              WAVE_FORMAT_MPEGLAYER3
    IF_EQUAL_RETURN(guid, MFAudioFormat_MPEG); //             WAVE_FORMAT_MPEG
    IF_EQUAL_RETURN(guid, MFAudioFormat_AAC); //              WAVE_FORMAT_MPEG_HEAAC
    IF_EQUAL_RETURN(guid, MFAudioFormat_ADTS); //             WAVE_FORMAT_MPEG_ADTS_AAC

    return NULL;
}

void DebugShowDeviceNames(IMFActivate **ppDevices, UINT count)
{
    for (DWORD i = 0; i < count; ++i)
    {
        HRESULT hr = S_OK;
        WCHAR *friendlyName = NULL;

        // get display name
        UINT32 name;
        hr = ppDevices[i]->GetAllocatedString(MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME, &friendlyName, &name);

        if (!SUCCEEDED(hr))
        {
            return;
        }

        std::wcout << friendlyName << std::endl;
        CoTaskMemFree(friendlyName);
    }
}

HRESULT CreateVideoCaptureDevice(IMFMediaSource **ppSource)
{
    *ppSource = NULL;
    IMFAttributes *pConfig = NULL;
    HRESULT hr = MFCreateAttributes(&pConfig, 1);

    if (!SUCCEEDED(hr))
    {
        return hr;
    }

    hr = pConfig->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);
    if (!SUCCEEDED(hr))
    {
        return hr;
    }

    IMFActivate **ppDevices = NULL;
    UINT32 count = 0;
    hr = MFEnumDeviceSources(pConfig, &ppDevices, &count);
    if (!SUCCEEDED(hr))
    {
        return hr;
    }

    std::cout << count << std::endl;
    DebugShowDeviceNames(ppDevices, count);

    if (count > 0) {
        hr = ppDevices[0]->ActivateObject(IID_PPV_ARGS(ppSource));
    } else {
        hr = MF_E_NOT_FOUND;
    }

    for (DWORD i = 0; i < count; ++i) {
        ppDevices[i]->Release();
    }

    CoTaskMemFree(ppDevices);

    return hr;
}

/**
* Helper function to get a user friendly description for a media type.
* Note that there may be properties missing or incorrectly described.
* @param[in] pMediaType: pointer to the media type to get a description for.
* @@Returns A string describing the media type.
*
* Potential improvements https://docs.microsoft.com/en-us/windows/win32/medfound/media-type-debugging-code.
*/
std::string GetMediaTypeDescription(IMFMediaType* pMediaType)
{
    HRESULT hr = S_OK;
    GUID MajorType;
    UINT32 cAttrCount;
    LPCSTR pszGuidStr;
    std::string description;
    WCHAR TempBuf[200];

    if (pMediaType == NULL)
    {
        description = "<NULL>";
        goto done;
    }

    hr = pMediaType->GetMajorType(&MajorType);
    CHECKHR_GOTO(hr, done);

    //pszGuidStr = STRING_FROM_GUID(MajorType);
    pszGuidStr = GetGUIDNameConst(MajorType);
    if (pszGuidStr != NULL)
    {
        description += pszGuidStr;
        description += ": ";
    }
    else
    {
        description += "Other: ";
    }

    hr = pMediaType->GetCount(&cAttrCount);
    CHECKHR_GOTO(hr, done);

    for (UINT32 i = 0; i < cAttrCount; i++)
    {
        GUID guidId;
        MF_ATTRIBUTE_TYPE attrType;

        hr = pMediaType->GetItemByIndex(i, &guidId, NULL);
        CHECKHR_GOTO(hr, done);

        hr = pMediaType->GetItemType(guidId, &attrType);
        CHECKHR_GOTO(hr, done);

        //pszGuidStr = STRING_FROM_GUID(guidId);
        pszGuidStr = GetGUIDNameConst(guidId);
        if (pszGuidStr != NULL)
        {
            description += pszGuidStr;
        }
        else
        {
            LPOLESTR guidStr = NULL;

            CHECKHR_GOTO(StringFromCLSID(guidId, &guidStr), done);
            auto wGuidStr = std::wstring(guidStr);
            description += std::string(wGuidStr.begin(), wGuidStr.end()); // GUID's won't have wide chars.

            CoTaskMemFree(guidStr);
        }

        description += "=";

        switch (attrType)
        {
            case MF_ATTRIBUTE_UINT32:
            {
                UINT32 Val;
                hr = pMediaType->GetUINT32(guidId, &Val);
                CHECKHR_GOTO(hr, done);

                description += std::to_string(Val);
                break;
            }
            case MF_ATTRIBUTE_UINT64:
            {
                UINT64 Val;
                hr = pMediaType->GetUINT64(guidId, &Val);
                CHECKHR_GOTO(hr, done);

                if (guidId == MF_MT_FRAME_SIZE)
                {
                    description += "W:" + std::to_string(HI32(Val)) + " H: " + std::to_string(LO32(Val));
                }
                else if (guidId == MF_MT_FRAME_RATE)
                {
                    // Frame rate is numerator/denominator.
                    description += std::to_string(HI32(Val)) + "/" + std::to_string(LO32(Val));
                }
                else if (guidId == MF_MT_PIXEL_ASPECT_RATIO)
                {
                    description += std::to_string(HI32(Val)) + ":" + std::to_string(LO32(Val));
                }
                else
                {
                    //tempStr.Format("%ld", Val);
                    description += std::to_string(Val);
                }

                //description += tempStr;

                break;
            }
            case MF_ATTRIBUTE_DOUBLE:
            {
                DOUBLE Val;
                hr = pMediaType->GetDouble(guidId, &Val);
                CHECKHR_GOTO(hr, done);

                //tempStr.Format("%f", Val);
                description += std::to_string(Val);
                break;
            }
            case MF_ATTRIBUTE_GUID:
            {
                GUID Val;
                const char* pValStr;

                hr = pMediaType->GetGUID(guidId, &Val);
                CHECKHR_GOTO(hr, done);

                //pValStr = STRING_FROM_GUID(Val);
                pValStr = GetGUIDNameConst(Val);
                if (pValStr != NULL)
                {
                    description += pValStr;
                }
                else
                {
                    LPOLESTR guidStr = NULL;
                    CHECKHR_GOTO(StringFromCLSID(Val, &guidStr), done);
                    auto wGuidStr = std::wstring(guidStr);
                    description += std::string(wGuidStr.begin(), wGuidStr.end()); // GUID's won't have wide chars.

                    CoTaskMemFree(guidStr);
                }

                break;
            }
            case MF_ATTRIBUTE_STRING:
            {
                hr = pMediaType->GetString(guidId, TempBuf, sizeof(TempBuf) / sizeof(TempBuf[0]), NULL);
                if (hr == HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
                {
                    description += "<Too Long>";
                    break;
                }
                CHECKHR_GOTO(hr, done);
                auto wstr = std::wstring(TempBuf);
                description += std::string(wstr.begin(), wstr.end()); // It's unlikely the attribute descriptions will contain multi byte chars.

                break;
            }
            case MF_ATTRIBUTE_BLOB:
            {
                description += "<BLOB>";
                break;
            }
            case MF_ATTRIBUTE_IUNKNOWN:
            {
                description += "<UNK>";
                break;
            }
        }

        description += ", ";
    }

    done:

    return description;
}

std::string GetVideoTypeDescriptionBrief(IMFMediaType* pMediaType)
{
#define CHECK_HR(hr, msg) if(!SUCCEEDED(hr)) { fprintf(stderr, msg); fprintf(stderr, "\n"); fprintf(stderr, "Error code: %.2lX\n", (hr)); goto done; }

    std::string description = " ";
    GUID subType;
    UINT32 width = 0, height = 0, fpsNum = 0, fpsDen = 0;

    if (pMediaType == NULL) {
        description = " <NULL>";
    }
    else {
        CHECK_HR(pMediaType->GetGUID(MF_MT_SUBTYPE, &subType), "Failed to get video sub type.");
        CHECK_HR(MFGetAttributeSize(pMediaType, MF_MT_FRAME_SIZE, &width, &height), "Failed to get MF_MT_FRAME_SIZE attribute.");
        CHECK_HR(MFGetAttributeRatio(pMediaType, MF_MT_FRAME_RATE, &fpsNum, &fpsDen), "Failed to get MF_MT_FRAME_RATE attribute.");

        description += GetGUIDNameConst(subType);
        description += ", " + std::to_string(width) + "x" + std::to_string(height) + ", " + std::to_string(fpsNum) + "/" + std::to_string(fpsDen) + "fps";
    }

    done:

    return description;
}

void ListModes(IMFSourceReader* pReader, bool brief = false) {
    HRESULT hr = NULL;
    DWORD dwMediaTypeIndex = 0;

    while (SUCCEEDED(hr)) {
        IMFMediaType* pType = NULL;
        hr = pReader->GetNativeMediaType(0, dwMediaTypeIndex, &pType);
        if (hr == MF_E_NO_MORE_TYPES) {
            hr = S_OK;
            break;
        } else if (SUCCEEDED(hr)) {
            if (brief) {
                std::cout << GetVideoTypeDescriptionBrief(pType) << std::endl;
            } else {
                std::cout << GetMediaTypeDescription(pType) << std::endl;
            }

            pType->Release();
        }

        ++dwMediaTypeIndex;
    }
}

// Got code from https://github.com/sipsorcery/mediafoundationsamples/blob/master/MFCaptureRawFramesToFile/MFCaptureRawFramesToFile.cpp
// and https://github.com/sipsorcery/mediafoundationsamples/blob/master/MFWebCamToFile/MFWebCamToFile.cpp

#include <iostream>
#include <fstream>
#include <mfapi.h>
#include <mfidl.h>
#include <mferror.h>
#include <mfreadwrite.h>
#include <wmsdkidl.h>
#include <wmcodecdsp.h>
#include <codecapi.h>

#include "utility.h"

#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfplay.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "wmcodecdspuuid.lib")

#define FILENAME L"output.yuv"
// #define FILENAME L"output.mp4"
#define SAMPLE_COUNT 100
#define FRAME_RATE 30
#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480

#define WEBCAM_INDEX 0

#define RAW_FRAMES 1

int main() {
    IMFMediaSource* videoSource = NULL;
    UINT32 videoDeviceCount = 0;
    IMFAttributes* videoConfig = NULL;
    IMFActivate** videoDevices = NULL;
    IMFSourceReader* videoReader = NULL;
    WCHAR* webcamFriendlyName = NULL;
    IMFMediaType* videoSourceOutputType = NULL;
    IMFMediaType* pSrcOutMediaType = NULL;
    UINT webcamNameLength = 0;

    IMFSample *videoSample = NULL;
    DWORD videoStreamIndex;
    DWORD streamIndex, flags;
    LONGLONG llVideoTimestamp, llVideoBaseTime;
    int sampleCount = 0;
    IMFSinkWriter *pWriter = NULL;

#if RAW_FRAMES
    std::ofstream outputBuffer(FILENAME, std::ios::out | std::ios::binary);
#endif

    CHECK_HR(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE), "COM init failed");
    CHECK_HR(MFStartup(MF_VERSION), "Start up failed");
    CHECK_HR(MFCreateAttributes(&videoConfig, 1), "video config failed");
    CHECK_HR(videoConfig->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID), "video config failed");
    CHECK_HR(MFEnumDeviceSources(videoConfig, &videoDevices, &videoDeviceCount), "enumerating video devices failed");
    CHECK_HR(videoDevices[WEBCAM_INDEX]->GetAllocatedString(MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME, &webcamFriendlyName, &webcamNameLength), "error getting friendly name");
    std::wcout << "First available webcam: " << webcamFriendlyName << std::endl;
    CHECK_HR(videoDevices[WEBCAM_INDEX]->ActivateObject(IID_PPV_ARGS(&videoSource)), "Error activating device");
    CHECK_HR(MFCreateSourceReaderFromMediaSource(videoSource, videoConfig, &videoReader), "Error creating video reader");
    // list supported types
    ListModes(videoReader, true);
    CHECK_HR(MFCreateMediaType(&pSrcOutMediaType), "Failed to create media type");
    // TODO: set to image
    CHECK_HR(pSrcOutMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video), "failed to set major type");
    CHECK_HR(pSrcOutMediaType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_YUY2), "failed to set subtype");
    CHECK_HR(MFSetAttributeRatio(pSrcOutMediaType, MF_MT_FRAME_RATE, FRAME_RATE, 1), "Could not set ratio");
    CHECK_HR(MFSetAttributeSize(pSrcOutMediaType, MF_MT_FRAME_SIZE, FRAME_WIDTH, FRAME_HEIGHT), "Failed to set size");
    CHECK_HR(videoReader->SetCurrentMediaType(0, NULL, pSrcOutMediaType), "failed to set source reader media type");
#if !RAW_FRAMES
    CHECK_HR(MFCreateSinkWriterFromURL(
        FILENAME,
        NULL,
        NULL,
        &pWriter), "Error creating writer");

    // I have no clue what this function does
    CHECK_HR(MFTRegisterLocalByCLSID(
        __uuidof(CColorConvertDMO),
        MFT_CATEGORY_VIDEO_PROCESSOR,
        L"",
        MFT_ENUM_FLAG_SYNCMFT,
        0,
        NULL,
        0,
        NULL
        ), "Error registering color converted");

    CHECK_HR(MFCreateMediaType(&videoSourceOutputType), "failed to create vid src out type");
    CHECK_HR(pSrcOutMediaType->CopyAllItems(videoSourceOutputType), "Error copying all items over");
    CHECK_HR(videoSourceOutputType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_H264), "failed to set out video format");
    CHECK_HR(videoSourceOutputType->SetUINT32(MF_MT_AVG_BITRATE, 240'000), "Error setting average bitrate");
    CHECK_HR(videoSourceOutputType->SetUINT32(MF_MT_INTERLACE_MODE, 2), "Error setting interlace mode");
    CHECK_HR(MFSetAttributeRatio(videoSourceOutputType, MF_MT_MPEG2_PROFILE, eAVEncH264VProfile_Base, 1), "Failed to set profile");

    CHECK_HR(pWriter->AddStream(videoSourceOutputType, &videoStreamIndex), "failed to add stream");
    CHECK_HR(pWriter->SetInputMediaType(videoStreamIndex, pSrcOutMediaType, NULL), "Error setting input type");
    CHECK_HR(pWriter->BeginWriting(), "failed to begin writing");

    std::cout << "Recording" << std::endl;

    while (sampleCount <= SAMPLE_COUNT)
    {
        CHECK_HR(videoReader->ReadSample(
            MF_SOURCE_READER_ANY_STREAM,
            0,
            &streamIndex,
            &flags,
            &llVideoTimestamp,
            &videoSample
            ), "Error reading video sample");

        if (videoSample) {
            llVideoTimestamp -= llVideoBaseTime;
            CHECK_HR(videoSample->SetSampleTime(llVideoTimestamp), "Set video sample time failed");
            CHECK_HR(pWriter->WriteSample(videoStreamIndex, videoSample), "Write video sample failed");

            SAFE_RELEASE(&videoSample);
        }

        sampleCount++;
    }

    if (pWriter) {
        CHECK_HR(pWriter->Finalize(), "Error finalizing");
    }
#else
    LONGLONG llVideoTimeStamp, llSampleDuration;

    while (sampleCount <= SAMPLE_COUNT)
    {
        CHECK_HR(videoReader->ReadSample(
            MF_SOURCE_READER_FIRST_VIDEO_STREAM,
            0,                              // Flags.
            &streamIndex,                   // Receives the actual stream index.
            &flags,                         // Receives status flags.
            &llVideoTimeStamp,              // Receives the time stamp.
            &videoSample                    // Receives the sample or NULL.
            ), "Error reading video sample.");

        if (flags & MF_SOURCE_READERF_STREAMTICK)
        {
            printf("Stream tick.\n");
        }

        if (videoSample)
        {
            printf("Writing sample %i.\n", sampleCount);

            CHECK_HR(videoSample->SetSampleTime(llVideoTimeStamp), "Error setting the video sample time.");
            CHECK_HR(videoSample->GetSampleDuration(&llSampleDuration), "Error getting video sample duration.");

            IMFMediaBuffer *buf = NULL;
            DWORD bufLength;
            CHECK_HR(videoSample->ConvertToContiguousBuffer(&buf), "ConvertToContiguousBuffer failed.");
            CHECK_HR(buf->GetCurrentLength(&bufLength), "Get buffer length failed.");

            printf("Sample length %lu.\n", bufLength);

            byte *byteBuffer;
            DWORD buffCurrLen = 0;
            DWORD buffMaxLen = 0;
            CHECK_HR(buf->Lock(&byteBuffer, &buffMaxLen, &buffCurrLen), "Failed to lock video sample buffer.");

            outputBuffer.write((char *)byteBuffer, bufLength);

            CHECK_HR(buf->Unlock(), "Failed to unlock video sample buffer.");

            buf->Release();
            videoSample->Release();
        }

        sampleCount++;
    }

    outputBuffer.close();
#endif

done:

    std::cout << "Finished" << std::endl;
//    int c = getchar();

    SAFE_RELEASE(videoSource);
    SAFE_RELEASE(videoConfig);
    SAFE_RELEASE(videoDevices);
    SAFE_RELEASE(videoReader);
    SAFE_RELEASE(videoSourceOutputType);
    SAFE_RELEASE(pSrcOutMediaType);

    return 0;
}

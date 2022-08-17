// Got code from https://github.com/sipsorcery/mediafoundationsamples/blob/master/MFCaptureRawFramesToFile/MFCaptureRawFramesToFile.cpp

#include <iostream>
#include <fstream>
#include <mfapi.h>
#include <mfidl.h>
#include <mferror.h>
#include <mfreadwrite.h>
#include <wmsdkidl.h>

#include "utility.h"

#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfplay.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "wmcodecdspuuid.lib")

#define FILENAME "output.yuv"
#define SAMPLE_COUNT 100
#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480

#define WEBCAM_INDEX 0

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
    DWORD streamIndex, flags;
    LONGLONG llVideoTimestamp, llSampleDuration;
    int sampleCount = 0;

    std::ofstream outputBuffer(FILENAME, std::ios::out | std::ios::binary);

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
    CHECK_HR(pSrcOutMediaType->SetGUID(MF_MT_SUBTYPE, WMMEDIASUBTYPE_YUY2), "failed to set subtype");
    CHECK_HR(MFSetAttributeSize(pSrcOutMediaType, MF_MT_FRAME_SIZE, FRAME_WIDTH, FRAME_HEIGHT), "Failed to set size");
    CHECK_HR(videoReader->SetCurrentMediaType(0, NULL, pSrcOutMediaType), "failed to set source reader media type");
    std::cout << "Reading video samples from webcam" << std::endl;

    while (sampleCount <= SAMPLE_COUNT)
    {
        CHECK_HR(videoReader->ReadSample(
            MF_SOURCE_READER_FIRST_VIDEO_STREAM,
            0,
            &streamIndex,
            &flags,
            &llVideoTimestamp,
            &videoSample
            ), "Error reading video sample");

        if (flags & MF_SOURCE_READERF_STREAMTICK) {
            std::cout << "Stream tick" << std::endl;
        }

        if (videoSample) {
            std::cout << "Writing sample " << sampleCount << std::endl;
            CHECK_HR(videoSample->SetSampleTime(llVideoTimestamp), "Error setting video sample time");
            CHECK_HR(videoSample->SetSampleDuration(llSampleDuration), "Error setting video sample duration");

            IMFMediaBuffer *buffer = NULL;
            DWORD bufferLength;
            CHECK_HR(videoSample->ConvertToContiguousBuffer(&buffer), "ConvertToContiguousBuffer failed");
            CHECK_HR(buffer->GetCurrentLength(&bufferLength), "Get buffer length failed");

            std::cout << "Sample length " << bufferLength << std::endl;

            byte *byteBuffer;
            DWORD buffCurrLen = 0;
            DWORD buffMaxLen = 0;
            CHECK_HR(buffer->Lock(&byteBuffer, &buffMaxLen, &buffCurrLen), "Failed to lock buffer");

            outputBuffer.write((char *) byteBuffer, bufferLength);
            CHECK_HR(buffer->Unlock(), "Failed to unlock buffer");

            buffer->Release();
            videoSample->Release();
        }

        sampleCount++;
    }

    outputBuffer.close();

done:

    std::cout << "Finished" << std::endl;
    int c = getchar();

    SAFE_RELEASE(videoSource);
    SAFE_RELEASE(videoConfig);
    SAFE_RELEASE(videoDevices);
    SAFE_RELEASE(videoReader);
    SAFE_RELEASE(videoSourceOutputType);
    SAFE_RELEASE(pSrcOutMediaType);
    /*
    IMFMediaSource *ppSource;
    HRESULT hr = CreateVideoCaptureDevice(&ppSource);
    if (!SUCCEEDED(hr)) {
        std::cerr << "Could not create video capture device" << std::endl;
        return 1;
    }

    IMFPresentationDescriptor *presentationDescriptor;
    ppSource->CreatePresentationDescriptor(&presentationDescriptor);
    PROPVARIANT propvariant;
    PropVariantInit(&propvariant);
    propvariant.vt = VT_EMPTY;
    ppSource->Start(
        presentationDescriptor,
        NULL,
        &propvariant
    );

    std::getchar();

    if (ppSource) {
        ppSource->Shutdown();
        ppSource->Release();
        PropVariantClear(&propvariant);
        ppSource = NULL;
    }
     */

    return 0;
}

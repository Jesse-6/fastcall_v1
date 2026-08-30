if ~ defined __PORTAUDIO_INC_INCLUDED__
    define __PORTAUDIO_INC_INCLUDED__
    define __PORTAUDIO_INC_INCLUDED__

    if ~ defined __ELF_MODE_DYNAMIC__
        library 'libportaudio.so.2'
    end if

    struct PA_DEVICE_INFO
        .structVersion              dd ?
                                    dd ?
        .name                       dq ?
        .hostApi                    dd ?
        .maxInputChannels           dd ?
        .maxOutputChannels          dd ?
                                    dd ?
        .defaultLowInputLatency     dq ?
        .defaultLowOutputLatency    dq ?
        .defaultHighInputLatency    dq ?
        .defaultHighOutputLatency   dq ?
        .defaultSampleRate          dq ?
    end struct

    struct PA_HOST_API_INFO
        .structVersion              dd ?
        .type                       dd ?
        .name                       dq ?
        .deviceCount                dd ?
        .defaultInputDevice         dd ?
        .defaulttOutputDevice       dd ?
    end struct

    struct PA_HOST_ERROR_INFO
        .errorCode      dq ?
        .errorText      dq ?
    end struct

    struct PA_STREAM_CALLBACK_TIME_INFO
        .inputBufferAdcTime     dq ?
        .currentTime            dq ?
        .outputBufferDacTime    dq ?
    end struct

    struct PA_STREAM_INFO
        .structVersion              dd ?
                                    dd ?
        .inputLatency               dq ?
        .outputLatency              dq ?
        .sampleRate                 dq ?
    end struct

    struct PA_STREAM_PARAMETERS
        .device                     dd ?
        .channelCount               dd ?
        .sampleFormat               dq ?
        .suggestedLatency           dq ?
        .hostApiSpecificStreamInfo  dq ?
    end struct

    struct PA_VERSION_INFO
        .versionMajor           dd ?
        .versionMinor           dd ?
        .versionSubMinor        dd ?
                                dd ?
        .versionControlRevision dq ?
        .versionText            dq ?
    end struct

    PA_NO_ERROR                                     = 0
    PA_NOT_INITIALIZED                              = -10000
    PA_UNANTICIPATED_HOST_ERROR                     = -9999
    PA_INVALID_CHANNEL_COUNT                        = -9998
    PA_INVALID_SAMPLE_RATE                          = -9997
    PA_INVALID_DEVICE                               = -9996
    PA_INVALID_FLAG                                 = -9995
    PA_SAMPLE_FORMAT_NOT_SUPPORTED                  = -9994
    PA_BAD_IO_DEVICE_COMBINATION                    = -9993
    PA_INSUFFICIENT_MEMORY                          = -9992
    PA_BUFFER_TOO_BIG                               = -9991
    PA_BUFFER_TOO_SMALL                             = -9990
    PA_NULL_CALLBACK                                = -9989
    PA_BAD_STREAM_PTR                               = -9988
    PA_TIMED_OUT                                    = -9987
    PA_INTERNAL_ERROR                               = -9986
    PA_DEVICE_UNAVAILABLE                           = -9985
    PA_INCOMPATIBLE_HOST_API_SPECIFIC_STREAM_INFO   = -9984
    PA_STREAM_IS_STOPPED                            = -9983
    PA_STREAM_IS_NOT_STOPPED                        = -9982
    PA_INPUT_OVERFLOWED                             = -9981
    PA_OUTPUT_UNDERFLOWED                           = -9980
    PA_HOST_API_NOT_FOUND                           = -9979
    PA_INVALID_HOST_API                             = -9978
    PA_CAN_NOT_READ_FROM_A_CALLBACK_STREAM          = -9977
    PA_CAN_NOT_WRITE_TO_A_CALLBACK_STREAM           = -9976
    PA_CAN_NOT_READ_FROM_AN_OUTPUT_ONLY_STREAM      = -9975
    PA_CAN_NOT_WRITE_TO_AN_INPUT_ONLY_STREAM        = -9974
    PA_INCOMPATIBLE_STREAM_HOST_API                 = -9973
    PA_BAD_BUFFER_PTR                               = -9972
    PA_CAN_NOT_INITIALIZE_RECURSIVELY               = -9971


    PA_IN_DEVELOPMENT   = 0
    PA_DIRECT_SOUND     = 1
    PA_MME              = 2
    PA_ASIO             = 3
    PA_SOUND_MANAGER    = 4
    PA_CORE_AUDIO       = 5
    PA_OSS              = 7
    PA_ALSA             = 8
    PA_AL               = 9
    PA_BEOS             = 10
    PA_WDM_KS           = 11
    PA_JACK             = 12
    PA_WASAPI           = 13
    PA_AUDIO_SCIENCE_HPI = 14
    PA_AUDIO_IO         = 15
    PA_PULSE_AUDIO      = 16
    PA_SND_IO           = 17

    PA_CONTINUE         = 0
    PA_COMPLETE         = 1
    PA_ABORT            = 2

    PA_FLOAT32          = 0000_0001h
    PA_INT32            = 0000_0002h
    PA_INT24            = 0000_0004h
    PA_INT16            = 0000_0008h
    PA_INT8             = 0000_0010h
    PA_UINT8            = 0000_0020h
    PA_CUSTOM_FORMAT    = 0001_0000h
    PA_NON_INTERLEAVED  = 8000_0000h

    ext proto Pa_AbortStream, qword
    ext proto Pa_CloseStream, qword
    ext proto Pa_GetDefaultHostApi, none
    ext proto Pa_GetDefaultInputDevice, none
    ext proto Pa_GetDefaultOutputDevice, none
    ext proto Pa_GetDeviceCount, none
    ext proto Pa_GetDeviceInfo, dword
    ext proto Pa_GetErrorText, dword
    ext proto Pa_GetHostApiCount, none
    ext proto Pa_GetHostApiInfo, dword
    ext proto Pa_GetLastHostErrorInfo, none
    ext proto Pa_GetSampleSize, qword
    ext proto Pa_GetStreamCpuLoad, qword
    ext proto Pa_GetStreamInfo, qword
    ext proto Pa_GetStreamReadAvailable, qword
    ext proto Pa_GetStreamTime, qword
    ext proto Pa_GetStreamWriteAvailable, qword
    ext proto Pa_GetVersion, none
    ext proto Pa_GetVersionInfo, none
    ext proto Pa_GetVersionText, none
    ext proto Pa_HostApiDeviceIndexToDeviceIndex, dword, dword
    ext proto Pa_HostApiTypeIdToHostApiIndex, dword
    ext proto Pa_Initialize, none
    ext proto Pa_IsFormatSupported, qword, qword, double
    ext proto Pa_IsStreamActive, qword
    ext proto Pa_IsStreamStopped, qword
    ext proto Pa_OpenDefaultStream, qword, dword, dword, qword, double, qword, qword, qword
    ext proto Pa_OpenStream, qword, qword, qword, double, qword, qword, qword, qword
    ext proto Pa_ReadStream, qword, qword, qword
    ext proto Pa_SetStreamFinishedCallback, qword, qword
    ext proto Pa_Sleep, qword
    ext proto Pa_StartStream, qword
    ext proto Pa_StopStream, qword
    ext proto Pa_Terminate, none
    ext proto Pa_WriteStream, qword, qword, qword

end if
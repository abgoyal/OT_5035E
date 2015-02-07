

#define LOG_TAG "AudioPolicyCompatClient"
//#define LOG_NDEBUG 0

#include <stdint.h>

#include <hardware/hardware.h>
#include <system/audio.h>
#include <system/audio_policy.h>
#include <hardware/audio_policy.h>

#include <hardware_legacy/AudioSystemLegacy.h>

#include "AudioPolicyCompatClient.h"

namespace android_audio_legacy {

audio_io_handle_t AudioPolicyCompatClient::openOutput(uint32_t *pDevices,
                                uint32_t *pSamplingRate,
                                uint32_t *pFormat,
                                uint32_t *pChannels,
                                uint32_t *pLatencyMs,
                                AudioSystem::output_flags flags)
{
    return mServiceOps->open_output(mService, pDevices, pSamplingRate, pFormat,
                                    pChannels, pLatencyMs,
                                    (audio_policy_output_flags_t)flags);
}

audio_io_handle_t AudioPolicyCompatClient::openDuplicateOutput(audio_io_handle_t output1,
                                                          audio_io_handle_t output2)
{
    return mServiceOps->open_duplicate_output(mService, output1, output2);
}

status_t AudioPolicyCompatClient::closeOutput(audio_io_handle_t output)
{
    return mServiceOps->close_output(mService, output);
}

status_t AudioPolicyCompatClient::suspendOutput(audio_io_handle_t output)
{
    return mServiceOps->suspend_output(mService, output);
}

status_t AudioPolicyCompatClient::restoreOutput(audio_io_handle_t output)
{
    return mServiceOps->restore_output(mService, output);
}

audio_io_handle_t AudioPolicyCompatClient::openInput(uint32_t *pDevices,
                                uint32_t *pSamplingRate,
                                uint32_t *pFormat,
                                uint32_t *pChannels,
                                uint32_t acoustics)
{
    return mServiceOps->open_input(mService, pDevices, pSamplingRate, pFormat,
                                   pChannels, acoustics);
}

status_t AudioPolicyCompatClient::closeInput(audio_io_handle_t input)
{
    return mServiceOps->close_input(mService, input);
}

status_t AudioPolicyCompatClient::setStreamOutput(AudioSystem::stream_type stream,
                                             audio_io_handle_t output)
{
    return mServiceOps->set_stream_output(mService, (audio_stream_type_t)stream,
                                          output);
}

status_t AudioPolicyCompatClient::moveEffects(int session, audio_io_handle_t srcOutput,
                                               audio_io_handle_t dstOutput)
{
    return mServiceOps->move_effects(mService, session, srcOutput, dstOutput);
}

String8 AudioPolicyCompatClient::getParameters(audio_io_handle_t ioHandle, const String8& keys)
{
    char *str;
    String8 out_str8;

    str = mServiceOps->get_parameters(mService, ioHandle, keys.string());
    out_str8 = String8(str);
    free(str);

    return out_str8;
}

void AudioPolicyCompatClient::setParameters(audio_io_handle_t ioHandle,
                                            const String8& keyValuePairs,
                                            int delayMs)
{
    mServiceOps->set_parameters(mService, ioHandle, keyValuePairs.string(),
                           delayMs);
}

status_t AudioPolicyCompatClient::setStreamVolume(
                                             AudioSystem::stream_type stream,
                                             float volume,
                                             audio_io_handle_t output,
                                             int delayMs)
{
    return mServiceOps->set_stream_volume(mService, (audio_stream_type_t)stream,
                                          volume, output, delayMs);
}

status_t AudioPolicyCompatClient::startTone(ToneGenerator::tone_type tone,
                                       AudioSystem::stream_type stream)
{
    return mServiceOps->start_tone(mService,
                                   AUDIO_POLICY_TONE_IN_CALL_NOTIFICATION,
                                   (audio_stream_type_t)stream);
}

status_t AudioPolicyCompatClient::stopTone()
{
    return mServiceOps->stop_tone(mService);
}

status_t AudioPolicyCompatClient::setVoiceVolume(float volume, int delayMs)
{
    return mServiceOps->set_voice_volume(mService, volume, delayMs);
}

}; // namespace android_audio_legacy
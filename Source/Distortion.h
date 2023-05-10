/*
  ==============================================================================

    Distortion.h
    Created: 10 May 2023 8:53:42am
    Author:  Roba

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

template <typename SampleType>
class Distortion
{
public:

    Distortion();

    void prepare(juce::dsp::ProcessSpec& spec);

    void reset();

    template <typename ProcessContext>
    void process(const ProcessContext& context) noexcept
    {
        const auto& inputBlock = context.getInputBlock();
        auto& outputBlock = context.getOutputBlock();
        const auto numChannels = outputBlock.getNumChannels();
        const auto numSamples = outputBlock.getNumSamples();

        jassert(inputBlock.getNumChannels() == numChannels);
        jassert(inputBlock.getNumSamples() == numSamples);

        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            auto* inputSamples = inputBlock.getChannelPointer(channel);
            auto* outputSamples = outputBlock.getChannelPointer(channel);

            for (size_t i = 0; i < numSamples; ++i)
            {
                outputSamples[i] = processSample(inputSamples[i]);
            }
        }
    }

    SampleType processSample(SampleType inputSample) noexcept
    {
        switch (_model)
        {
            case DistortionModel::kHard:
            {
                return processHardClipper(inputSample);
                break;
            }

            case DistortionModel::kSoft:
            {
                return processSoftClipper(inputSample);
                break;
            }

            case DistortionModel::kSaturation:
            {
                return processSaturationClipper(inputSample);
                break;
            }
        }
    }

    /*
        Take any signal above 0dB,
        and map it down
    */
    SampleType processHardClipper(SampleType inputSample)
    {
        // Apply the input gain to the sample
        float wetSignal = inputSample * _input.getNextValue();

        // Check if the absolute value of the wetSignal is greater than 0.99 (0 dB)
        if (std::abs(wetSignal) > 0.99)
        {
            wetSignal = 1.0 / std::abs(wetSignal);
        }

        // Calculate the mix between the original input signal and the distorted signal
        // by using the _mix parameter (ranging from 0 to 1)
        auto mix = (1.0 - _mix.getNextValue()) * inputSample + wetSignal * _mix.getNextValue();

        // Apply the output gain and return the resulting audio sample
        return mix * _output.getNextValue();
    }

    SampleType processSoftClipper(SampleType inputSample)
    {
        return inputSample;
    }

    SampleType processSaturationClipper(SampleType inputSample)
    {
        return inputSample;
    }

    enum class DistortionModel
    {
        kHard,
        kSoft,
        kSaturation
    };

    void setDrive(SampleType newDrive);
    void setMix(SampleType newMix);
    void setOutput(SampleType newOutput);

    void setDistortionModel(DistortionModel newModel);

private:
    juce::SmoothedValue<float> _input;
    juce::SmoothedValue<float> _mix;
    juce::SmoothedValue<float> _output;

    float _sampleRate = 44100.0f;

    DistortionModel _model = DistortionModel::kHard;
};

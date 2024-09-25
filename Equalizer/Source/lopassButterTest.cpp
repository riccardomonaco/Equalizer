/*
  ==============================================================================

    lopassButterTest.cpp
    Created: 25 Sep 2024 8:21:38am
    Author:  Dev

  ==============================================================================
*/
#define _USE_MATH_DEFINES

#include <JuceHeader.h>
#include <cmath>
#include "lopassButterTest.h"

//==============================================================================

lopassButterTest::lopassButterTest(double cutoffFreq)
{
    this->sampleRate = 44100;
    this->cutoffFreq = cutoffFreq;
    bCoefficients = juce::dsp::IIR::Coefficients<double>::makeLowPass(sampleRate, cutoffFreq);
    bFilter = juce::dsp::IIR::Filter<double>::Filter(bCoefficients);
}

lopassButterTest::~lopassButterTest()
{
    this->sampleRate = 44100;
    this->cutoffFreq = 1000;
    bCoefficients = juce::dsp::IIR::Coefficients<double>::makeLowPass(sampleRate, cutoffFreq);
    bFilter = juce::dsp::IIR::Filter<double>::Filter(bCoefficients);
}

void lopassButterTest::updateCoefficients()
{    
    double pig = 3.14;
    // Calcolo del periodo di campionamento
    double T = 1.0 / sampleRate;

    // Frequenza angolare di taglio
    double omegaC = 2.0 * pig * this->cutoffFreq;

    // Trasformazione bilineare dei poli
    double k = 2.0 / T;

    // Polinomio Butterworth di terzo ordine: i poli si trovano a 60°, 120° e 180° gradi nel piano complesso
    double theta1 = pig / 6.0;  // 30° in radianti
    double theta2 = pig / 2.0;  // 90° in radianti
    double theta3 = 5.0 * pig / 6.0;  // 150° in radianti

    // Polinomio analogico (poli nel semicerchio sinistro)
    std::complex<double> p1 = std::polar(omegaC, theta1);
    std::complex<double> p2 = std::polar(omegaC, theta2);
    std::complex<double> p3 = std::polar(omegaC, theta3);

    // Trasformiamo i poli tramite la trasformazione bilineare
    std::complex<double> z1 = (k + p1) / (k - p1);
    std::complex<double> z2 = (k + p2) / (k - p2);
    std::complex<double> z3 = (k + p3) / (k - p3);

    // Calcolo dei coefficienti del filtro IIR usando i poli digitali
    double b0 = 1.0; // Il numeratore è normalizzato
    double b1 = -2.0 * (z1.real() + z2.real() + z3.real());
    double b2 = 2.0 * (z1.real() * z2.real() + z1.real() * z3.real() + z2.real() * z3.real());
    double b3 = -2.0 * z1.real() * z2.real() * z3.real();
    double a0 = 1.0;
    double a1 = -(z1.real() + z2.real() + z3.real());
    double a2 = z1.real() * z2.real() + z1.real() * z3.real() + z2.real() * z3.real();
    double a3 = -z1.real() * z2.real() * z3.real();

    // Normalizzazione del numeratore (il filtro è passa-basso)
    b1 /= a0;
    b2 /= a0;
    b3 /= a0;
    a1 /= a0;
    a2 /= a0;
    a3 /= a0;
}

double lopassButterTest::processSample(double currSample)
{
    return bFilter.processSample(currSample);
}
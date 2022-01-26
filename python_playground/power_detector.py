#!/usr/bin/env python3

import sys
import argparse
import numpy as np

parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter,
                                 description='Extract and print power in dB from I/Q stream.',
                                 epilog='''

Examples: Find peak power of signal at 1296.050 MHz within a bandwidth of 5 kHz.
          SDR frontend runs with a center frequency of 1296 MHz and a sampling rate of 250 kHz.

          rtl_sdr -f 1296000000 -s 250000 -g 30 -| python3 power_detector.py -f 1296000000 -s 250000 -t 1296050000 --bw 5000 --uint8


          Find peak power of signal at 29.050 MHz within a bandwidth of 1 kHz.
          SDR frontend runs with a center frequency of 29 MHz and a sampling rate of 250 kHz.

          rtl_sdr -f 29000000 -s 250000 -g 30 -| python3 power_detector.py -f 29000000 -s 250000 -t 29050000 --bw 1000 --uint8

          Hints:
          - Do not use preamp AGC feature (-g 0)
          - Running at low sampling rates (e.g. 250 kHz) will speed up computation.
          - Results are in dB with no real world reference (unless calibrated).
          - Detector window (target signal freq. +/- bw/2) must be above SDR center frequency.
          - You can use, e.g., osmocom_fft to dial in the parameters roughly.
          - Parameters -f and -s must match!
          - -f and -s must be given to rtl_sdr for the hardware and also to power_detector.py since it needs to know about those settings.
          - Use --uint8 for 8-bit I/Q streams (e.g. from the rtl_sdr tool). Two 32 bit floats are expected otherwise.
          - Abort with ctrl-c
''')

parser.add_argument('-s',   type=int,   metavar = 'FS',               required=True, help='SDR frontend sampling rate in Hz')
parser.add_argument('-f',   type=int,   metavar = 'center_frequency', required=True, help='SDR center frequency in Hz')
parser.add_argument('-t',   type=int,   metavar = 'signal_frequency', required=True, help='Frequency of the target signal in Hz')
parser.add_argument('--bw', type=float, metavar = 'BW',               default=10000, help='Detector bandwidth in Hz. We look for the peak power within that window.\nDefault: 10000 (10 kHz)')
parser.add_argument('--integration-time', type=float, metavar = 'T',  default=1,     help='Integration time in s. Default: 1 second.')
parser.add_argument('--uint8', action='store_true', help='I/Q stream is two uint8 instead of two 32 bit floats.')
args = parser.parse_args()

fs               = args.s
center_freq      = args.f
target_freq      = args.t
detector_bw      = args.bw
integration_time = args.integration_time

# Calculations for internal use
baseband_freq =  target_freq - center_freq
n = int(fs * integration_time)
target_bin_low  = int(n * (baseband_freq-detector_bw/2)/fs)
target_bin_high = int(n * (baseband_freq+detector_bw/2)/fs)
if target_bin_low < 0:
    # We don't allow this because we don't want to rearrange the frequency bins and
    # doing this right for detectors that overlap with baseband DC will be annoyingly tricky.
    #target_bin_low  += n//2
    #target_bin_high += n//2
    print('Signal of interest must be fully contained in the positive half of the baseband spectrum. Aborting.')
    sys.exit(1)

#FFT_WINDOW = np.ones_like(signal) # Use this for rectangular FFT window
FFT_WINDOW  = np.hamming(n)
FFT_WINDOW /= np.sum(FFT_WINDOW) # Normalize

while True:
    if args.uint8:
        # We read two bytes per sample; one for I and one for Q.
        raw_signal = np.frombuffer(sys.stdin.buffer.read(2*n), dtype=np.uint8)
        # Extract I and Q
        i_signal = raw_signal[0::2]/255.
        q_signal = raw_signal[1::2]/255.
        signal = i_signal + 1j*q_signal
    else:
        # We read 8*n bytes since each sample is a complex number consisting of two floats (i.e. 2*4 bytes)
        signal = np.frombuffer(sys.stdin.buffer.read(8*n), dtype=np.complex64)
    if len(signal) != n: break
    spectrum = np.abs(np.fft.fft(signal*FFT_WINDOW, n))
    spectrum_windowed = spectrum[target_bin_low:target_bin_high]
    #power = np.max(spectrum_windowed)
    power = np.max(20*np.log10(spectrum_windowed))
    print(power)
    #plt.plot(spectrum,'*')
    #plt.plot(f,spectrum,'*')
    #plt.show()

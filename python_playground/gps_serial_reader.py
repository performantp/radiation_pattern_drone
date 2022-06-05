#!/usr/bin/env python3
from nmea import input_stream, data_frame

#setup issue: nmea folder needs to be copied separately from repo, otherwise it will complain about not finding 'nmea' in '.'core'
#see here https://gitlab.com/bek3/nmea_parser/-/issues/37

# this is an example of using the nmea-parser module to get the desired data form a nmea sentences over a serial port
stream = input_stream.GenericInputStream.open_stream('/dev/tnt1')

with stream:
    # while data_frame.DataFrame:
        new_frame = data_frame.DataFrame.get_next_frame(stream)

        print("Fix Quality:", new_frame.fix_quality)
        print("Current GPS time:", new_frame.gps_time)
        print("Current Latitude:", new_frame.latitude)
        print("Current Longitude:", new_frame.longitude)
        print("Current Altitude:", new_frame.altitude)
        print("Current Speed:", new_frame.velocity)
        print("Current heading:", new_frame.track)

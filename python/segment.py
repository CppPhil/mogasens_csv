#!/usr/bin/env python3
# -*- coding: utf8 -*-

import argparse
import sys
import os

from modules.data_set import DataSet
from modules.segmentation_kind import *
from modules.sensors import sensors
from modules.constants import *
from plotter import main_impl as plotter_main


def validate_sensor(sensor):
  if sensor not in sensors():
    print(f"segment.py: {sensor} is not a valid sensor.", file=sys.stderr)
    return False
  return True


def validate(csv_file_path, sensor, channel, segmentation_kind, window_size):
  if not os.path.isfile(csv_file_path):
    print(f"segment.py: \"{csv_file_path}\" is not a file.", file=sys.stderr)
    return False

  if not validate_sensor(sensor):
    return False

  if channel not in range(1, 7):
    print(
        f"segment.py: {channel} is not a valid channel, must be within 1 - 6.",
        file=sys.stderr)
    return False

  try:
    segmentation_kind_from_str(segmentation_kind)
  except Exception:
    print(
        f"segment.py: \"{segmentation_kind}\" is not a valid segmentation kind.",
        file=sys.stderr)
    return False

  if window_size < 3:
    print(
        f"segment.py: window size was {window_size}, but must be at least 3!",
        file=sys.stderr)
    return False

  if not window_size % 2 == 1:
    print(
        f"segment.py: window size {window_size} is an even number, but an odd number is required.",
        file=sys.stderr)
    return False

  return True


def delete_too_close_segmenting_hardware_timestamps(
    segmenting_hardware_timestamps):
  minimum_distance_milliseconds = 325

  maximum_index = len(segmenting_hardware_timestamps) - 1
  current_index = 0

  while current_index != maximum_index:
    current_value = segmenting_hardware_timestamps[current_index]
    next_value = segmenting_hardware_timestamps[current_index + 1]
    distance = next_value - current_value

    if distance < minimum_distance_milliseconds:
      segmenting_hardware_timestamps.pop(current_index)
      maximum_index -= 1
    else:
      current_index += 1


def main(arguments):
  parser = argparse.ArgumentParser(description='Segment a MoGaSens CSV file.')
  parser.add_argument('--image_format',
                      type=str,
                      help='The image format to use e.g. svg',
                      default='png',
                      required=False)
  parser.add_argument('--csv_file_path',
                      type=str,
                      help='Path to the CSV file to segment.',
                      required=True)
  parser.add_argument('--sensor',
                      type=int,
                      help='The sensor to use (769 | 770 | 771 | 772)',
                      required=True)
  parser.add_argument('--channel',
                      type=int,
                      help='The channel to use (1 | 2 | 3 | 4 | 5 | 6)',
                      required=True)
  parser.add_argument('--segmentation_kind',
                      type=str,
                      help='The segmentation kind to use (min | max | both)',
                      required=True)
  parser.add_argument('--window_size',
                      type=int,
                      help='The window size to use for segmenting.',
                      required=True)
  args = parser.parse_args(arguments)
  csv_file_path = args.csv_file_path
  sensor = args.sensor
  channel = args.channel
  segmentation_kind = args.segmentation_kind
  window_size = args.window_size

  if not validate(csv_file_path, sensor, channel, segmentation_kind,
                  window_size):
    sys.exit(1)

  entire_data_set = DataSet.from_file(csv_file_path)
  desired_sensor_data_set = entire_data_set.filter_by_sensor(sensor)
  segmenting_hardware_timestamps = desired_sensor_data_set.segmenting_hardware_timestamps(
      f"channel{channel}", segmentation_kind_from_str(segmentation_kind),
      window_size)

  print(
      f"segment.py: {len(segmenting_hardware_timestamps)} segmentation points found in \"{csv_file_path}\" (before deleting too close ones)."
  )

  delete_too_close_segmenting_hardware_timestamps(
      segmenting_hardware_timestamps)

  print(
      f"segment.py: {len(segmenting_hardware_timestamps)} segmentation points found in \"{csv_file_path}\" (after deleting too close ones)."
  )

  imus = [accelerometer_string(), gyroscope_string()]

  for sensor in sensors():
    for imu in imus:
      plotter_main(
          arguments=[
              '--image_format',
              args.image_format,
              '--no-moving_average_filter',  # Don't use a filter
              '--time_based_split',  # Time based split setting
              csv_file_path,  # Path to the entire CSV file
              f'{sensor}',  # The sensor (left arm, belly, right arm, chest)
              imu,  # The imu (accelerometer / gyroscope)
              '0'  # Filter sample count (must be 0 if none is used)
          ],
          segmenting_hwstamps=segmenting_hardware_timestamps)

  print("segment.py: Done.")
  sys.exit(0)


if __name__ == "__main__":
  main(sys.argv[1:])

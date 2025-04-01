"""
Finds Numbers of groups of oscillators at the very last time period of the simulation
"""

import re
import os
import math as ma
import pandas as pd
import numpy as np


DIRECTORY = "/home/pine/Code/Sync/data"
FILE = "projectdata_20o7e3l2n1.txt"

FILE_PATH = os.path.join(DIRECTORY, FILE)

match = re.search(r"projectdata_(\d+)o(\d+)e(\d+)l(\d+)n(\d+)\.txt", FILE_PATH)
if match:
    s0 = int(match.group(1))
    gamma = int(match.group(2)) * 0.1
    epsilon = int(match.group(3))
    print(f"S0: {s0}, Gamma: {gamma}, Epsilon: {epsilon}")
else:
    print(f"Filename format does not match for file: {FILE}")

# Calculate intrinsic period
intrinsic_period = np.log(s0 / (s0 - gamma))
intrinsic_period *= 1 / gamma
intrinsic_period *= 1000

# Read the text file into a DataFrame
df = pd.read_csv(FILE_PATH, delim_whitespace=True, header=0)

num_rows = df.shape[0]
num_cols = df.shape[1]

# Count the number of oscillators above the threshold
above_threshold = df >= 1.0
oscillators_above_threshold = above_threshold.sum(axis=1)

amount_of_periods = ma.floor(num_rows / intrinsic_period)

upper_bound = amount_of_periods * intrinsic_period
lower_bound = (amount_of_periods - 1) * intrinsic_period

i = int(lower_bound)
NUM_GROUPS = 0
NUM = 0

while i < upper_bound:
    if oscillators_above_threshold.iloc[i] > 0:
        NUM_GROUPS += 1
    NUM += oscillators_above_threshold.iloc[i]
    if NUM == num_cols:
        break
    i += 1

print(f"Number of groups of oscillators: {NUM_GROUPS}")
print(f"Upper bound: {upper_bound}")
print(f"Lower bound: {lower_bound}")

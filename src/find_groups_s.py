"""
Finds the number of groups of oscillators at the very last time period of the simulation.
"""

import os
import glob as gl
import math as ma
import re               g\  
import ctypes as ct
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

# Load the shared library
current_dir = os.path.dirname(os.path.abspath(__file__))
lib_path = os.path.join(current_dir, "../lib/libdefines.so")
lib = ct.CDLL(lib_path)
lib.get_delta_time.restype = ct.c_double

# Retrieve delta_time from the shared library
delta_time = lib.get_delta_time()

# Define constants and file paths
DIRECTORY = "/home/pine/Code/Sync/data"
FILE = "projectdata_*o9e10l2n1.txt"
FILE_PATH = gl.glob(os.path.join(DIRECTORY, FILE))

# Initialize variables
NUM_FILES = 0
results_df = pd.DataFrame(columns=["S0", "NUM_GROUPS"])

# Process each file in the directory
for file in FILE_PATH:
    # Initialize parameters
    gamma = 0
    epsilon = 0
    s0 = 0

    # Extract parameters from the filename
    match = re.search(r"projectdata_(\d+)o(\d+)e(\d+)l(\d+)n(\d+)\.txt", file)
    if match:
        s0 = int(match.group(1))
        gamma = int(match.group(2)) * 0.1
        epsilon = int(match.group(3)) * 0.01
    else:
        print(f"Filename format does not match for file: {file}")
        continue

    # Calculate intrinsic period
    try:
        intrinsic_period = np.log(s0 / (s0 - gamma))
        intrinsic_period *= 1 / gamma
        intrinsic_period *= 1 / delta_time
    except ZeroDivisionError:
        print(f"Error: Division by zero encountered in file {file}.")
        continue
    except ValueError as e:
        print(f"Error: Invalid value encountered in file {file}: {e}")
        continue

    # Read the text file into a DataFrame
    try:
        df = pd.read_csv(file, sep=r"\s+", header=0)
    except (FileNotFoundError, pd.errors.ParserError) as e:
        print(f"Error reading file {file}: {e}")
        continue

    # Analyze the data
    num_rows = df.shape[0]
    num_cols = df.shape[1]
    above_threshold = df >= 1.0
    oscillators_above_threshold = above_threshold.sum(axis=1)

    # Calculate the number of periods
    try:
        amount_of_periods = ma.floor(num_rows / intrinsic_period)
        if amount_of_periods <= 0:
            print(
                f"Skipping file {file} because amount_of_periods ({amount_of_periods}) is invalid."
            )
            continue
    except (ValueError, OverflowError) as e:
        print(f"Error calculating amount_of_periods for file {file}: {e}")
        continue

    # Determine bounds for analysis
    upper_bound = amount_of_periods * intrinsic_period
    lower_bound = (amount_of_periods - 1) * intrinsic_period

    i = int(lower_bound)
    NUM_GROUPS = 0
    NUM = 0

    # Count the number of groups of oscillators
    while i < upper_bound:
        if oscillators_above_threshold.iloc[i] > 0:
            NUM_GROUPS += 1
        NUM += oscillators_above_threshold.iloc[i]
        if NUM == num_cols:
            break
        i += 1

    # Store results in the DataFrame
    results_df.loc[len(results_df)] = {"S0": s0, "NUM_GROUPS": NUM_GROUPS}
    NUM_FILES += 1

# Set Seaborn style and font size
sns.set(style="whitegrid")
sns.set_context("notebook", font_scale=1.6)  # Font size 16

# Create the plot
plt.figure(figsize=(5, 3.75))  # Set figure size to 5x3.75 inches
sns.lineplot(data=results_df, x="S0", y="NUM_GROUPS", marker="o", color="b")

# Add titles and labels
plt.title("Number of Groups vs S0", fontsize=16)
plt.xlabel("S0", fontsize=16)
plt.ylabel("Number of Groups", fontsize=16)

# Set axes to start at 0
# Extend x-axis slightly beyond max S0
plt.xlim(left=0, right=results_df["S0"].max() + 2)
# Extend y-axis slightly beyond max NUM_GROUPS
plt.ylim(bottom=0, top=results_df["NUM_GROUPS"].max() + 1)

# Set x-axis ticks to increment by 0.01
plt.xticks(np.arange(0, results_df["S0"].max() + 2, 2))

# Set y-axis ticks to increment by 1
plt.yticks(range(0, int(results_df["NUM_GROUPS"].max()) + 2, 2))

# Show the plot
plt.tight_layout()  # Adjust layout to fit everything nicely
plt.show()

"""
This module reads the text files containing the simulation data and plots the data.
The plots are saved as HTML files in the graphs directory.
"""

import glob
import os
import re
import pandas as pd
import plotly.express as px
import plotly.graph_objects as go
import numpy as np

# Define the file path containing the data
FILE_PATH = r"/home/pine/Code/Sync/data"

# Find all files matching the pattern "projectdata_2*.txt"
group_files = glob.glob(os.path.join(FILE_PATH, "projectdata_2o7e3l2n3.txt"))

for file in group_files:
    # Extract x, y, and z values from the filename using a regular expression
    match = re.search(
        r"projectdata_(\d+)o(\d+)e(\d+)l(\d+)n(\d+)\.txt", file
    )

    if match:
        s0 = int(match.group(1))
        gamma = int(match.group(2)) * 0.1
        epsilon = int(match.group(3))
        print(f"S0: {s0}, Gamma: {gamma}, Epsilon: {epsilon}")
    else:
        print(f"Filename format does not match for file: {file}")
        continue

    # Read the text file into a DataFrame
    df = pd.read_csv(file, delim_whitespace=True, header=0)

    num_rows = df.shape[0]
    num_cols = df.shape[1]

    # Count the number of oscillators above the threshold
    above_threshold = df >= 1.0
    counts = above_threshold.sum(axis=1)

    # Extract column names for plotting
    fig3_x = df.columns
    row1 = df.loc[45000]
    row2 = df.loc[10000]
    row3 = df.loc[1000]

    # Calculate intrinsic period
    intrinsicPeriod = np.log(s0 / (s0 - gamma))
    intrinsicPeriod *= 1 / gamma

    # Create a time column
    df["Time"] = df.index / 100.0  # Assuming data is in 100 Hz

    # Melt the DataFrame to have a long format for plotting
    df_melted = df.melt(id_vars=["Time"], var_name="Oscillator", value_name="Voltage")

    # Plot the oscillator voltage vs. time
    fig = px.line(
        df_melted,
        x="Time",
        y="Voltage",
        color="Oscillator",
        title="Oscillator Voltage vs Time",
    )

    # Plot the number of oscillators above threshold
    fig2 = px.bar(counts, title="Number of Oscillators above Threshold")

    # Plot the voltage of three oscillators vs. time
    fig3 = go.Figure()
    fig3.add_trace(go.Scatter(x=fig3_x, y=row1, mode="lines", name="Oscillator 1"))
    fig3.add_trace(go.Scatter(x=fig3_x, y=row2, mode="lines", name="Oscillator 2"))
    fig3.add_trace(go.Scatter(x=fig3_x, y=row3, mode="lines", name="Oscillator 3"))

    # Calculate the average of the differences in firing times inside the moving intrinsic period
    windowSize = int(
        intrinsicPeriod * 1000
    )  # Convert intrinsic period to number of samples (assuming 100 Hz)
    averageDifferences = []
    timePeriods = []

    i = 0
    k = 0
    averageValue = []
    averageIndex = []
    standardDeviation = []
    INITIAL_SKIP = 1

    while i < (num_rows - windowSize):
        INITIAL_SKIP = 0
        WINDOW_START = i
        windowEnd = WINDOW_START + windowSize
        j = WINDOW_START
        VAL = 0
        NUM = 0
        VAL_SQUARED = 0
        while j < windowEnd:
            VAL += counts.iloc[j] * (j - WINDOW_START)
            VAL_SQUARED += counts.iloc[j] * (j - WINDOW_START) * (j - WINDOW_START)
            NUM += counts.iloc[j]
            j += 1
            if NUM == num_cols:
                break
        mean = VAL / NUM
        variance = (VAL_SQUARED - (2 * mean * VAL) + (NUM * (mean * mean))) / NUM
        stdDev = np.sqrt((variance))
        averageValue.append(mean)
        standardDeviation.append(stdDev)
        averageIndex.append(k)
        k += 1
        i += windowSize
    # Create a DataFrame for the average differences and their corresponding time periods

    # Plot the average differences vs. time periods
    fig4 = go.Figure()
    fig4.add_trace(
        go.Scatter(x=averageIndex, y=averageValue, mode="lines", name="Mean")
    )

    fig5 = go.Figure()
    fig5.add_trace(
        go.Scatter(
            x=averageIndex, y=standardDeviation, mode="lines", name="Standard Deviation"
        )
    )

    fileName = os.path.basename(file)
    graphLocation = "./graphs/" + fileName.replace(".txt", "")

    fig.update_layout(width=24 * 37.7953, height=20 * 37.7953, font=dict(size=30))
    fig2.update_layout(width=24 * 37.7953, height=20 * 37.7953, font=dict(size=30))
    fig3.update_layout(width=24 * 37.7953, height=20 * 37.7953, font=dict(size=30))
    fig4.update_layout(width=24 * 37.7953, height=20 * 37.7953, font=dict(size=30))
    fig5.update_layout(width=24 * 37.7953, height=20 * 37.7953, font=dict(size=30))

    fig5.write_html(graphLocation + "_stdDev.html")
    fig4.write_html(graphLocation + "_mean.html")
    fig3.write_html(graphLocation + "_oscillator.html")
    fig2.write_html(graphLocation + "_threshold.html")
    fig.write_html(graphLocation + "_voltage.html")

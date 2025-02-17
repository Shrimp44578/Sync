import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

# Read the text file into a DataFrame, using the first row as column names
file_path = r'./data/test.txt'
df = pd.read_csv(file_path, delim_whitespace=True, header=0)

# Create a time column
df['Time'] = df.index / 100.0  # Assuming data is in 100 Hz

# Set up the figure and axis
fig, ax = plt.subplots()
ax.set_xlim(0, df.shape[1] - 1)
ax.set_ylim(0, df.shape[1] - 1)

# Create a grid of squares
grid_size = int(np.sqrt(df.shape[1]))
squares = np.zeros((grid_size, grid_size))

# Function to update the grid
def update(frame):
    ax.clear()
    ax.set_xlim(0, grid_size - 1)
    ax.set_ylim(0, grid_size - 1)
    time_step = df.iloc[frame]
    for i in range(grid_size):
        for j in range(grid_size):
            if time_step[i * grid_size + j] >= 1.0:
                squares[i, j] = 1
            else:
                squares[i, j] = 0
    ax.imshow(squares, cmap='gray', vmin=0, vmax=1)

# Create the animation
ani = animation.FuncAnimation(fig, update, frames=len(df), repeat=False)

# Show the plot
plt.show()
import pandas as pd
import plotly.express as px
import plotly.graph_objects as go

# Read the text file into a DataFrame, using the first row as column names
file_path = r'C:\Users\smchi\Sync\data\sync8.txt'
df = pd.read_csv(file_path, delim_whitespace=True, header=0)

# Count the number of oscillators above threshold
above_threshold = df >= 1.0
counts  = above_threshold.sum(axis = 1)
fig3_x = df.columns
row1 = df.loc[100]
row2 = df.loc[4000]
row3 = df.loc[8000]

# Create a time column
df['Time'] = df.index / 100.0  # Assuming data is in 100 Hz

# Melt the DataFrame to have a long format for plotting
df_melted = df.melt(id_vars=['Time'], var_name='Oscillator', value_name='Voltage')

# Plot the oscillator voltage vs. time
fig = px.line(df_melted, x='Time', y='Voltage', color='Oscillator', title='Oscillator Voltage vs Time')
fig.show()

# Plot the number of oscillators above threshold
fig2 = px.bar(counts, title='Number of Oscillators above Threshold')
fig2.show()
 
# Plot the voltage of three oscillators vs. time
fig3 = go.Figure()
fig3.add_trace(go.Scatter(x=fig3_x, y=row1, mode='lines', name='Oscillator 1'))
fig3.add_trace(go.Scatter(x=fig3_x, y=row2, mode='lines', name='Oscillator 2'))
fig3.add_trace(go.Scatter(x=fig3_x, y=row3, mode='lines', name='Oscillator 3'))
fig3.show()

# Save the plot as an HTML file
fig.write_html('oscillator_voltage_vs_time.html')
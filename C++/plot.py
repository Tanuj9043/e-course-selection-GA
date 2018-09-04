import plotly
plotly.tools.set_credentials_file(username='tanuj_drall', api_key='TNayiqfBMR4aElrcT8N8')
from plotly import tools
import plotly.plotly as py
import plotly.graph_objs as go

import pandas as pd

df = pd.read_csv('graph.csv')

trace1 = go.Scatter(x=df['Generation'], y=df['Fitmax'])
trace2 = go.Scatter(x=df['Generation'], y=df['Fitness'])

fig = tools.make_subplots(rows=2, cols=1, specs=[[{}], [{}]],
                          shared_xaxes=True, shared_yaxes=True,
                          vertical_spacing=0.001)
fig.append_trace(trace1, 1, 1)
fig.append_trace(trace2, 2, 1)

py.iplot(fig, filename='genetic-algorithm')
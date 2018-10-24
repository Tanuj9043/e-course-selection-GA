import plotly
plotly.tools.set_credentials_file(username='tanuj_drall', api_key='TNayiqfBMR4aElrcT8N8')
from plotly import tools
import plotly.plotly as py
import plotly.graph_objs as go

import pandas as pd

df = pd.read_csv('graph.csv')

trace1 = go.Scatter(x=df['Generation'], y=df['Fitmax'], name="Maximum Fitness")
trace2 = go.Scatter(x=df['Generation'], y=df['Fitness'], name="Average Fitness")

fig = tools.make_subplots(rows=2, cols=1, specs=[[{}], [{}]],
                          shared_xaxes=True, shared_yaxes=True,
                          vertical_spacing=0.001)
fig.append_trace(trace1, 1, 1)
fig.append_trace(trace2, 2, 1)

#fig['layout'].update(title='1000 Population Size')
fig['layout']['xaxis1'].update(title='Generation')

py.iplot(fig, filename='genetic-algorithm')
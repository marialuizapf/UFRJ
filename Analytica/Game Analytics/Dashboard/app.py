from pathlib import Path

import pandas as pd
import plotly.express as px
import plotly.graph_objects as go
from dash import Dash, dcc, html, dash_table
from data_loader import load_csv

df_combat, df_input, df_position, df_session = load_csv(300)

df_session["duration_min"] = df_session["duration_ms"] / 60000

combat_counts = df_combat["action"].value_counts().reset_index()
combat_counts.columns = ["action", "count"]

input_counts = df_input["input"].value_counts().reset_index()
input_counts.columns = ["input", "count"]

position_sample = df_position.sample(min(3000, len(df_position)), random_state=1)

template = "plotly_dark"

fig_combat = px.bar(
    combat_counts,
    x="action",
    y="count",
    title="Eventos de combate"
)
fig_combat.update_layout(template=template, paper_bgcolor="#111827", plot_bgcolor="#111827")

fig_input = px.bar(
    input_counts,
    x="input",
    y="count",
    title="Inputs mais usados"
)
fig_input.update_layout(template=template, paper_bgcolor="#111827", plot_bgcolor="#111827")

fig_position = px.scatter(
    position_sample,
    x="position_x",
    y="position_y",
    title="Mapa simples de posições",
    opacity=0.4
)
fig_position.update_layout(template=template, paper_bgcolor="#111827", plot_bgcolor="#111827")


def card(title, value):
    return html.Div(
        className="metric-card",
        children=[
            html.H3(title),
            html.P(value)
        ]
    )


app = Dash(__name__)

app.layout = html.Div(
    className="page",
    children=[
        html.Div(
            className="header",
            children=[
                html.Div([
                    html.H1("Game Analytics Dashboard"),
                ])
            ]
        ),

        html.Div(
            className="metrics-grid",
            children=[
                card("Sessões", df_session["session_id"].nunique()),
                card("Jogadores", df_session["player_id"].nunique()),
                card("Duração média", f"{df_session['duration_min'].mean():.1f} min"),
                card("Eventos de combate", len(df_combat)),
                card("Inputs", len(df_input)),
                card("Registros de posição", len(df_position)),
            ]
        ),

        dcc.Tabs(
            children=[
                dcc.Tab(
                    label="Visão Geral",
                    children=[
                        html.H2("Visão Geral e Padrões Globais"),
                        dcc.Graph(figure=fig_combat)
                    ]
                ),

                dcc.Tab(
                    label="Ritmo de Jogo",
                    children=[
                        html.H2("Curva de Dificuldade e Ritmo"),
                        dcc.Graph(figure=fig_input)
                    ]
                ),

                dcc.Tab(
                    label="Telemetria",
                    children=[
                        html.H2("Telemetria e Zonas de Calor"),
                        dcc.Graph(figure=fig_position)
                    ]
                ),
            ]
        )
    ]
)


if __name__ == "__main__":
    app.run(debug=True)
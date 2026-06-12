import pandas as pd

URLS = {
    "combat": "https://raw.githubusercontent.com/marialuizapf/UFRJ/refs/heads/main/Analytica/Game%20Analytics/Dashboard/csv/Combat.csv",
    "input": "https://raw.githubusercontent.com/marialuizapf/UFRJ/refs/heads/main/Analytica/Game%20Analytics/Dashboard/csv/Input.csv",
    "position": "https://raw.githubusercontent.com/marialuizapf/UFRJ/refs/heads/main/Analytica/Game%20Analytics/Dashboard/csv/Position.csv",
    "session": "https://raw.githubusercontent.com/marialuizapf/UFRJ/refs/heads/main/Analytica/Game%20Analytics/Dashboard/csv/Session.csv",
}

def load_csv(n):
    df_combat = pd.read_csv(URLS["combat"])
    df_input = pd.read_csv(URLS["input"])
    df_position = pd.read_csv(URLS["position"])
    df_session = pd.read_csv(URLS["session"])

    return df_combat.head(n), df_input.head(n), df_position.head(n), df_session.head(n)

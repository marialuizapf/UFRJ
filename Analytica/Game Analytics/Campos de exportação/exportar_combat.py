import json
import pandas as pd
from pathlib import Path
import re
import numpy as np

PASTA = Path("dados")
ARQ = Path("Combat.csv")

def to_ms(t):
    return int(pd.to_timedelta(t).total_seconds() * 1000)

def sort_size(path: Path):
    return [int(x) if x.isdigit() else x.lower()
            for x in re.split(r'(\d+)', path.stem)]

def str_to_float(value):
    if value is None:
        return np.nan
    s = str(value).strip()
    if s == "":
        return np.nan
    s = s.replace(",", ".")
    s = re.sub(r"[^0-9\.\-+]", "", s)
    try:
        return float(s)
    except ValueError:
        return np.nan

def main():
    reg = []

    # Percorre e lista todos os arquivos JSON na pasta especificada
    # Ordena os arquivos para garantir consistência nos IDs
    # Cria pares de (índice, caminho do arquivo)
    for fp in sorted(PASTA.glob("*.json"), key=sort_size):
        session_id = fp.stem 
        
        with fp.open("r", encoding="utf-8") as file:
            data = json.load(file)

        combats = data.get("Combats", [])
        for idx, combats_data in enumerate(combats):
            action = combats_data.get("Action", "")
            t = combats_data.get("Time", "00:00:00")
            value = combats_data.get("Value", "")

            reg.append({
                "session_id": session_id,     # String
                "idx": idx,                   # Int 
                "time_ms": to_ms(t),          # Int 
                "action": action,             # String 
                "value": str_to_float(value)  # Float
            })
    df = pd.DataFrame(reg)
    mapping = {
        "session_id": "string",
        "idx": "int32",
        "time_ms": "int32",
        "action": "string",
        "value": "float32"
    }
    df = df.astype(mapping)

    df.to_csv(ARQ, index=False)
    print(f"Exportado {len(reg)} registros para {ARQ}")

if __name__ == "__main__":
    main()

##Ajustes:
# Adicionar nova informação quando tiver dados novos em vez de sobrescrever o arquivo todo
# Não poder escrever a informação se for duplicada  



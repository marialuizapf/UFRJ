import json
import pandas as pd
from pathlib import Path
import re
import numpy as np

PASTA = Path("dados_finais")
ARQ = Path("Position.csv")

def to_ms(t):
    return int(pd.to_timedelta(t).total_seconds() * 1000)

def getPosition(position_str):
    """
    Extrai as coordenadas X, Y e Z de uma string de posição como "(xx, yy, zzz)".
    Retorna (x, y, z) como floats, ou (0.0, 0.0, 0.0) se a string vazia.
    """
    if not position_str:
        return np.nan, np.nan, np.nan
    
    cleaned  = re.sub(r'[\(\)\s]', '', position_str)
    
    try:
        # Divide a string pela vírgula e converte cada parte para float
        x_str, y_str, z_str = cleaned.split(',')
        return float(x_str), float(y_str), float(z_str)
    except (ValueError, IndexError):
        # Retorna valores padrão caso a string não esteja no formato esperado
        return np.nan, np.nan, np.nan

def sort_size(path: Path):
    return [int(x) if x.isdigit() else x.lower()
            for x in re.split(r'(\d+)', path.stem)]

def main():
    reg = []

    # Percorre e lista todos os arquivos JSON na pasta especificada
    # Ordena os arquivos para garantir consistência nos IDs
    # Cria pares de (índice, caminho do arquivo)

    for fp in sorted(PASTA.glob("*.json"), key=sort_size):
        session_id = fp.stem 
        
        with fp.open("r", encoding="utf-8") as file:
            data = json.load(file)

        positions = data.get("Positions", [])
        for idx, position_data in enumerate(positions):
            map_id = position_data.get("Map", "")       
            position_str = position_data.get("Position", "")
            t = position_data.get("Time", "00:00:00")

            x, y, z = getPosition(position_str)
            time_ms = to_ms(t)

            reg.append({
                "session_id": session_id,   # String 
                "idx": idx,                 # Int 
                "time_ms": time_ms,         # Int                 
                "map_id": map_id,           # String
                "position_x": x,            # Float
                "position_y": y,            # Float
                "position_z": z             # Float
            })

    df = pd.DataFrame(reg)
    mapping = {
        "session_id": "string",
        "idx": "int32",
        "time_ms": "int32",
        "map_id": "string",
        "position_x": "float32",
        "position_y": "float32",
        "position_z": "float32"
    }
    df = df.astype(mapping)

    #Diminuindo o tamanho do arquivo final, deixando 1 posição por segundo
    df = df.drop_duplicates(subset=["session_id", "time_ms"], keep="last")

    df.to_csv(ARQ, index=False)
    print(f"Exportado {len(df)} registros para {ARQ}")

if __name__ == "__main__":
    main()
 



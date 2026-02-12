import json
import pandas as pd
from pathlib import Path
import re

PASTA = Path("dados")
ARQ = Path("Session.csv")

def to_ms(t):
    return int(pd.to_timedelta(t).total_seconds() * 1000)

def ms_to_str(ms):
    seconds = int(ms / 1000)
    m, s = divmod(seconds, 60)
    h, m = divmod(m, 60)
    return f"{h:02d}:{m:02d}:{s:02d}"

def sort_size(path: Path):
    return [int(x) if x.isdigit() else x.lower()
            for x in re.split(r'(\d+)', path.stem)]

def main():
    reg = []
    time_stamp = 0
    # Percorre e lista todos os arquivos JSON na pasta especificada
    # Ordena os arquivos para garantir consistência nos IDs
    # Cria pares de (índice, caminho do arquivo)
    for fp in sorted(PASTA.glob("*.json"), key=sort_size):
        session_id = fp.stem
        with fp.open("r", encoding="utf-8") as file:
            data = json.load(file)

        name = data.get("Name", "")

        match = re.search(r'(\d+)$', name)
        if match:
            id = int(match.group(1))
            print(id)

        s = data.get("StartTime", "00:00:00")
        e = data.get("EndTime", "00:00:00")

        start_ms = to_ms(s)
        end_ms = to_ms(e)
        duration_ms = max(0, end_ms - start_ms)

        video_start_val = time_stamp
        video_end_val = time_stamp + duration_ms

        duration_str = ms_to_str(duration_ms)
        v_start_str = ms_to_str(video_start_val)
        v_end_str = ms_to_str(video_end_val)    

        player_id = f"P{(id+3):02}"

        reg.append({
            "player_id": player_id,                      # string
            "session_id": session_id,                   # string
            "session_name": name,                       # string
            "duration_ms": duration_ms,                 # int
            "duration_str": duration_str,               # string
            "video_start_str": v_start_str,             # string 
            "video_end_str":v_end_str                   # string 
        })

        time_stamp += duration_ms

    df = pd.DataFrame(reg)

    mapping = {
        "player_id": "string",
        "session_id": "string",
        "session_name": "string",
        "duration_ms": "int32",
        "duration_str": "string",
        "video_start_str": "string",
        "video_end_str": "string"
    }
    df = df.astype(mapping)

    df.to_csv(ARQ, index=False)
    print(f"Exportado {len(reg)} registros para {ARQ}")

if __name__ == "__main__":
    main()




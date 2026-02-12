import json
import pandas as pd
from pathlib import Path
import copy

# --- CONFIGURAÇÕES ---
PASTA_ORIGEM = Path("dados")
PASTA_DESTINO = Path("dados_tratados")

# NOME do arquivo que você quer cortar (sem o .json)
ARQUIVO_ALVO = "Analytics_Data_Attempt_8(1)(1)" 

# TEMPO EM MILISSEGUNDOS onde o corte vai acontecer
MS_DE_CORTE = 729000  # Exemplo: Cortar aos 15 segundos (15000ms)

# Listas que contêm dados baseados em tempo que precisam ser divididos
CHAVES_TEMPORAIS = ["Positions", "Inputs", "Combats"] 

# --- FUNÇÕES AUXILIARES ---

def to_ms(t):
    """Converte string 'HH:MM:SS' para milissegundos (int)."""
    if not t: return 0
    # pd.to_timedelta é robusto para formatos de tempo
    return int(pd.to_timedelta(t).total_seconds() * 1000)

def ms_to_str(ms):
    """Converte milissegundos (int) para string 'HH:MM:SS'."""
    seconds = int(ms / 1000)
    m, s = divmod(seconds, 60)
    h, m = divmod(m, 60)
    # Retorna formatado. Ajuste os milissegundos se o seu JSON original usar casas decimais
    return f"{h:02d}:{m:02d}:{s:02d}"

def processar_corte(arquivo_nome, tempo_corte_ms):
    """
    Divide um arquivo JSON em dois baseados no tempo de corte.
    """
    caminho_arquivo = PASTA_ORIGEM / f"{arquivo_nome}.json"
    
    if not caminho_arquivo.exists():
        print(f"Erro: Arquivo {caminho_arquivo} não encontrado.")
        return

    # 1. Carregar o JSON Original
    with caminho_arquivo.open("r", encoding="utf-8") as f:
        data_original = json.load(f)

    # Verifica se o tempo de corte é válido
    start_time_original = to_ms(data_original.get("StartTime", "00:00:00"))
    end_time_original_ms = to_ms(data_original.get("EndTime", "00:00:00"))

    if tempo_corte_ms >= end_time_original_ms:
        print("Erro: O tempo de corte é maior ou igual à duração total do vídeo.")
        return

    print(f"Processando '{arquivo_nome}'...")
    print(f"Duração Original: {end_time_original_ms}ms | Corte em: {tempo_corte_ms}ms")

    # =================================================================
    # PARTE 1: O INÍCIO (Do 0 até o Corte)
    # =================================================================
    data_parte_1 = copy.deepcopy(data_original)
    
    # Atualiza o fim da Parte 1 para ser o tempo de corte
    data_parte_1["EndTime"] = ms_to_str(tempo_corte_ms)

    # Filtra as listas: Mantém apenas o que aconteceu ANTES ou IGUAL ao corte
    for chave in CHAVES_TEMPORAIS:
        if chave in data_parte_1:
            lista_filtrada = []
            for item in data_parte_1[chave]:
                tempo_item_ms = to_ms(item.get("Time", "00:00:00"))
                if tempo_item_ms <= tempo_corte_ms:
                    lista_filtrada.append(item)
            data_parte_1[chave] = lista_filtrada

    # Salva a Parte 1 (Sobrescreve ou salva na pasta tratados com mesmo nome)
    path_parte_1 = PASTA_DESTINO / f"{arquivo_nome}.json"
    with path_parte_1.open("w", encoding="utf-8") as f:
        json.dump(data_parte_1, f, ensure_ascii=False, indent=4)
    print(f"-> Parte 1 salva em: {path_parte_1.name} (Novo EndTime: {data_parte_1['EndTime']})")

    # =================================================================
    # PARTE 2: O RESTANTE (Do Corte até o Fim)
    # =================================================================
    data_parte_2 = copy.deepcopy(data_original)

    # Novo StartTime é 0 (pois é um novo arquivo começando do ponto de corte)
    data_parte_2["StartTime"] = "00:00:00"
    
    # Novo EndTime = EndTime Antigo - Tempo de Corte
    novo_end_time_ms = end_time_original_ms - tempo_corte_ms
    data_parte_2["EndTime"] = ms_to_str(novo_end_time_ms)
    
    # Ajusta o nome da sessão (Opcional, para identificar)
    data_parte_2["Name"] = data_parte_2.get("Name", "") + " (Parte 2)"

    # Filtra e SHIFTA (Desloca) os tempos
    for chave in CHAVES_TEMPORAIS:
        if chave in data_parte_2:
            lista_processada = []
            for item in data_parte_2[chave]:
                tempo_item_ms = to_ms(item.get("Time", "00:00:00"))
                
                # Só pega o que aconteceu DEPOIS do corte
                if tempo_item_ms > tempo_corte_ms:
                    # Cria um novo item para não alterar a referência original errada
                    novo_item = item.copy()
                    
                    # CÁLCULO IMPORTANTE: Subtrai o tempo de corte para o tempo começar do 0
                    novo_tempo_ms = tempo_item_ms - tempo_corte_ms
                    novo_item["Time"] = ms_to_str(novo_tempo_ms)
                    
                    lista_processada.append(novo_item)
            
            data_parte_2[chave] = lista_processada

    # Salva a Parte 2 com sufixo (1)
    path_parte_2 = PASTA_DESTINO / f"{arquivo_nome}(1).json"
    with path_parte_2.open("w", encoding="utf-8") as f:
        json.dump(data_parte_2, f, ensure_ascii=False, indent=4)
    print(f"-> Parte 2 salva em: {path_parte_2.name} (Duração: {data_parte_2['EndTime']})")

def main():
    # Cria a pasta de destino se não existir
    PASTA_DESTINO.mkdir(parents=True, exist_ok=True)
    
    # Chama a função de processamento
    processar_corte(ARQUIVO_ALVO, MS_DE_CORTE)

if __name__ == "__main__":
    main()
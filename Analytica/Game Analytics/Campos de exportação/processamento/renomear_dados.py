import json
import re
from pathlib import Path

# --- CONFIGURAÇÕES ---
PASTA_ORIGEM  = Path("dados_origem")
PASTA_DESTINO = Path("dados_destino")         

# OFFSET: Quanto queremos somar ao número original?
# 0 virar 18 significa somar 18.
VALOR_SOMA = 18 

def main():
    # Garante que a pasta de destino existe
    PASTA_DESTINO.mkdir(parents=True, exist_ok=True)

    # Lista apenas arquivos que seguem o padrão "Analytics_Data_Attempt_X.json"
    arquivos = sorted(PASTA_ORIGEM.glob("Analytics_Data_Attempt_*.json"))
    
    print(f"Encontrados {len(arquivos)} arquivos em '{PASTA_ORIGEM}'. Iniciando processamento...\n")

    count = 0
    for fp in arquivos:
        # 1. Identificar o número (ID) no nome do arquivo usando Regex
        # O padrão procura por dígitos (\d+) no final do nome
        match = re.search(r"Analytics_Data_Attempt_(\d+)", fp.stem)

        if match:
            current_id = int(match.group(1))

            # 2. Verificar se está no intervalo alvo 
            if 0 <= current_id <= 80:
                
                # 3. Calcular o novo ID
                new_id = current_id + VALOR_SOMA
                
                # Cria os novos nomes
                new_base_name = f"Analytics_Data_Attempt_{new_id}"
                new_filename = f"{new_base_name}.json"

                # 4. Ler o conteúdo original
                with fp.open("r", encoding="utf-8") as f_in:
                    data = json.load(f_in)

                # Guarda o nome antigo para log
                old_name_internal = data.get("Name", "SemNome")

                # 5. ATUALIZAR O CONTEÚDO JSON
                # Atualiza o campo "Name" para bater com o novo nome do arquivo
                data["Name"] = new_base_name

                # Os arrays Inputs, Positions e Combats são preservados automaticamente
                # ao salvarmos o objeto 'data' inteiro novamente.

                # 6. Salvar na pasta de destino (dados)
                path_destino = PASTA_DESTINO / new_filename
                
                with path_destino.open("w", encoding="utf-8") as f_out:
                    json.dump(data, f_out, ensure_ascii=False, indent=4)

                print(f"Processado: {fp.name} ({old_name_internal}) \n       -->  {new_filename} (Nome interno: {new_base_name})")
                count += 1
            else:
                print(f"Ignorado (Fora do intervalo 0-17): {fp.name}")
        else:
            print(f"Ignorado (Padrão de nome incorreto): {fp.name}")

    print(f"\nSucesso! {count} arquivos foram renomeados e movidos para '{PASTA_DESTINO}'.")

if __name__ == "__main__":
    main()
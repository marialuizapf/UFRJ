
## Estrutura dos Arquivos

Os dados estão divididos em quatro arquivos principais. A chave primária para conectar todas as tabelas é o `session_id`.

### 1. `Session.csv` 
Atua como o índice principal. Cada linha representa uma sessão única de jogo.

| Coluna | Tipo | Descrição |
| :--- | :--- | :--- |
| **`player_id`** | String | Identificador do jogador  |
| **`session_id`** | String | **PK**. Identifica a sessão específica. Use este ID para buscar dados nos outros arquivos. |
| **`session_name`** | String | Nome original do arquivo  |
| **`duration_ms`** | Int | Duração total da sessão em milissegundos. |
| **`duration_str`** | String | Duração formatada (`HH:MM:SS`). |
| **`video_start_str`** | String | **Timeline Acumulada**: Momento exato onde esta sessão começa no arquivo de vídeo consolidado. |
| **`video_end_str`** | String | **Timeline Acumulada**: Momento exato onde esta sessão termina no arquivo de vídeo consolidado. |


### 2. `Position.csv` 

| Coluna | Tipo | Descrição |
| :--- | :--- | :--- |
| **`session_id`** |String| **FK**. Conecta com `Session.csv`. |
| **`idx`** |Int| Índice sequencial do registro dentro daquela sessão  |
| **`time_ms`** |Int| Tempo decorrido desde o início desta sessão específica. |
| **`map_id`** | String | Nome do mapa |
| **`position_x`** |Float |Coordenada X  |
| **`position_y`** |Float| Coordenada Y  |
| **`position_z`** |Float| Coordenada Z |

### 3. `Input.csv` 

| Coluna | Tipo | Descrição |
| :--- | :--- | :--- |
| **`session_id`**|String| **FK**. Conecta com `Session.csv` |
| **`idx`** | Int|Índice sequencial do evento |
| **`time_ms`** |Int| Momento exato da ação |
| **`input`** |String| Nome do comando acionado |
| **`value`** |Float| Valor associado ao input  |

### 4. `Combat.csv` (Eventos de Combate)
Registra interações de combate ou eventos importantes de gameplay.

| Coluna | Tipo | Descrição |
| :--- | :--- | :--- |
| **`session_id`** |String| **FK**. Conecta com `Session.csv`. |
| **`idx`** | Int|Índice sequencial do evento. |
| **`time_ms`** | Int|Momento exato da ação |
| **`action`** |String| Tipo de ação  |
| **`value`** |Float| Valor numérico associado  |

---

## !! Notas !!


### Grupo Vídeo 1 (Sessões 0 a 17)
* **Jogadores vs. Sessões:** O vídeo registra 8 jogadores distintos, mas existem 11 sessões registradas, então pode ter 6 jogadores ou tentaivas não registradas no vídeo.

### Sessões de Continuação 
Algumas sessões representam continuações diretas onde um jogador assume o jogo de outro.

**Importante:** Nestes arquivos, o `time_ms` foi resetado (começa do 0), pois representa o tempo da *nova gravação*, e não o tempo acumulado de jogo total.

1.  **Sessões 5 e 6:**
    * Dois jogadores envolvidos.
    * A **Sessão 6** é a continuação direta do progresso da **Sessão 5**.
2.  **Sessões 8 a 11:**
    * Quatro jogadores envolvidos.
    * Sequência de revezamento: **8 → 9 → 10 → 11**. Cada um continuou o jogo do anterior.

### Grupo Vídeo 2 (Sessões 18 a 36)
* Como não teve vídeo assistido, não há conhecimento de sessões repetidas, conjuntas ou continuações. Então Assume-se que cada arquivo é uma execução independente padrão.

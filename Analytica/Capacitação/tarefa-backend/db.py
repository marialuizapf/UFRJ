import sqlite3
from modelos import SATRecord

DB_PATH = 'Database.db'

def init_db():
    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    cur.execute('''
        CREATE TABLE IF NOT EXISTS SAT (
            DBN TEXT PRIMARY KEY,
            Nome_Escola TEXT,
            Numero_Candidatos INTEGER,
            Media_Leitura INTEGER,
            Media_Matematica INTEGER,
            Media_Escrita INTEGER
        )
    ''')
    conn.commit()
    conn.close()

def list_all():
    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    cur.execute("SELECT * FROM SAT ORDER BY DBN")
    rows = cur.fetchall()
    conn.close()
    return [SATRecord(*row) for row in rows]

def get_by_dbn(dbn):
    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    cur.execute("SELECT * FROM SAT WHERE DBN=?", (dbn,))
    row = cur.fetchone()
    conn.close()
    return SATRecord(*row) if row else None

def create(record: SATRecord):
    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    cur.execute(
        "INSERT INTO SAT VALUES (?, ?, ?, ?, ?, ?)",
        (
            record.DBN,
            record.Nome_Escola,
            record.Numero_Candidatos,
            record.Media_Leitura,
            record.Media_Matematica,
            record.Media_Escrita
        )
    )
    conn.commit()
    conn.close()

def update(record: SATRecord):
    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    cur.execute(
        """
        UPDATE SAT SET
          Nome_Escola=?, Numero_Candidatos=?, 
          Media_Leitura=?, Media_Matematica=?, Media_Escrita=?
        WHERE DBN=?
        """,
        (
            record.Nome_Escola,
            record.Numero_Candidatos,
            record.Media_Leitura,
            record.Media_Matematica,
            record.Media_Escrita,
            record.DBN
        )
    )
    conn.commit()
    conn.close()

def delete(dbn):
    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()
    cur.execute("DELETE FROM SAT WHERE DBN=?", (dbn,))
    conn.commit()
    conn.close()

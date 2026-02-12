class SATRecord:
    def __init__(self, DBN, Nome_Escola, Numero_Candidatos, Media_Leitura, Media_Matematica, Media_Escrita):
        self.DBN = DBN
        self.Nome_Escola = Nome_Escola
        self.Numero_Candidatos = Numero_Candidatos
        self.Media_Leitura = Media_Leitura
        self.Media_Matematica = Media_Matematica
        self.Media_Escrita = Media_Escrita

    def __repr__(self):
        return f'<DBN {self.DBN}>'

    def serialize(self):
        return {
            'DBN': self.DBN,
            'Nome_Escola': self.Nome_Escola,
            'Numero_Candidatos': self.Numero_Candidatos,
            'Media_Leitura': self.Media_Leitura,
            'Media_Matematica': self.Media_Matematica,
            'Media_Escrita': self.Media_Escrita
        }

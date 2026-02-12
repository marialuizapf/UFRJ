-- Unidades
INSERT INTO Unidade (nome_unidade) VALUES
('Instituto de Matemática'),
('Faculdade de Letras'),
('Instituto de Física');

-- Cursos
INSERT INTO Curso (nome_curso, id_unidade) VALUES
('Engenharia', 1),
('Letras', 2),
('Física', 3);

-- Pessoas 
INSERT INTO Pessoa (CPF, nome, email, data_nascimento) VALUES
('11111111111', 'Ana Souza', 'ana@ufrj.br', '2000-05-01'),
('22222222222', 'Bruno Lima', 'bruno@ufrj.br', '1999-04-02'),
('33333333333', 'Carlos Dias', 'carlos@ufrj.br', '2001-03-03'),
('44444444444', 'Diana Alves', 'diana@ufrj.br', '2002-02-04'),
('55555555555', 'Eduardo Nunes', 'eduardo@ufrj.br', '2000-01-05'),
('66666666666', 'Prof. Fátima', 'fatima@ufrj.br', '1975-01-01'),
('77777777777', 'Prof. Gustavo', 'gustavo@ufrj.br', '1980-02-02'),
('88888888888', 'Prof. Helena', 'helena@ufrj.br', '1978-03-03'),
('99999999999', 'Prof. Igor', 'igor@ufrj.br', '1982-04-04');

-- Professores
INSERT INTO Professor (registro_funcional, titulacao_academica, CPF) VALUES
('P001', 'Doutorado', '66666666666'),
('P002', 'Mestrado', '77777777777'),
('P003', 'Doutorado', '88888888888'),
('P004', 'Mestrado', '99999999999');

-- Alunos
INSERT INTO Aluno (DRE, CPF, id_curso) VALUES
('202300001', '11111111111', 1),
('202300002', '22222222222', 2),
('202300003', '33333333333', 3),
('202300004', '44444444444', 1),
('202300005', '55555555555', 2);

-- Disciplinas
INSERT INTO Disciplina (nome_disciplina) VALUES
('Cálculo I'),
('Português I'),
('Física I'),
('Álgebra Linear'),
('Literatura Brasileira');

-- Turmas
INSERT INTO Turma (registro_funcional, id_disciplina, ano, semestre, horario, sala) VALUES
('P001', 1, 2024, 1, '08:00:00', '101A'), 
('P002', 2, 2024, 1, '10:00:00', '102B'), 
('P003', 3, 2024, 1, '14:00:00', '103C'), 
('P004', 4, 2024, 1, '16:00:00', '104D'), 
('P001', 5, 2024, 2, '08:00:00', '105E'), 
('P002', 1, 2024, 2, '10:00:00', '106F'); 

-- CRID 
INSERT INTO CRID (semestre, DRE) VALUES
(1, '202300001'),
(1, '202300002'),
(1, '202300003'),
(1, '202300004'),
(1, '202300005'),
(2, '202300001'),
(2, '202300002'),
(2, '202300003'),
(2, '202300004'),
(2, '202300005');

-- Historico 
INSERT INTO Historico (DRE, semestre, id_turma, nota_final, frequencia, resultado) VALUES
('202300001', 1, 1, 8.5, 95, 'Aprovado'),
('202300001', 1, 2, 4.0, 80, 'Reprovado'),

('202300002', 1, 2, 9.0, 100, 'Aprovado'),
('202300002', 1, 3, 5.5, 60, 'Reprovado'),

('202300003', 1, 3, 6.0, 75, 'Aprovado'),
('202300003', 1, 4, 3.0, 40, 'Reprovado'),

('202300004', 1, 1, 9.0, 100, 'Aprovado'),
('202300004', 1, 4, 2.0, 50, 'Reprovado'),

('202300005', 1, 5, 7.0, 85, 'Aprovado'),
('202300005', 1, 6, 6.0, 70, 'Aprovado'),

('202300001', 2, 5, 7.5, 90, 'Aprovado'),
('202300001', 2, 6, 6.5, 88, 'Aprovado'),

('202300002', 2, 5, 5.0, 70, 'Reprovado'),
('202300002', 2, 6, 6.0, 65, 'Aprovado'),

('202300003', 2, 5, 8.0, 92, 'Aprovado'),
('202300003', 2, 6, 4.0, 60, 'Reprovado'),

('202300004', 2, 5, 9.0, 100, 'Aprovado'),
('202300004', 2, 6, 7.0, 80, 'Aprovado'),

('202300005', 2, 5, 8.0, 95, 'Aprovado'),
('202300005', 2, 6, 7.0, 90, 'Aprovado');


-- Consulta 1: Nome do aluno e o nome do curso
SELECT Pessoa.nome AS nome_aluno, Curso.nome_curso
FROM Pessoa
INNER JOIN Aluno ON Pessoa.CPF = Aluno.CPF
INNER JOIN Curso ON Aluno.id_curso = Curso.id_curso;

-- Consulta 2: Turmas do 2º semestre de 2024
SELECT id_turma, horario, sala 
FROM Turma
WHERE semestre = 2 AND ano = 2024;

-- Consulta 3: Professores e número de turmas
SELECT Pessoa.nome AS nome_professor, COUNT(*) AS quantidade_turmas
FROM Turma
INNER JOIN Professor ON Turma.registro_funcional = Professor.registro_funcional
INNER JOIN Pessoa ON Professor.CPF = Pessoa.CPF
GROUP BY Pessoa.nome;

-- Consulta 4: Alunos reprovados
SELECT DISTINCT Pessoa.nome AS nome_aluno
FROM Historico
INNER JOIN Aluno ON Historico.DRE = Aluno.DRE
INNER JOIN Pessoa ON Aluno.CPF = Pessoa.CPF
WHERE Historico.resultado = 'Reprovado';

-- Consulta 5: Matrículas do 1º semestre de 2023
SELECT 
    aluno_p.nome AS nome_aluno,
    Disciplina.nome_disciplina,
    prof_p.nome AS nome_professor,
    Historico.nota_final
FROM Historico
INNER JOIN Aluno ON Historico.DRE = Aluno.DRE
INNER JOIN Pessoa AS aluno_p ON Aluno.CPF = aluno_p.CPF
INNER JOIN Turma ON Historico.id_turma = Turma.id_turma
INNER JOIN Disciplina ON Turma.id_disciplina = Disciplina.id_disciplina
INNER JOIN Professor ON Turma.registro_funcional = Professor.registro_funcional
INNER JOIN Pessoa AS prof_p ON Professor.CPF = prof_p.CPF
WHERE Turma.ano = 2023 AND Turma.semestre = 1;

-- Desafio: Consulta Avançada
SELECT 
    Pessoa.nome AS nome_aluno,
    Aluno.DRE,
    COUNT(Historico.id_turma) AS total_disciplinas
FROM Historico
INNER JOIN Aluno ON Historico.DRE = Aluno.DRE
INNER JOIN Pessoa ON Aluno.CPF = Pessoa.CPF
WHERE Aluno.DRE NOT IN (
    SELECT DRE
    FROM Historico
    WHERE resultado = 'Reprovado'
)
GROUP BY Pessoa.nome, Aluno.DRE;

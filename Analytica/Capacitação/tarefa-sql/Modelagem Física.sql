-- Pessoa
CREATE TABLE Pessoa (
    CPF CHAR(11) NOT NULL PRIMARY KEY,
    nome VARCHAR(50) NOT NULL,
    email VARCHAR(50) NOT NULL UNIQUE,
    data_nascimento DATE NOT NULL
);

-- Unidade
CREATE TABLE Unidade (
    id_unidade INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    nome_unidade VARCHAR(50) NOT NULL UNIQUE
);

-- Curso
CREATE TABLE Curso (
    id_curso INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    nome_curso VARCHAR(50) NOT NULL UNIQUE,
    id_unidade INT NOT NULL,
    FOREIGN KEY (id_unidade) REFERENCES Unidade(id_unidade)
);

-- Aluno
CREATE TABLE Aluno (
    DRE CHAR(9) NOT NULL PRIMARY KEY,
    CPF CHAR(11) NOT NULL,
    id_curso INT NOT NULL,
    FOREIGN KEY (CPF) REFERENCES Pessoa(CPF),
    FOREIGN KEY (id_curso) REFERENCES Curso(id_curso)
);

-- Professor
CREATE TABLE Professor (
    registro_funcional VARCHAR(20) NOT NULL PRIMARY KEY,
    titulacao_academica VARCHAR(50) NOT NULL,
    CPF CHAR(11) NOT NULL,
    FOREIGN KEY (CPF) REFERENCES Pessoa(CPF)
);

-- Disciplina
CREATE TABLE Disciplina (
    id_disciplina INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    nome_disciplina VARCHAR(50) NOT NULL UNIQUE
);

-- Turma
CREATE TABLE Turma (
    id_turma INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    ano INT NOT NULL,
    semestre INT NOT NULL CHECK (semestre BETWEEN 1 AND 2),
    horario TIME NOT NULL,
    sala VARCHAR(10) NOT NULL,
    registro_funcional VARCHAR(20) NOT NULL,
    id_disciplina INT NOT NULL,
    FOREIGN KEY (registro_funcional) REFERENCES Professor(registro_funcional),
    FOREIGN KEY (id_disciplina) REFERENCES Disciplina(id_disciplina)
);

-- CRID 
CREATE TABLE CRID (
    semestre INT NOT NULL CHECK (semestre BETWEEN 1 AND 2),
    DRE CHAR(9) NOT NULL,
    PRIMARY KEY (semestre, DRE),
    FOREIGN KEY (DRE) REFERENCES Aluno(DRE)
);

-- Historico 
CREATE TABLE Historico (
    DRE CHAR(9) NOT NULL,
    semestre INT NOT NULL CHECK (semestre BETWEEN 1 AND 2),
    id_turma INT NOT NULL,
    nota_final DECIMAL(5,2) NOT NULL CHECK (nota_final BETWEEN 0 AND 10),
    frequencia DECIMAL(5,2) NOT NULL CHECK (frequencia BETWEEN 0 AND 100),
    resultado VARCHAR(20) NOT NULL CHECK (resultado IN ('Aprovado', 'Reprovado', 'Trancado')),
    PRIMARY KEY (DRE, semestre, id_turma),
    FOREIGN KEY (DRE, semestre) REFERENCES CRID(DRE, semestre),
    FOREIGN KEY (id_turma) REFERENCES Turma(id_turma)
);

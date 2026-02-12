### Trabalho 4: Compress ao de dados

- Em um certo concurso, os candidatos devem responder a 50 questões
objetivas, com alternativas A, B, C e D.

- As respostas dos candidatos estão salvas em um arquivo texto. Cada
linha come ̧ca com o CPF do candidato seguido pelas respostas das
questões.
    - Exemplo: 123.345.678-23 A B C D ...

- Faça um programa que lê esse arquivo (modo texto) e gera um arquivo
comprimido (modo binário) com taxa de compressão de pelo menos
50%.

- Faça um programa para descomprimir um arquivo compactado pelo
item acima.

    private static void lerArquivoTexto(String path, ArrayList<String> pessoas) throws IOException {
        try(BufferedReader br = new BufferedReader(new FileReader(path))){
            String linha;
            while((linha = br.readLine()) != null){
                pessoas.add(linha);
                System.out.println("Pessoa adicionada: " + linha);
            }
        }
    }
    private static void escrevertexto(String path, ArrayList<Sala> salas) throws IOException {
        try(BufferedWriter bw = new BufferedWriter(new FileWriter(path))){
            for(Sala s: salas){
                bw.write(s.toString() + "\n" + "Atualizada");
                bw.newLine();
                System.out.println("Arquivo escrito com sucesso!");  
            }          
        }catch(IOException e){
            System.out.println(e.getMessage());
        }
   }
   
   private static void escrevertexto2(String path) throws IOException {
        Scanner scn = new Scanner(System.in);
        int n;
        n = scn.nextInt();
        try(BufferedWriter bw = new BufferedWriter(new FileWriter(path))){
            for(int i = 1; i <= 10; i++){
                bw.write(String.format("(%2d x %d = %2d)\n", i, n, i*n)); 
                bw.newLine();
            }
        }catch(IOException e){
            System.out.println(e.getMessage());
        }
   }

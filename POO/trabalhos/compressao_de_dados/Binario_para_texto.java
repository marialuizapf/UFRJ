package trabalhos.compressao_de_dados;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.util.Scanner;

// programa que le um arquivo texto do formato: XXX.XXX.XXX-XX A B C... (até 50 letras maiusculas)
// e gera um arquivo comprimido binario com 50% de compressão
// depois outro programa para descommprimir o arquivo binario gerado
public class Binario_para_texto {
    public static void main (String[] argv){
        
        AString[] s;
        String path = "C:/Users/maria/OneDrive/Documents/GitHub/UFRJ/POO/trabalhos/compressao_de_dados/arquivo.txt";
        try{
            escreverBinario(path);
            lerTexto(path, s);
        }catch(IOException e){
            System.out.println(e.getMessage());
        }

    }

    public static void escreverBinario(String path) throws IOException {
        Scanner sc = new Scanner(System.in);
        String s = sc.nextLine();
        byte[] c = s.getBytes();

        FileOutputStream arq = new FileOutputStream(path);
        arq.write(c);

        arq.close();
        sc.close();
    }

    public static void lerTexto(String path, String[] s) throws IOException {
        try(BufferedReader br = new BufferedReader(new FileReader(path))){
            String linha;
            while((linha = br.readLine()) != null){
                for(String str: s){
                    s = linha;
                }
            }
        }
    }
}


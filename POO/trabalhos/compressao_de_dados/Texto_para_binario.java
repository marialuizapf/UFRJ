package trabalhos.compressao_de_dados;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.io.FileInputStream;

// programa que le um arquivo texto do formato: XXX.XXX.XXX-XX A B C... (até 50 letras maiusculas)
// e gera um arquivo comprimido binario com 50% de compressão
// depois outro programa para descommprimir o arquivo binario gerado
public class Texto_para_binario {
    public static void main (String[] argv){
        
        String path = "C:/Users/maria/OneDrive/Documents/GitHub/UFRJ/POO/trabalhos/compressao_de_dados/arquivo.txt";
        

    }

    public static void escreverTexto(String path, ArrayList<String> lista){
        try(BufferedWriter bw = new BufferedWriter(new FileWriter(path))){
            for(String s: lista){
                bw.write(s);
                bw.newLine();
            }
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    public static void lerTexto(String path){
        try(BufferedReader br = new BufferedReader(new FileReader(path))){
            

        }
    }

    public static void lerBinario(String path) throws IOException {
        FileInputStream arq = new FileInputStream(path);
        byte[] c = new byte[15];
        arq.read(c);
        String s = new String(c, "UTF-8");
        arq.close();
    }
}

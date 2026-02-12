package trabalhos.compressao_de_dados;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.File;

public class Binario {
    public static void main(String[] args) {

        String path = "C:/Users/maria/OneDrive/Documents/GitHub/UFRJ/POO/trabalhos/compressao_de_dados/arquivo.bin";
        try{
            escreverBinario(path);
        }catch(IOException e){
            System.out.println(e.getMessage());
        }
    }


    public static void escreverBinario(String path) throws IOException {
        FileOutputStream arq = new FileOutputStream(path);
        byte[] c = new byte[15];
        String s = "oi tubedm com vc";
        c = s.getBytes();
        arq.write(c);
        arq.close();
    }

    private static void lerBinario() throws IOException {
        FileInputStream arq = new FileInputStream("saida.bin");
        byte[] conteudo = new byte[15];
        arq.read(conteudo);

        String s = new String(conteudo, "UTF-8");
        arq.close();
        System.out.print(s);
    }

}

import java.util.Scanner;

public class Principal {

    static int simularArmarios(int n) {

        boolean[] armarios = new boolean[n+1];  // não usaremos a posição 0 para nada

        for (int crianca = 1; crianca <= n; crianca++) {
            for (int armario = 1; armario <= n; armario++) {
                if (armario % crianca == 0) {
                    armarios[armario] = !armarios[armario];  // flip
                }
            }
        }

        int contAbertos = 0;
        int i = 1;
        while (i <= n) {
            if (armarios[i]) {  // == true
                contAbertos++;
            }
            i++;
        }

        return contAbertos;
    }

    static int contarArmariosAbertos(int n) {
        return (int) Math.sqrt(n);
    }


    public static void main(String[] args) {  // psvm <TAB>
        System.out.println("Oi!");  // sout <TAB>

        for (int i = 0; i < args.length; i++) {
            System.out.println(args[i]);
        }

        int nArmarios;
        if (args.length > 0) {
            // vou ler da linha de comando
            nArmarios = Integer.parseInt(args[0]);

        } else {
            // vou pedir pro usuário digitar
            Scanner scanner = new Scanner(System.in);
            System.out.println("Quantos armários ?");
            nArmarios = scanner.nextInt();
        }



        System.out.println("Abertos ==> " + simularArmarios(nArmarios));
        System.out.println("Abertos ==> " + contarArmariosAbertos(nArmarios));

        int x = 7;
        int y = 20;

        if (x > y || y > 18.3f && x < 8) {
            System.out.println("ok");
        }

        System.out.println("valor é " + (x > 5 ? "alto" : "baixo"));

        float numero = 70.3f;
        System.out.printf("Meu número é %.2f, ok?", numero);





    }
}

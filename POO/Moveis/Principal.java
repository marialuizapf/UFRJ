public class Principal {
    public static void main(String[] args){
        Cadeira c1 = new Cadeira("Madeira", 150, 4);
        Cadeira c2 = new Cadeira("Plástico", 0, 3);
        Armario a1 = new Armario("Metal", 300, 2);
        Mesa m1 = new Mesa("Vidro", 250, 2.0f);

        System.out.println("Dados da Cadeira:");
        c1.imprimirDados();
        c2.imprimirDados();

        System.out.println("\nDados do Armário:");
        a1.imprimirDados();

        System.out.println("\nDados da Mesa:");
        m1.imprimirDados();

        a1.setCusto(120);

        System.out.println("\nDados do Armário após alteração do custo:");
        a1.imprimirDados();
    }
}

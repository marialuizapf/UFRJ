public abstract class Carro {
    protected int volume;
    protected int tamTanque;

    public Carro(int volume, int tamTanque){
        this.volume = volume;
        this.tamTanque = tamTanque;
    }

    public void alterarTanque(int novoTam){
        if (novoTam < this.volume/2){
            System.out.println("Tamanho do tanque alterado com sucesso.");
            this.tamTanque = novoTam;
        } else{
            System.out.println("Erro: novo tamanho do tanque muito pequeno para o volume do carro.");
            return;
        }
    }
}

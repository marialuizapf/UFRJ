public class Passeio extends Carro {
    private String modelo;

    public Passeio(int volume, int tamTanque, String modelo) {
        super(volume, tamTanque);
        this.modelo = modelo;
    }
}

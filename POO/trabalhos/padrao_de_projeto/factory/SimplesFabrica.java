package trabalhos.padrao_de_projeto.factory;

public class SimplesFabrica {
    public static Produto criar(TipodeVeiculo tipo){
        switch(tipo){
            case CARRO:
                return new Carro();
            case MOTO:
                return new Moto();
            default:
                throw new RuntimeException("Tipo de veículo não suportado: " + tipo);
        }
    }
}

public class Chassi{
    public String getCodigoChassi() {
		int num = (int)(Math.random() * 100000);
		String numeroFormatado = String.format("ABC%05d", num);
        return numeroFormatado;
    }
}

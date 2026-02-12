package trabalhos.Drones;
class Singleton {
    private static Singleton instacia = new Singleton();
    private Singleton(){}
    public static Singleton getInstancia(){
        return instacia;
    }
}

punlic main(){
    Singleton a = Singleton.getInstancia()
}
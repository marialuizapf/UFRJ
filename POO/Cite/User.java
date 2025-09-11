package POO.Cite;

public class User {
    private int id;
    private String _name;
    String membership;

    public User(int id, String name, String membership){
        this.id = id;
        this._name = name;
        this.membership = membership;
    }

    void set_id(int id){
        this.id = id;
    }

    void set_name(String name){
        _name = name;
        // this._name = name;
    }

    String get_name(){
        return _name;
    }
}

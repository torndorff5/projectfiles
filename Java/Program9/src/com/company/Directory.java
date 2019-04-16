package com.company;
import java.util.ArrayList;

public class Directory extends Component{
    private ArrayList<Component> components;
    public Directory(String s){
        components = new ArrayList<>();
        name = s;
        value = 0;
    }

    @Override
    public void add(Component c) {
        components.add(c);
    }

    @Override
    public void remove(Component c) {
        components.remove(c);
    }

    @Override
    public void list() {
        for(Component c: components){
            System.out.print(c.getName() + " ");
        }
        System.out.print("\n");
    }

    @Override
    public void listall(int i) {
        System.out.println(name);
        for(Component c:components){
            for (int j = 0; j < i; j++) {
                System.out.print("\t");
            }
            c.listall(i+1);
        }
    }

    @Override
    public void chdir(String s) {
        for(Component c: components){
            if(s.equals(c.name)){
                c.chdir(s);
            }
        }
    }

    @Override
    public void up() {

    }

    @Override
    public int count() {
        int count = 0;
        for(Component c: components){
            count += c.value;
        }
        return count;
    }

    @Override
    public int countall() {
        int count = 0;
        for (Component c: components) {
            count += c.countall();
        }
        return count;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    void print() {
        System.out.println(name);
    }
}

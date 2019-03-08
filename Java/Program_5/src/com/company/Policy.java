package com.company;

import java.util.ArrayList;

public class Policy {
    public ArrayList<policyHolder> phs;
    private static int policycount = 1000;
    private static Policy uniqueinstance;
    private Policy(){
        phs = new ArrayList<>();
    }
    public static Policy getInstance(){
        if(uniqueinstance == null)
            uniqueinstance = new Policy();
        return uniqueinstance;
    }
    public void addPolicyHolder(String name){
        if(uniqueinstance != null) {
            phs.add(new policyHolder(name,policycount++));
        }
    }
    public void print(){
        if(uniqueinstance != null){
            for (var ph: phs) {
                System.out.println("Policy Holder: " + ph.name +"\nPolicy #: " + ph.id + "\n");
            }
        }
    }
    public policyHolder fetchPolicyHolder(int id){
        for(var ph:phs){
            if(ph.id == id)
                return ph;
        }
        return null;
    }

}


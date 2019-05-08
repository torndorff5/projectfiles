package com.spokaneautomationcompany.dev;

public class Customer {
    String id;
    String DisplayName;
    String Title;
    String GivenName;
    String MiddleName;
    String Suffix;
    String FamilyName;
    String PrimaryEmailAddr;
    String Mobile;
    String AlternatePhone;
    PhysicalAddress ShipAddr;
    Customer(String firstname, String lastname, String email, PhysicalAddress addr){
        this.GivenName = firstname;
        this.FamilyName = lastname;
        this.PrimaryEmailAddr = email;
        this.ShipAddr = addr;
    }
}


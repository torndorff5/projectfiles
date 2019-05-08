package com.spokaneautomationcompany.dev;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.event.SmartApplicationListener;

@SpringBootApplication
public class DevApplication {

    public static void main(String[] args) {
        Backend be = new Backend();
        SmallBusiness spokaneFence = new SmallBusiness(be);
        PhysicalAddress pa = new PhysicalAddress();
        pa.Address = "411 S 2060 W";
        pa.City = "Vineyard";
        pa.Country = "USA";
        pa.CountrySubDivisionCode = "UT";
        pa.PostalCode = "84059";
        Customer c = new Customer("Tanner","Orndorff","torndorff5@gmail.com",pa);
        spokaneFence.be.createCustomer(c);
    }

}

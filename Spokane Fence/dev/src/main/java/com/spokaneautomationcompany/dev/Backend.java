package com.spokaneautomationcompany.dev;


import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

public class Backend {
    /**
     * Constructor for Backend class
     */
    Backend(){}

    /**
     * Creates a customer in Quickbooks Online
     *      creates Customer from object passed in. throws exception if required data isn't given
     */
    @RequestMapping(method = RequestMethod.POST, value="/v3/company/<realmID>/customer")
    @ResponseBody
    void createCustomer(@RequestBody Customer c){

    }

    /**
     * Deletes a customer in Quickbooks Online
     */
    void deleteCustomer(){}

    /**
     * Creates an Estimate in Quickbooks Online attached to a specific customer
     */
    void createEstimate(){}

    /**
     * Deletes an Estimate in Quickbooks online attached to a specific customer
     */
    void deleteEstimate(){}

    /**
     * Sends an estimate to the email address of the customer attached to it
     */
    void sendEstimate(){}


}
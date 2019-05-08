//
//  Backend.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/7/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import Foundation

class Customer {
    var firstname, middlename, lastname, suffix, email, phone, altphone, address, city, state, zip: String!
    init(f:String,m:String, l:String, s:String, e:String, p:String, ap:String, a:String, c:String, sta:String, z:String ){
        firstname = f
        middlename = m
        lastname = l
        suffix = s
        email = e
        phone = p
        altphone = ap
        address = a
        city = c
        state = sta
        zip = z
    }
}

class Backend {
    static func fetchCustomer(){
        let urlString = "https://www.google.com/"
        if let url = URL.init(string: urlString) {
            let task = URLSession.shared.dataTask(with: url, completionHandler: {(data,response,error) in
                print(String.init(data: data!, encoding: .ascii) ?? "no data")
            })
            task.resume();
        }
    }
    static func createCustomer(){
    }
    static func deleteCustomer(){
    }
    static func fetchEstimate(){
    }
    static func createEstimate(){
    }
    static func deleteEstimate(){
    }
    static func sendEstimate(){
    }
   
}

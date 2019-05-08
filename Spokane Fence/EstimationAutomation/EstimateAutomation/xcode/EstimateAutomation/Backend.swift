//
//  Backend.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/7/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import Foundation

class Customer {
    var firstname: String!
    var middlename: String!
    var lastname: String!
    var suffix: String!
    var email: String!
    var phone: String!
    var altphone: String!
    var address: String!
    var city: String!
    var state: String!
    var zip: String!
    static func createCustomer(f:String,m:String, l:String, s:String, e:String, p:String, ap:String, a:String, c:String, sta:String, z:String ){
        
    }
    static func fetchCustomer(){
        let urlString = "https://www.google.com"
        if let url = URL.init(string: urlString) {
            let task = URLSession.shared.dataTask(with: url, completionHandler: {(data,response,error) in
                print(String.init(data: data!, encoding: .ascii) ?? "no data")
            })
            task.resume();
        }
    }
}

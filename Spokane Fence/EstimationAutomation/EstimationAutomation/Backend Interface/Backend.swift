//
//  Backend.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/7/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import Foundation

class Addr{
    var line1, city, countrysubdiv, postal:String
    init(l:String, c:String, csd:String,p:String){
        line1 = l;
        city = c;
        countrysubdiv = csd;
        postal = p;
    }
    init(dict: [String:Any]){
        line1 = dict["Line1"] as? String ?? ""
        city = dict["City"] as? String ?? ""
        countrysubdiv = dict["CountrySubDivisionCode"] as? String ?? ""
        postal = dict["PostalCode"] as? String ?? ""
    }
}
class Customer {
    
    var firstname, middlename, lastname, suffix, email, phone, altphone: String
    var address: Addr!
    init(f:String,m:String, l:String, s:String, e:String, p:String, ap:String, addr:Addr){
        firstname = f
        middlename = m
        lastname = l
        suffix = s
        email = e
        phone = p
        altphone = ap
        address = addr;
    }
    init(dict:[String:Any]){
        firstname = dict["GivenName"] as? String ?? ""
        middlename = dict["MiddleName"] as? String ?? ""
        lastname = dict["FamilyName"] as? String ?? ""
        suffix = dict["Suffix"] as? String ?? ""
        let addressdict = dict["ShipAddr"] as? [String:Any]
        let emaildict = dict["PrimaryEmailAddr"] as? [String:Any]
        let phonedict = dict["PrimaryPhone"] as? [String:Any]
        let altphonedict = dict["AlternatePhone"] as? [String:Any]
        email = emaildict?["Address"] as? String ?? ""
        phone = phonedict?["FreeFormNumber"] as? String ?? ""
        altphone = altphonedict?["AlternatePhone"] as? String ?? ""
        address = Addr.init(dict: addressdict ?? Dictionary.init())
    }
}
class AccessToken{
    let decode_error = "Error decoding AccessToken from peristent memory."
    var accessToken:String
    var accessTokenExpiresAt:Date
    var refreshToken:String
    var refreshTokenExpiresAt:Date
    init(at:String,rt:String,atea:Date,rtea:Date){
        accessToken = at
        accessTokenExpiresAt = atea
        refreshTokenExpiresAt = rtea
        refreshToken = rt
    }
    init(dictionary: [String:Any]) {
        let defaultDateFormat = "yyyy/MM/dd HH:mm:ss"
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = defaultDateFormat
        accessToken = dictionary[Backend.at_key] as! String
        refreshToken = dictionary[Backend.rt_key] as! String
        var datestring = dictionary[Backend.rtea_key] as! String
        refreshTokenExpiresAt = dateFormatter.date(from: datestring) ?? Date.init()
        datestring = dictionary[Backend.atea_key] as! String
        accessTokenExpiresAt = dateFormatter.date(from: datestring) ?? Date.init()
    }
}

class Backend {
    static let defaultDateFormat = "yyyy/MM/dd HH:mm:ss"
    static let dateFormatter = DateFormatter()
    static let CONTENT = "Content-Type"
    static let JSON = "application/json"
    static let APPX = "application/x-www-form-urlencoded"
    static let AUTHORIZE_URL = "http://localhost:3000/authenticate"
    static let STATE = "state"
    static let CODE = "code"
    static let REALMID = "realmId"
    static let ACCESSTOKEN = "accessToken"
    static let REFRESHTOKEN = "refreshToken"
    static let username = "Q0TQ6lCBvimkFOSwfhUJtgUhTG2jTdS4eK7F2BxndS0VQYqNqy"
    static let password = "fSpYAppFDSo3Bv65caMDj4UM2WFuyKDkBwECMVHx"
    static let at_key = "access_token"
    static let rt_key = "refresh_token"
    static let atea_key = "expires_in"
    static let rtea_key = "x_refresh_token_expires_in"
    static var accessToken:AccessToken!
    static var customers:[Customer]!
    static var keychain = KeychainFacade()
    static func accessTokenIsValid() -> Bool {
        if (accessToken == nil){
            return false
        }
        else if(accessToken.accessTokenExpiresAt <= Date()){
            return false
        }
        else if(accessToken.refreshTokenExpiresAt <= Date()){
            return false
        }
        else{
            return true
        }
    }
    static func createRequest(headers:[String:String],method:String,url:URL) -> NSMutableURLRequest {
        let request = NSMutableURLRequest(url: url, cachePolicy: .useProtocolCachePolicy, timeoutInterval: 10.0)
        request.httpMethod = method
        request.allHTTPHeaderFields = headers
        return request
    }
    static func saveAccessToken(){
        do{
            dateFormatter.dateFormat = defaultDateFormat
            let atea_string = dateFormatter.string(from: accessToken.accessTokenExpiresAt)
            let rtea_string = dateFormatter.string(from: accessToken.refreshTokenExpiresAt)
            try keychain.set(string: accessToken.accessToken, forKey: at_key)
            try keychain.set(string: accessToken.refreshToken, forKey: rt_key)
            try keychain.set(string: atea_string, forKey: atea_key)
            try keychain.set(string: rtea_string, forKey: rtea_key)
        }
        catch let facadeError as KeychainFacadeError {
            print("Could not store credentials in the Keychain. \(facadeError)")
        }
        catch{
            print(error)
        }
    }
    static func loadAccessToken(){
        guard let at = try? keychain.get(forkey: at_key),
            let rt = try? keychain.get(forkey: rt_key),
            let atea = try? keychain.get(forkey: atea_key),
            let rtea = try? keychain.get(forkey: rtea_key)
        else {
                print("Could not retrieve access token from Keychain.")
                return
        }
        let a_t:[String:String?] = [at_key:at,
                                    rt_key:rt,
                                    atea_key:atea,
                                    rtea_key:rtea]
        accessToken = AccessToken(dictionary: a_t as [String:Any])
    }
    static func getAccessToken(){
        //pass code and realmId to as headers to POST http://localhost/authenticate
        //receive JSON object returned
        let headers = [
            CONTENT : APPX,
            "Connection": "keep-alive",
            "Cache-Control": "no-cache",
        ]
        let request = createRequest(headers: headers , method: "POST", url: URL(string:AUTHORIZE_URL+"/"+username+"/"+password)!)
        let session = URLSession.shared
        let dataTask = session.dataTask(with: request as URLRequest, completionHandler: { (data, response, error) -> Void in
            guard let dataResponse = data,
                error == nil else {
                    print(error?.localizedDescription ?? "Response Error")
                    return }
            do{
                //here dataResponse received from a network request
                let jsonResponse = try JSONSerialization.jsonObject(with:
                    dataResponse, options: [])
                let jsonArray = jsonResponse as! [String: Any]
                accessToken = AccessToken.init(dictionary: jsonArray)
            } catch let parsingError {
                print("Error", parsingError)
            }
        })
        dataTask.resume()
    }
    static func fetchCustomers(){
        
    }
    static func createCustomer(c:Customer!){
        
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
    static func randomString(length: Int) -> String {
        let letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
        return String((0..<length).map{ _ in letters.randomElement()! })
    }
    static func makeAPICall(){
        
    }
}

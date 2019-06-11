//
//  Backend.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/7/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import Foundation

class ReferenceType : Codable {
    var value:String
    init(id:String) {
        value = id
    }
    init(dict: [String:Any] ){
        value = dict["value"] as? String ?? ""
    }
}

/*class CurrencyRefType : Codable {
    var value:String
    init(id:String) {
        value = id
    }
    init(dict: [String:Any]){
        value = dict["value"] as? String ?? ""
    }
}*/

/*class MemoRef : Codable{
    var value:String
    init(value:String) {
        self.value = value
    }
    init(dict: [String:Any]){
        value = dict["value"] as? String ?? ""
    }
}*/

class SaleItemLineDetail : Codable {
    var DiscountAmt:Double?
    var DiscountRate:Double?
    var ItemRef:String?
    var Qty:Double
    var UnitPrice:Double
    init(q:Double, up: Double){
        Qty = q
        UnitPrice = up
    }
    required init(dict: [String:Any]){
        var temp = dict["DiscountAmt"] as? String ?? "0.0"
        DiscountAmt = Double(temp)
        temp = dict["DiscountRate"] as? String ?? "0.0"
        DiscountRate = Double(temp)
        ItemRef = dict["ItemRef"] as? String ?? ""
        temp = dict["Qty"] as? String ?? "0.0"
        Qty = Double(temp) ?? 0.0
        temp = dict["UnitPrice"] as? String ?? "0.0"
        UnitPrice = Double(temp) ?? 0.0
    }
}


class Telephone : Codable {
    var FreeFormNumber: String
    init(f: String){
        FreeFormNumber = f
    }
    init(dict: [String:Any]){
        FreeFormNumber = dict["FreeFormNumber"] as? String ?? ""
    }
}
class EmailAddr : Codable {
    var Address: String
    init(a: String){
        Address = a
    }
    init(dict: [String:Any]){
        Address = dict["Address"] as? String ?? ""
    }
}

class Addr : Codable {
    var Line1, City, CountrySubDivisionCode, PostalCode:String
    init(l:String, c:String, csd:String,p:String){
        Line1 = l;
        City = c;
        CountrySubDivisionCode = csd;
        PostalCode = p;
    }
    init(dict: [String:Any]){
        Line1 = dict["Line1"] as? String ?? ""
        City = dict["City"] as? String ?? ""
        CountrySubDivisionCode = dict["CountrySubDivisionCode"] as? String ?? ""
        PostalCode = dict["PostalCode"] as? String ?? ""
    }
}
class Customer : Codable {
    var DisplayName:String?
    var Id:String?
    var GivenName, MiddleName, FamilyName, Suffix, SyncToken, Notes: String
    var sparse:Bool?
    var ShipAddr: Addr!
    var PrimaryEmailAddr: EmailAddr
    var PrimaryPhone,AlternatePhone:Telephone
    init(f:String,m:String, l:String, s:String, e:EmailAddr, p:Telephone, ap:Telephone, addr: Addr, n: String){
        GivenName = f
        MiddleName = m
        FamilyName = l
        Suffix = s
        PrimaryEmailAddr = e
        PrimaryPhone = p
        AlternatePhone = ap
        ShipAddr = addr;
        Notes = n
        SyncToken = "0"
    }
    init(dict:[String:Any]){
        DisplayName = dict["DisplayName"] as? String ?? ""
        GivenName = dict["GivenName"] as? String ?? ""
        MiddleName = dict["MiddleName"] as? String ?? ""
        FamilyName = dict["FamilyName"] as? String ?? ""
        Suffix = dict["Suffix"] as? String ?? ""
        Id = dict["Id"] as? String ?? ""
        Notes = dict["Notes"] as? String ?? ""
        SyncToken = dict["SyncToken"] as? String ?? "0"
        let addressdict = dict["ShipAddr"] as? [String:Any]
        let emaildict = dict["PrimaryEmailAddr"] as? [String:Any]
        let phonedict = dict["PrimaryPhone"] as? [String:Any]
        let altphonedict = dict["AlternatePhone"] as? [String:Any]
        PrimaryEmailAddr = EmailAddr.init(dict: emaildict ?? Dictionary.init())
        PrimaryPhone = Telephone.init(dict: phonedict ?? Dictionary.init())
        AlternatePhone = Telephone.init(dict: altphonedict ?? Dictionary.init())
        ShipAddr = Addr.init(dict: addressdict ?? Dictionary.init())
    }
}

class Estimate : Codable {
    var Id:String?
    var CustomerRef:String?
    var SyncToken:String?
    var CurrencyRef:String?
    var TotalAmt:Double?
    var PrivateNote:String?
    var Line:[Lines]?
    var CustomerMemo:String?
    var EmailStatus:String?
    var AcceptedBy:String?
    var ShipAddr:Addr?
    var BillAddr:Addr?
    var BillEmail:EmailAddr?
    init() {
        SyncToken = "0"
        CurrencyRef =  "USD"
    }
    init(dict: [String:Any]) {
        Id = dict["Id"] as? String ?? ""
        CustomerRef = dict["CustomerRef"] as? String ?? ""
        SyncToken = dict["SyncToken"] as? String ?? "0"
        CurrencyRef = dict["CurrencyRef"] as? String ?? "USD"
        let temp = dict["TotalAmt"] as? String ?? "0.0"
        TotalAmt = Double(temp) ?? 0.0
        PrivateNote = dict["PrivateNote"] as? String ?? ""
        CustomerMemo = dict["CustomerMemo"] as? String ?? ""
        EmailStatus = dict["EmailStatus"] as? String ?? ""
        AcceptedBy = dict ["AcceptedBy"] as? String ?? ""
        let shipaddrdict = dict["ShipAddr"] as? [String:Any]
        let billaddrdict = dict["BillAddr"] as? [String:Any]
        let billemaildict = dict["BillEmail"] as? [String:Any]
        ShipAddr = Addr.init(dict: shipaddrdict ?? Dictionary.init())
        BillAddr = Addr.init(dict: billaddrdict ?? Dictionary.init())
        BillEmail = EmailAddr.init(dict: billemaildict ?? Dictionary.init())
        let linearray = dict["Line"] as? [[String:Any]] ?? [[String:Any]]()
        Line = [Lines]()
        for l in linearray {
            if l["DetailType"] as? String ?? "" == "SalesItemLineDetail" {
                Line?.append(Lines.init(dict: l))
            }
        }
    }
}

class Lines : Codable {
    var Id:String?
    var DetailType:String
    var SalesItemLineDetail:SaleItemLineDetail
    var Amount:Double
    var Description:String
    var LineNum:Int
    init(item:SaleItemLineDetail,d:String, ln:Int) {
        DetailType = "SalesItemLineDetail"
        Description = d
        LineNum = ln
        SalesItemLineDetail = item
        Amount = SalesItemLineDetail.UnitPrice * SalesItemLineDetail.Qty
    }
    init(dict:[String:Any]) {
        Id = dict["Id"] as? String ?? ""
        DetailType = dict["DetailType"] as? String ?? ""
        let salesdict = dict["SalesItemLineDetail"] as? [String:Any]
        SalesItemLineDetail = SaleItemLineDetail.init(dict: salesdict ?? Dictionary.init())
        let temp = dict["Amount"] as? String ?? "0.0"
        Amount = Double(temp) ?? 0.0
        Description = dict["Description"] as? String ?? ""
        let inttemp = dict["LineNum"] as? String ?? "0"
        LineNum = Int(inttemp) ?? 0
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
        dateFormatter.timeZone = TimeZone(identifier: "UTC")
        accessToken = dictionary[Backend.at_key] as! String
        refreshToken = dictionary[Backend.rt_key] as! String
        var datestring = dictionary[Backend.rtea_key] as! String
        refreshTokenExpiresAt = dateFormatter.date(from: datestring) ?? Date.init()
        datestring = dictionary[Backend.atea_key] as! String
        accessTokenExpiresAt = dateFormatter.date(from: datestring) ?? Date.init()
    }
}

class Backend {
    static var syncToken = 0
    static let defaultDateFormat = "yyyy/MM/dd HH:mm:ss"
    static let dateFormatter = DateFormatter()
    static let CONTENT = "Content-Type"
    static let JSON = "application/json"
    static let APPX = "application/x-www-form-urlencoded"
    static let AUTHORIZE_URL = "http://localhost:3000/authenticate"
    static let BASE_API_URL = "http://localhost:3000"
    static let STATE = "state"
    static let CODE = "code"
    static let REALMID = "realmId"
    static let ACCESSTOKEN = "accessToken"
    static let REFRESHTOKEN = "refreshToken"
    static let username = "Q0TQ6lCBvimkFOSwfhUJtgUhTG2jTdS4eK7F2BxndS0VQYqNqy"//client id
    static let password = "fSpYAppFDSo3Bv65caMDj4UM2WFuyKDkBwECMVHx"//client secret 
    static let at_key = "access_token"
    static let rt_key = "refresh_token"
    static let atea_key = "expires_in"
    static let rtea_key = "x_refresh_token_expires_in"
    static var accessToken:AccessToken!
    static var customers:[Customer]!
    static var keychain = KeychainFacade()
    static var returnEst:Estimate?
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
            dateFormatter.timeZone = TimeZone(identifier: "UTC")
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
    static func createCustomer(c:Customer!) -> Customer{
        var cus:Customer?
        DispatchQueue.global(qos: .userInitiated).sync {
            let group = DispatchGroup()
            //change customer to json
            let encoder = JSONEncoder()
            let jsonData = try! encoder.encode(c)
            //set headers
            let headers = [
                at_key:accessToken.accessToken,
                CONTENT:JSON
            ]
            print(String(data: jsonData, encoding: .utf8)!)
            //create request with headers
            let request = createRequest(headers: headers, method: "POST", url: URL(string: BASE_API_URL + "/customers")!)
            request.httpBody = jsonData
            //create session
            let session = URLSession.shared
            //create datatask with session and request and completion handler
            group.enter()
            let dataTask = session.dataTask(with: request as URLRequest, completionHandler:{
                (data, response, error) -> Void in
                guard let dataResponse = data,
                    error == nil else {
                        print(error?.localizedDescription ?? "Response Error")
                        return }
                do{
                    //here dataResponse received from a network request
                    print(String(data: dataResponse, encoding: .utf8)!)
                    let jsonResponse = try JSONSerialization.jsonObject(with:
                        dataResponse, options: [])
                    let jsonArray = jsonResponse as! [String: Any]
                    cus = Customer.init(dict: jsonArray)
                    group.leave()
                } catch let parsingError {
                    print("Error", parsingError)
                }
            })
            //data tast resume
            dataTask.resume()
            group.wait()
        }
        return cus!
    }
    static func updateCustomer(c:Customer){
        c.sparse = true
        let encoder = JSONEncoder()
        let jsonData = try! encoder.encode(c)
        let headers = [
            at_key:accessToken.accessToken,
            CONTENT:JSON
        ]
        //create request with headers
        let request = createRequest(headers: headers, method: "POST", url: URL(string: BASE_API_URL + "/customers" + "/update")!)
        request.httpBody = jsonData
        //create session
        let session = URLSession.shared
        let dataTask = session.dataTask(with: request as URLRequest, completionHandler:{
            (data, response, error) -> Void in
            if (error != nil) {
                //if error tell user there was an error
                print(error!)
            }
            else{
                //if not, say successful add
                print("success")
            }
        })
        //data tast resume
        dataTask.resume()
    }
    static func deleteCustomer(){
    }
    static func fetchEstimate(){
    }
    static func createEstimate(est:Estimate) -> Estimate{
        DispatchQueue.global(qos: .userInitiated).sync {
            let downloadgroup = DispatchGroup()
            
            let encoder = JSONEncoder()
            let jsonData = try! encoder.encode(est)
            //set headers
            let headers = [
                at_key:accessToken.accessToken,
                CONTENT:JSON
            ]
            //create request with headers
            let request = createRequest(headers: headers, method: "POST", url: URL(string: BASE_API_URL + "/estimates")!)
            request.httpBody = jsonData
            //create session
            let session = URLSession.shared
            //create datatask with session and request and completion handler
            downloadgroup.enter()
            let dataTask = session.dataTask(with: request as URLRequest, completionHandler:{
                (data, response, error) -> Void in
                guard let dataResponse = data,
                    error == nil else {
                        print(error?.localizedDescription ?? "Response Error")
                        return }
                do{
                    //here dataResponse received from a network request
                    print(String(data: dataResponse, encoding: .utf8)!)
                    let jsonResponse = try JSONSerialization.jsonObject(with:
                        dataResponse, options: [])
                    let jsonArray = jsonResponse as! [String: Any]
                    returnEst = Estimate.init(dict: jsonArray)
                    downloadgroup.leave()
                } catch let parsingError {
                    print("Error", parsingError)
                }
            })
            //data tast resume
            dataTask.resume()
            downloadgroup.wait()
        }
        return returnEst!
    }
    static func deleteEstimate(){
    }
    static func sendEstimate(est: Estimate){
        DispatchQueue.global(qos: .userInitiated).sync {
            let downloadgroup = DispatchGroup()
            
            let encoder = JSONEncoder()
            let jsonData = try! encoder.encode(est)
            //set headers
            let headers = [
                at_key:accessToken.accessToken,
                CONTENT:JSON
            ]
            print(String(data: jsonData, encoding: .utf8)!)
            //create request with headers
            let request = createRequest(headers: headers, method: "POST", url: URL(string: BASE_API_URL + "/estimates/send")!)
            request.httpBody = jsonData
            //create session
            let session = URLSession.shared
            //create datatask with session and request and completion handler
            downloadgroup.enter()
            let dataTask = session.dataTask(with: request as URLRequest, completionHandler:{
                (data, response, error) -> Void in
                guard let dataResponse = data,
                    error == nil else {
                        print(error?.localizedDescription ?? "Response Error")
                        return }
                do{
                    //here dataResponse received from a network request
                    print(String(data: dataResponse, encoding: .utf8)!)
                    let jsonResponse = try JSONSerialization.jsonObject(with:
                        dataResponse, options: [])
                    let jsonArray = jsonResponse as! [String: Any]
                    returnEst = Estimate.init(dict: jsonArray)
                    downloadgroup.leave()
                } catch let parsingError {
                    print("Error", parsingError)
                }
            })
            //data tast resume
            dataTask.resume()
            downloadgroup.wait()
        }
    }
    static func randomString(length: Int) -> String {
        let letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
        return String((0..<length).map{ _ in letters.randomElement()! })
    }
}




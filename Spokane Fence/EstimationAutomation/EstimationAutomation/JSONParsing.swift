//
//  JSONParsing.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/16/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import Foundation

protocol JSONDecodable {
    init(_ decoder: JSONDecoderer) throws
}
enum JSONParsingError: Error{
    case missingKey(key: String)
    case typeMismatch(key: String)
}

typealias JSONObject = [String:Any]
class JSONDecoderer {
    let jsonObject: JSONObject
    init(_ jsonObject: JSONObject){
        self.jsonObject = jsonObject
    }
    func value<T>(forKey key: String) throws -> T{
        guard let value = jsonObject[key] else {throw JSONParsingError.missingKey(key: key)}
        guard let finalvalue  = value as? T else {throw JSONParsingError.typeMismatch(key: key)}
        return finalvalue
    }
    static let defaultDateFormat = "yyyy/MM/dd HH:mm:ss"
    private lazy var dateFormatter = DateFormatter()
    func value(forKey key: String, format: String = JSONDecoderer.defaultDateFormat) throws -> Date {
        let dateValue: String = try value(forKey: key)
        dateFormatter.dateFormat = format
        guard let returnValue = dateFormatter.date(from: dateValue) else {throw JSONParsingError.typeMismatch(key: key)}
        return returnValue
    }
}

func parse<T>(_ data: Data) throws -> [T] where T: JSONDecodable {
    let jsonObjects: [JSONObject] = try deserialize(data)
    return try jsonObjects.map(decode)
}

func deserialize(_ data: Data) throws -> [JSONObject] {
    let json = try JSONSerialization.jsonObject(with: data, options: [])
    let objects = json as! [JSONObject]
    return objects
}

func decode<T>(_ jsonObject: JSONObject) throws -> T where T: JSONDecodable {
    return try T.init(JSONDecoderer(jsonObject))
}


/*    "CustomerRef": "60",
 "BillAddr": {
 "Id": 128,
 "Line1": "411 S 2060 W",
 "City": "Vineyard",
 "CountrySubDivisionCode": "UT",
 "PostalCode": "84059"
 },
 "ShipAddr": {
 "Id": "129",
 "Line1": "411 S 2060 W",
 "City": "Vineyard",
 "CountrySubDivisionCode": "UT",
 "PostalCode": "84059"
 },
 "TotalAmt": "0",
 "ApplyTaxAfterDiscount": "false",
 "PrintStatus": "NeedToPrint",
 "EmailStatus": "NotSet",
 "BillEmail": {
 "Address": "torndorff5@gmail.com"
 },
 "DocNumber": "1011",
 "TxnDate": "2019-06-11",
 "CurrencyRef": "USD",
 "PrivateNote": "This guys just wants gates apparently.",
 "TxnStatus": "Pending",
 "Line": [
 {
 "Id": "1",
 "LineNum": "1",
 "Description": "Left Return: 6.0 ft x 2.0 ft Vinyl Gate with hardware",
 "Amount": "0",
 "DetailType": "SalesItemLineDetail",
 "SalesItemLineDetail": {
 "ItemRef": "1",
 "UnitPrice": "0",
 "Qty": "1",
 "ItemAccountRef": "1"
 }
 },
 {
 "Id": "2",
 "LineNum": "2",
 "Description": "Left Return: 6.0 ft x 2.0 ft Vinyl Gate with hardware",
 "Amount": "0",
 "DetailType": "SalesItemLineDetail",
 "SalesItemLineDetail": {
 "ItemRef": "1",
 "UnitPrice": "0",
 "Qty": "1",
 "ItemAccountRef": "1"
 }
 },
 {
 "Id": "3",
 "LineNum": "3",
 "Description": "Right Return: 6.0 ft x 4.0 ft Vinyl Gate with hardware",
 "Amount": "0",
 "DetailType": "SalesItemLineDetail",
 "SalesItemLineDetail": {
 "ItemRef": "1",
 "UnitPrice": "0",
 "Qty": "1",
 "ItemAccountRef": "1"
 }
 },
 {
 "Id": "4",
 "LineNum": "4",
 "Description": "Left Return: 6.0 ft x 8.0 ft Vinyl Gate with hardware",
 "Amount": "0",
 "DetailType": "SalesItemLineDetail",
 "SalesItemLineDetail": {
 "ItemRef": "1",
 "UnitPrice": "0",
 "Qty": "1",
 "ItemAccountRef": "1"
 }
 }
 ],
 "Id": "155",
 "SyncToken": "0"
 }*/

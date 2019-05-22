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

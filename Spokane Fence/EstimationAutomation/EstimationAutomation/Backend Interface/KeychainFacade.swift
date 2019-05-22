//
//  KeychainFacade.swift
//  EstimationAutomation
//
//  Created by codeslinger on 5/22/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import Foundation
import Security

public enum KeychainFacadeError: Error {
    case invalidContent
    case failure(OSStatus)
}

class KeychainFacade {
    private func setUpQueryDict(forKey key: String) -> [String:Any] {
        var querydict: [String:Any] = [kSecClass as String:kSecClassGenericPassword]
        querydict[kSecAttrAccount as String] = key.data(using: .utf8)
        return querydict
    }
    
    public func set(string: String, forKey key: String) throws {
        guard !string.isEmpty && !key.isEmpty else {
            print("Can't add empty value to Keychain")
            throw KeychainFacadeError.invalidContent
        }
        do{
            try remove(forKey: key)
        } catch{
            print("Not a Duplicate")
        }
        var querydict = setUpQueryDict(forKey: key)
        querydict[kSecValueData as String] = string.data(using: .utf8)
        let status = SecItemAdd(querydict as CFDictionary, nil)
        if status != errSecSuccess {
            throw KeychainFacadeError.failure(status)
        }
    }
    public func remove(forKey key: String) throws {
        guard !key.isEmpty else {
            print("Key must be valid")
            throw KeychainFacadeError.invalidContent
        }
        let querydict = setUpQueryDict(forKey: key)
        let status = SecItemDelete(querydict as CFDictionary)
        if status != errSecSuccess {
            throw KeychainFacadeError.failure(status)
        }
    }
    public func get(forkey key: String) throws -> String? {
        guard !key.isEmpty else {
            print("Key must be valid")
            throw KeychainFacadeError.invalidContent
        }
        var querydict = setUpQueryDict(forKey: key)
        querydict[kSecReturnData as String] = kCFBooleanTrue
        querydict[kSecMatchLimit as String] = kSecMatchLimitOne
        var data:AnyObject?
        let status = SecItemCopyMatching(querydict as CFDictionary, &data)
        if status != errSecSuccess {
            throw KeychainFacadeError.failure(status)
        }
        let result:String?
        if let item = data as? Data {
            result = String(data: item, encoding: .utf8)
        } else {
            result = nil
        }
        return result
    }
}

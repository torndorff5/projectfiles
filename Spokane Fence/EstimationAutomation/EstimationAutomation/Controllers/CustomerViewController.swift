//
//  NewCustomerViewController.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/7/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import UIKit

class CustomerViewController: UIViewController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    @IBOutlet weak var firstname: UITextField!
    @IBOutlet weak var middlename: UITextField!
    @IBOutlet weak var lastname: UITextField!
    @IBOutlet weak var suffix: UITextField!
    @IBOutlet weak var email: UITextField!
    @IBOutlet weak var phone: UITextField!
    @IBOutlet weak var altphone: UITextField!
    @IBOutlet weak var address: UITextField!
    @IBOutlet weak var city: UITextField!
    @IBOutlet weak var state: UITextField!
    @IBOutlet weak var zip: UITextField!
    @IBOutlet weak var notes: UITextView!
    
    
    
    @IBAction func createCustomer(_ sender: Any) {
        //create customer
        let physAddr = Addr.init(l: address.text ?? "",c: city.text ?? "",csd: state.text ?? "",p: zip.text ?? "");
        let phoneobj = Telephone.init(f: phone.text ?? "")
        let altphoneobj = Telephone.init(f: altphone.text ?? "")
        let emailobj = EmailAddr.init(a: email.text ?? "")
        let customer = Customer.init(f: firstname.text ?? "", m: middlename.text ?? "", l: lastname.text ?? "", s: suffix.text ?? "", e: emailobj, p: phoneobj, ap: altphoneobj, addr: physAddr, n: notes.text ?? "");
        
        firstname.text=""
        middlename.text=""
        lastname.text=""
        suffix.text = ""
        email.text = ""
        phone.text = ""
        altphone.text = ""
        address.text = ""
        city.text = ""
        state.text = ""
        zip.text = ""
        notes.text = ""

        //add to quickbooks
        if(!Backend.accessTokenIsValid()){
            //reauth
            print("invalid access token")
        }
        Backend.createCustomer(c: customer)
    }
    
    
}


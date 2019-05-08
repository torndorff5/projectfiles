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
    @IBAction func createCustomer(_ sender: Any) {
        Customer.fetchCustomer();
        //create customer
        //add to quickbooks
    }
    
    
}


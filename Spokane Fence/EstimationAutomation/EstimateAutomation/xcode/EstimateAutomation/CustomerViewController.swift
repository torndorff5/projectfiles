//
//  MyViewController.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/6/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import UIKit

class CustomerViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
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
        //save customer to quickbooks
        Customer.fetchCustomer();
        //use interface function 
        //open create estimate page 
    }
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}

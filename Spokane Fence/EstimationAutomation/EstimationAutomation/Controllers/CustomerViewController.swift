//
//  NewCustomerViewController.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/7/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import UIKit

class CustomerViewController: UIViewController , UITextViewDelegate{
    
    var customer:Customer?
    var firstTime:Bool?
    override func viewDidLoad() {
        super.viewDidLoad()
        notes.delegate = self
        firstTime = true
        activity.isHidden = true
        // Do any additional setup after loading the view, typically from a nib.
    }
    var validatedFirstname, validatedLastname, validatedEmail, validatedPhone, validatedAddress, validatedState, validatedZip:String?
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
    @IBOutlet weak var activity: UIActivityIndicatorView!

    func showAlert(message: String){
        let alert = UIAlertController(title: "Form Validation", message: message, preferredStyle: .alert )
        let action = UIAlertAction(title: "Dismiss", style: .default, handler: nil)
        alert.addAction(action)
        self.present(alert, animated: true, completion: nil)
    }
    
    func validateForm() -> Bool {
        if(Validation.isFirstNameValid(firstname.text ?? "")){
            validatedFirstname = firstname.text
        }
        else{
            showAlert(message: "Please Enter First Name")
            return false
        }
        if(Validation.isLastNameValid(lastname.text ?? "")){
            validatedLastname = lastname.text
        }
        else{
            showAlert(message: "Please Enter Last Name")
            return false
        }
        if(Validation.isEmailValid(email.text ?? "")){
            validatedEmail = email.text
        }
        else{
            showAlert(message: "Invalid Email")
            return false
        }
        if(Validation.isPhoneValid(phone.text ?? "")){
            validatedPhone = phone.text
        }
        else {
            showAlert(message: "Invalid Phone Number")
            return false
        }
        if(Validation.isStateValid(state.text ?? "")){
            validatedState = state.text
        }
        else {
            showAlert(message: "Invalid State (ex: WA)")
            return false
        }
        if(Validation.isZipValid(zip.text ?? "")){
            validatedZip = zip.text
        }
        else {
            showAlert(message: "Invalid Zip")
            return false
        }
        return true
    }
    
    @IBAction func createCustomer(_ sender: Any) {
        self.activity.isHidden = false
        self.activity.startAnimating()
        if validateForm() {
            //create customer
            let physAddr = Addr.init(l: address.text ?? "",c: city.text ?? "",csd: state.text ?? "",p: zip.text ?? "");
            let phoneobj = Telephone.init(f: phone.text ?? "")
            let altphoneobj = Telephone.init(f: altphone.text ?? "")
            let emailobj = EmailAddr.init(a: email.text ?? "")
            customer = Customer.init(f: firstname.text ?? "", m: middlename.text ?? "", l: lastname.text ?? "", s: suffix.text ?? "", e: emailobj, p: phoneobj, ap: altphoneobj, addr: physAddr, n: notes.text ?? "");

            //add to quickbooks
            //Backend.validateToken()
            customer = Backend.createCustomer(c: customer)
            //stop activity indicator
            if customer != nil {
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
                //show alert that says either customer was successfully created
                self.activity.stopAnimating()
                let alert = UIAlertController(title: "QuickBooks Notification", message: "Customer Successfully Created", preferredStyle: .alert )
                let action = UIAlertAction(title: "Ok", style: .default, handler: { (action) in
                    self.performSegue(withIdentifier: "showCreateEstimate", sender: nil)
                })
                alert.addAction(action)
                self.present(alert, animated: true, completion: nil)
            }
            else {
                self.activity.stopAnimating()
                //show alert that says it failed and give reason why
                let alert = UIAlertController(title: "QuickBooks Notification", message: "Network Error", preferredStyle: .alert )
                let action = UIAlertAction(title: "Ok", style: .default, handler: nil)
                alert.addAction(action)
                self.present(alert, animated: true, completion: nil)
            }
        }
        activity.stopAnimating()
    }
    
    func textViewDidBeginEditing(_ textView: UITextView) {
        if firstTime == true {
            textView.text = ""
            firstTime = !firstTime!
        }
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if let destVC = segue.destination as? CreateEstimateViewController{
            destVC.cus = customer!
        }
    }
    
}


//
//  ViewController.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/7/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import UIKit
import SafariServices

class ViewController: UIViewController, SFSafariViewControllerDelegate {
    @IBOutlet weak var connectToQBO: UIButton!
    @IBOutlet weak var createEstimate: UIButton!
    
    func safariViewControllerDidFinish(_ controller: SFSafariViewController) {
        Backend.getAccessToken();
        //display create estimate button
        createEstDisplay()
    }
    
    func createEstDisplay(){
        connectToQBO.isHidden = true
        createEstimate.isHidden = false
    }
    func connectQBDisplay(){
        createEstimate.isHidden = true
        connectToQBO.isHidden = false
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        //load access token
        //if we have an access token, display create estimate
        if(!Backend.accessTokenIsValid()){
            //display connect to QB
            connectQBDisplay()
        }
        else{
            //display create estimate button
            createEstDisplay()
        }
    }
    
    @IBAction func connectToQBO(_ sender: Any) {
        let url = URL(string: Backend.AUTHORIZE_URL)
        let safariVC = SFSafariViewController(url: url!)
        safariVC.delegate = self
        self.present(safariVC, animated: true, completion: nil)
    }
}





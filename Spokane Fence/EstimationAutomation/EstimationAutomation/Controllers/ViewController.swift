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
    @IBOutlet weak var activity: UIActivityIndicatorView!

    func safariViewControllerDidFinish(_ controller: SFSafariViewController) {
        Backend.getAccessToken();
        //display create estimate button
        createEstDisplay()
    }
    
    func createEstDisplay(){
        activity.stopAnimating()
        connectToQBO.isHidden = true
        createEstimate.isHidden = false
    }
    func connectQBDisplay(){
        activity.stopAnimating()
        createEstimate.isHidden = true
        connectToQBO.isHidden = false
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        //load access token
        //if we have an access token, display create estimate
        if Backend.accessTokenIsValid() {
            createEstDisplay()
        }
        else if Backend.refreshTokenIsValid() {
            let at = Backend.refreshToken()
            if at {
                createEstDisplay()
            }
            else {
                connectQBDisplay()
            }
        }
        else {
            connectQBDisplay()
        }
    }
    @IBAction func unwindToHome(_ unwindSegue: UIStoryboardSegue) {
        // Use data from the view controller which initiated the unwind segue
    }
    
    @IBAction func connectToQBO(_ sender: Any) {
        let safariVC = Backend.safariVCinit()
        safariVC.delegate = self
        self.present(safariVC, animated: true, completion: nil)
    }
}





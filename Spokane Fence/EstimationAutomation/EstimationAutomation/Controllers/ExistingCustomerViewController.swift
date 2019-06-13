//
//  ExistingCustomerView.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/14/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import UIKit
import SafariServices

class ExistingCustomerViewController: UIViewController, UITableViewDataSource, UITableViewDelegate, SFSafariViewControllerDelegate {
    
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var activity: UIActivityIndicatorView!

    var data = [Customer]()
    var current:Customer?
    
    override func viewDidLoad() {
        tableView.isHidden = true
        super.viewDidLoad()
        loadCustomers()
        tableView.delegate = self
        activity.stopAnimating()
        tableView.isHidden = false
    }
    override func viewDidAppear(_ animated: Bool) {
        self.tableView.reloadData()
    }

    func getNewToken(){
        let safariVC = Backend.safariVCinit()
        safariVC.delegate = self
        safariVC.present(self, animated: true, completion: nil)
    }
    
    func loadCustomers(){
        if !Backend.validateToken() {
            getNewToken()
        }
        //get json objects
        let headers = [
            Backend.CONTENT : Backend.JSON,
            Backend.at_key : Backend.accessToken.accessToken,
            Backend.rt_key : Backend.accessToken.refreshToken
        ]
        let request = Backend.createRequest(headers: headers , method: "GET", url: URL(string:"http://localhost:3000/customers")!)
        let session = URLSession.shared
        let dataTask = session.dataTask(with: request as URLRequest, completionHandler: { (data, response, error) -> Void in
            guard let dataResponse = data,
                error == nil else {
                    print(error?.localizedDescription ?? "Response Error")
                    return }
            do{
                ////convert to customer objects
                //store and return as data
                let jsonResponse = try JSONSerialization.jsonObject(with:
                    dataResponse, options: [])
                let jsonArray = jsonResponse as! [[String:Any]]
                DispatchQueue.main.async {
                    for object in jsonArray {
                        self.data.append(Customer.init(dict: object))
                    }
                    //reload table data
                    self.tableView.reloadData()
                }
            } catch let parsingError {
                print("Error", parsingError)
            }
        })
        dataTask.resume()
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return data.count;
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "customercell", for: indexPath) as! CustomerCellTableViewCell
        let cus = data[indexPath.row]
        let addr = cus.ShipAddr
        cell.customerName.text = NSString(format:"%@ %@ %@",cus.GivenName, cus.MiddleName, cus.FamilyName) as String
        cell.customerAddress.text = NSString(format:"%@ %@, %@ %@",addr!.Line1, addr!.City, addr!.CountrySubDivisionCode,addr!.PostalCode) as String
        cell.customerPhone.text = cus.PrimaryPhone.FreeFormNumber
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        current = data[indexPath.row]
        performSegue(withIdentifier: "showDetailExisting", sender: nil)
    }

    func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCell.EditingStyle, forRowAt indexPath: IndexPath) {
        if editingStyle == .delete {
            let alert = UIAlertController(title: "QuickBooks Online Message", message: "Are you sure you want to delete this customer? Its data will also be removed from your QuickBoooks account.", preferredStyle: .alert)
            let yes = UIAlertAction(title: "Yes", style: .destructive) { (action) in
                self.activity.startAnimating()
                self.activity.isHidden = false
                let cus = self.data[indexPath.row]
                self.data.remove(at: indexPath.row)
                self.tableView.reloadData()
                self.deleteCustomer(cus: cus)
            }
            let no = UIAlertAction(title: "Cancel", style: .cancel, handler: nil)
            alert.addAction(yes)
            alert.addAction(no)
            self.present(alert, animated: true, completion: nil)
        }
    }

    func deleteCustomer (cus: Customer) {
        //remove from QBO
        if Backend.deleteCustomer(cus: cus) {
            activity.stopAnimating()
            showAlert(message: "Customer successfully deleted.")
        }
        else {
            activity.stopAnimating()
            showAlert(message: "Failed to delete customer: Unknown Network Error")
        }
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if let viewController = segue.destination as? CustomerDetailViewController {
            viewController.customer = current
        }
    }

    func safariViewControllerDidFinish(_ controller: SFSafariViewController) {
        Backend.getAccessToken();
    }

    func showAlert(message: String) {
        let alert = UIAlertController(title: "QuickBooks Online Message", message: message, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "Dismiss", style: .default, handler: nil))
        present(alert, animated: true, completion: nil)
    }
}



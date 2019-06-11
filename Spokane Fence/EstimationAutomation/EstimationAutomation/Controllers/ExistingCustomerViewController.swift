//
//  ExistingCustomerView.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/14/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import UIKit

class ExistingCustomerViewController: UIViewController, UITableViewDataSource, UITableViewDelegate {
    
    @IBOutlet weak var tableView: UITableView!
    
    var data = [Customer]()
    var current:Customer?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        loadCustomers()
        tableView.delegate = self
    }
    override func viewDidAppear(_ animated: Bool) {
        self.tableView.reloadData()
    }
    
    func loadCustomers(){
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
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if let viewController = segue.destination as? CustomerDetailViewController {
            viewController.customer = current
        }
    }
    
}



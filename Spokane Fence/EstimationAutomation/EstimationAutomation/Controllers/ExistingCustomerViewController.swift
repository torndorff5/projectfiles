//
//  ExistingCustomerView.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/14/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import UIKit

class ExistingCustomerViewController: UIViewController, UITableViewDataSource {
    
    @IBOutlet weak var tableView: UITableView!
    
    var data = [Customer]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        loadCustomers()
    }
    
    func loadCustomers(){
        //get json objects
        let headers = [
            Backend.CONTENT : Backend.JSON,
            Backend.ACCESSTOKEN : Backend.accessToken.accessToken,
            Backend.REFRESHTOKEN : Backend.accessToken.refreshToken
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
        let addr = cus.address
        cell.customerName.text = NSString(format:"%@ %@ %@",cus.firstname, cus.middlename, cus.lastname) as String
        cell.customerAddress.text = NSString(format:"%@ %@, %@ %@",addr!.line1, addr!.city, addr!.countrysubdiv,addr!.postal) as String
        cell.customerPhone.text = cus.phone
        return cell
    }
    
    
}



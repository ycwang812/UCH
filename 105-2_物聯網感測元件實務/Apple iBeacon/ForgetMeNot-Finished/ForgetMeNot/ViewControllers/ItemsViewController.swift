/*
 * Copyright (c) 2017 Razeware LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

import UIKit
import CoreLocation

let storedItemsKey = "storedItems"

class ItemsViewController: UIViewController {
	
  @IBOutlet weak var tableView: UITableView!
  
  var items = [Item]()
  let locationManager = CLLocationManager()
  
  override func viewDidLoad() {
    super.viewDidLoad()
    
    locationManager.delegate = self
    locationManager.requestAlwaysAuthorization()
    
    loadItems()
  }
  
  func loadItems() {
    guard let storedItems = UserDefaults.standard.array(forKey: storedItemsKey) as? [Data] else { return }
    for itemData in storedItems {
      guard let item = NSKeyedUnarchiver.unarchiveObject(with: itemData) as? Item else { continue }
      items.append(item)
      startMonitoringItem(item)
    }
  }
  
  func persistItems() {
    var itemsData = [Data]()
    for item in items {
      let itemData = NSKeyedArchiver.archivedData(withRootObject: item)
      itemsData.append(itemData)
    }
    UserDefaults.standard.set(itemsData, forKey: storedItemsKey)
    UserDefaults.standard.synchronize()
  }

  func startMonitoringItem(_ item: Item) {
    let beaconRegion = item.asBeaconRegion()
    locationManager.startMonitoring(for: beaconRegion)
    locationManager.startRangingBeacons(in: beaconRegion)
  }
  
  func stopMonitoringItem(_ item: Item) {
    let beaconRegion = item.asBeaconRegion()
    locationManager.stopMonitoring(for: beaconRegion)
    locationManager.stopRangingBeacons(in: beaconRegion)
  }
  
  override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
    if segue.identifier == "segueAdd", let viewController = segue.destination as? AddItemViewController {
      viewController.delegate = self
    }
  }
  
}

extension ItemsViewController: AddBeacon {
  func addBeacon(item: Item) {
    items.append(item)
    
    tableView.beginUpdates()
    let newIndexPath = IndexPath(row: items.count - 1, section: 0)
    tableView.insertRows(at: [newIndexPath], with: .automatic)
    tableView.endUpdates()
    
    startMonitoringItem(item)
    persistItems()
  }
}

// MARK: UITableViewDataSource
extension ItemsViewController : UITableViewDataSource {
  func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
    return items.count
  }
  
  func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
    let cell = tableView.dequeueReusableCell(withIdentifier: "Item", for: indexPath) as! ItemCell
    cell.item = items[indexPath.row]
    
    return cell
  }
  
  func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
    return true
  }
  
  func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
    
    if editingStyle == .delete {
      stopMonitoringItem(items[indexPath.row])
      
      tableView.beginUpdates()
      items.remove(at: indexPath.row)
      tableView.deleteRows(at: [indexPath], with: .automatic)
      tableView.endUpdates()
      
      persistItems()
    }
  }
}

// MARK: UITableViewDelegate
extension ItemsViewController: UITableViewDelegate {
  func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
    tableView.deselectRow(at: indexPath, animated: true)
    
    let item = items[indexPath.row]
    let detailMessage = "UUID: \(item.uuid.uuidString)\nMajor: \(item.majorValue)\nMinor: \(item.minorValue)"
    let detailAlert = UIAlertController(title: "Details", message: detailMessage, preferredStyle: .alert)
    detailAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
    self.present(detailAlert, animated: true, completion: nil)
  }
}

// MARK: CLLocationManagerDelegate
extension ItemsViewController: CLLocationManagerDelegate {
  func locationManager(_ manager: CLLocationManager, monitoringDidFailFor region: CLRegion?, withError error: Error) {
    print("Failed monitoring region: \(error.localizedDescription)")
  }
  
  func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
    print("Location manager failed: \(error.localizedDescription)")
  }
  
  func locationManager(_ manager: CLLocationManager, didRangeBeacons beacons: [CLBeacon], in region: CLBeaconRegion) {
    
    // Find the same beacons in the table.
    var indexPaths = [IndexPath]()
    for beacon in beacons {
      for row in 0..<items.count {
        if items[row] == beacon {
          items[row].beacon = beacon
          indexPaths += [IndexPath(row: row, section: 0)]
        }
      }
    }
    
    // Update beacon locations of visible rows.
    if let visibleRows = tableView.indexPathsForVisibleRows {
      let rowsToUpdate = visibleRows.filter { indexPaths.contains($0) }
      for row in rowsToUpdate {
        let cell = tableView.cellForRow(at: row) as! ItemCell
        cell.refreshLocation()
      }
    }
    
  }
}


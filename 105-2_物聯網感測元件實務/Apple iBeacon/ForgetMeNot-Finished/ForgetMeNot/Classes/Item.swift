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

import Foundation
import CoreLocation

struct ItemConstant {
  static let nameKey = "name"
  static let iconKey = "icon"
  static let uuidKey = "uuid"
  static let majorKey = "major"
  static let minorKey = "minor"
}

class Item: NSObject, NSCoding {
  let name: String
  let icon: Int
  let uuid: UUID
  let majorValue: CLBeaconMajorValue
  let minorValue: CLBeaconMinorValue
  var beacon: CLBeacon?
  
  init(name: String, icon: Int, uuid: UUID, majorValue: Int, minorValue: Int) {
    self.name = name
    self.icon = icon
    self.uuid = uuid
    self.majorValue = CLBeaconMajorValue(majorValue)
    self.minorValue = CLBeaconMinorValue(minorValue)
  }

  // MARK: NSCoding
  required init(coder aDecoder: NSCoder) {
    let aName = aDecoder.decodeObject(forKey: ItemConstant.nameKey) as? String
    name = aName ?? ""
    
    let aUUID = aDecoder.decodeObject(forKey: ItemConstant.uuidKey) as? UUID
    uuid = aUUID ?? UUID()
    
    icon = aDecoder.decodeInteger(forKey: ItemConstant.iconKey)
    majorValue = UInt16(aDecoder.decodeInteger(forKey: ItemConstant.majorKey))
    minorValue = UInt16(aDecoder.decodeInteger(forKey: ItemConstant.minorKey))
  }
  
  func encode(with aCoder: NSCoder) {
    aCoder.encode(name, forKey: ItemConstant.nameKey)
    aCoder.encode(icon, forKey: ItemConstant.iconKey)
    aCoder.encode(uuid, forKey: ItemConstant.uuidKey)
    aCoder.encode(Int(majorValue), forKey: ItemConstant.majorKey)
    aCoder.encode(Int(minorValue), forKey: ItemConstant.minorKey)
  }

  func asBeaconRegion() -> CLBeaconRegion {
    return CLBeaconRegion(proximityUUID: uuid,
                          major: majorValue,
                          minor: minorValue,
                          identifier: name)
  }
  
  func locationString() -> String {
    guard let beacon = beacon else { return "Location: Unknown" }
    let proximity = nameForProximity(beacon.proximity)
    let accuracy = String(format: "%.2f", beacon.accuracy)
    
    var location = "Location: \(proximity)"
    if beacon.proximity != .unknown {
      location += " (approx. \(accuracy)m)"
    }
    
    return location
  }
  
  func nameForProximity(_ proximity: CLProximity) -> String {
    switch proximity {
    case .unknown:
      return "Unknown"
    case .immediate:
      return "Immediate"
    case .near:
      return "Near"
    case .far:
      return "Far"
    }
  }
  
}

func ==(item: Item, beacon: CLBeacon) -> Bool {
    return ((beacon.proximityUUID.uuidString == item.uuid.uuidString)
        && (Int(beacon.major) == Int(item.majorValue))
        && (Int(beacon.minor) == Int(item.minorValue)))
}


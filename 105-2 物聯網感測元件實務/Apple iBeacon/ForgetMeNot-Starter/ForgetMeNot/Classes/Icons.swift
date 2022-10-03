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
import UIKit


enum Icons: Int {
  case bag = 0
  case brain
  case cat
  case glasses
  case key
  case wallet
  
  func image() -> UIImage? {
    return UIImage(named: "\(self.name())")
  }
  
  func name() -> String {
    switch self {
    case .bag: return "Icon_Bag"
    case .brain: return "Icon_Brain"
    case .cat: return "Icon_Cat"
    case .glasses: return "Icon_Glasses"
    case .key: return "Icon_Key"
    case .wallet: return "Icon_Wallet"
    }
  }
  
  static func icon(forTag tag: Int) -> Icons {
    return Icons(rawValue: tag) ?? .bag
  }
  
  static let allIcons: [Icons] = {
    var all = [Icons]()
    var index: Int = 0
    while let icon = Icons(rawValue: index) {
      all += [icon]
      index += 1
    }
    return all.sorted { $0.rawValue < $1.rawValue }
  }()
}

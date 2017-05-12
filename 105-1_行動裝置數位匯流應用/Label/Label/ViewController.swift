//
//  ViewController.swift
//  Label
//
//  Created by Administrator on 2016/10/4.
//  Copyright © 2016年 uch. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        let labelTest:UILabel = UILabel()
        labelTest.frame = CGRect(x: 60, y: 80, width: 240, height: 40)
        labelTest.text = "這是程式碼建立的元件"
        labelTest.textColor = UIColor.red
        view.addSubview(labelTest)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}


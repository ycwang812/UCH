//
//  ViewController.swift
//  SingleButton
//
//  Created by Administrator on 2016/10/11.
//  Copyright © 2016年 uch. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    @IBOutlet weak var textFieldName: UITextField!
    
    @IBOutlet weak var labelMsg: UILabel!
    
    @IBAction func sureClick(_ sender: UIButton) {
        if textFieldName.text != "" {
            labelMsg.text = (textFieldName.text)! + "，歡迎光臨！"
        } else {
            labelMsg.text = "必須輸入姓名！"
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        labelMsg.text = ""
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}


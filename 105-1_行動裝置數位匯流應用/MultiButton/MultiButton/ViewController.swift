//
//  ViewController.swift
//  MultiButton
//
//  Created by Administrator on 2016/10/18.
//  Copyright © 2016年 uch. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var labelTel: UILabel!
    
    @IBOutlet weak var labelMsg: UILabel!
    
    @IBAction func numberClick(_ sender: UIButton) {
        labelTel.text = labelTel.text! + sender.currentTitle!
    }
    
    @IBAction func sureClick(_ sender: UIButton) {
        if labelTel.text?.lengthOfBytes(using: String.Encoding.utf8) == 10 {
            labelMsg.text = "撥打電話：" + labelTel.text!
        } else {
            labelMsg.text = "必須輸入10個數字！"
        }
    }
    
    @IBAction func clearClick(_ sender: UIButton) {
        labelTel.text = ""
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}


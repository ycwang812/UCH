//
//  ViewController.swift
//  ProgramButton
//
//  Created by Administrator on 2016/10/18.
//  Copyright © 2016年 uch. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var labelTel: UILabel!
    @IBOutlet weak var labelMsg: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        for i in 0...11 {
            let x:Int = 80 + (i % 4) * 60
            let y:Int = 95 + (i / 4) * 50
            
            let buttonNumber:UIButton = UIButton(type: UIButtonType.system) as UIButton
            buttonNumber.frame = CGRect(x: x, y: y, width: 41, height: 35)
            buttonNumber.setTitleColor(UIColor.yellow, for: UIControlState())
            buttonNumber.titleLabel?.font = UIFont(name: "system", size: 22.0)
            
            if i == 10 {
                buttonNumber.setTitle("清除", for: UIControlState())
                buttonNumber.addTarget(self, action: #selector(ViewController.clearClick(_:)), for: UIControlEvents.touchUpInside)
            } else if i == 11 {
                buttonNumber.setTitle("確定", for: UIControlState())
                buttonNumber.addTarget(self, action: #selector(ViewController.sureClick(_:)), for: UIControlEvents.touchUpInside)
            } else {
                buttonNumber.setTitle("\(i)", for: UIControlState())
                buttonNumber.addTarget(self, action: #selector(ViewController.numberClick(_:)), for: UIControlEvents.touchUpInside)
            }
            
            view.addSubview(buttonNumber)
        }
    }

    func numberClick(_ sender:UIButton) {
        labelTel.text = labelTel.text! + sender.currentTitle!
    }
    
    func clearClick(_ sender:UIButton) {
        labelTel.text = ""
    }
    
    func sureClick(_ sender:UIButton) {
        if labelTel.text?.lengthOfBytes(using: String.Encoding.utf8) == 10 {
            labelMsg.text = "撥打電話：" + labelTel.text!
        } else {
            labelMsg.text = "必須輸入10個數字！"
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

}

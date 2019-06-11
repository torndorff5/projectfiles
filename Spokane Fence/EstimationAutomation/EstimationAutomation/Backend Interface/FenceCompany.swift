//
//  FenceCompany.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/16/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import Foundation

//ACCESSORY PRICES
let U_CHANNEL_STEEL_1X5X8 = 7.25
let INSERT_TWO_SIDED_4INX8FT = 28.5
let INSERT_Z_LINE_5INX8FT = 25
let INSERT_TWO_SIDED_5INX8F = 39.04
let INSERT_THREE_SIDED_5INX8FT = 50
let INSERT_GATE_ALUM_5INX8FT = 75
let CONCRETE_PRE_MIX_80LBS = 4.15
let PORTLAND_CEMENT_94LBS = 11.95
let QUICK_ROCK_50LBS = 34.25
//WHITE PRIVACY PRICES
let WHITE_PRIVACY_PANEL_4X6  = 51.48
let WHITE_PRIVACY_PANEL_4X8 = 74.95
let WHITE_PRIVACY_PANEL_5X6 = 51.48
let WHITE_PRIVACY_PANEL_5X8 = 74.95
let WHITE_PRIVACY_PANEL_6X6 = 60.48
let WHITE_PRIVACY_PANEL_6X8 = 86.73
let WHITE_PRIVACY_RAIL_GRN_1X5X6 = 6.89
let WHITE_PRIVACY_RAIL_GRN_1X5X8 = 9.19
let WHITE_PRIVACY_RAIL_STD_1X5X6 = 8.10
let WHITE_PRIVACY_RAIL_STD_1X5X8 = 10.8
let WHITE_PRIVACY_RAIL_STD_1X5X12 = 16.20
let WHITE_PRIVACY_T_G_11INX50IN = 5.83
let WHITE_PRIVACY_T_G_11INX61IN = 7.23
let WHITE_PRIVACY_T_G_11INX62IN = 7.23
let WHITE_PRIVACY_T_G_11INX16FT = 22.29
let WHITE_PRIVACY_T_G_6INX16FT = 11.48
let WHITE_PRIVACY_U_CHANNEL_6 = 1.96
let WHITE_PRIVACY_U_CHANNEL_16 = 5.22
let WHITE_VINYL_GATE_T_G_4X6 = 245
let WHITE_VINYL_GATE_T_G_5X6 = 290
let WHITE_METAL_GATE_T_G_4X6 = 300
let WHITE_METAL_GATE_T_G_6X6 = 340
let WHITE_METAL_GATE_T_G_5X6 = 340
let WHITE_POST_GREEN_5INX5INX5FT = 8.73
let WHITE_POST_GREEN_5INX5INX6FT = 10.48
let WHITE_POST_GREEN_5INX5INX7FT = 12.23
let WHITE_POST_GREEN_5INX5INX8FT = 13.97
let WHITE_POST_GREEN_5INX5INX9FT = 15.72
let WHITE_POST_GREEN_5INX5INX10FT = 17.47
let WHITE_POST_GREEN_LINE_5INX5INX8FT = 13.97
let WHITE_POST_ECONO_5INX5INX5FT = 10.73
let WHITE_POST_ECONO_5INX5INX6FT = 12.87
let WHITE_POST_ECONO_5INX5INX6_5FT = 13.94
let WHITE_POST_ECONO_5INX5INX7FT = 15.02
let WHITE_POST_ECONO_5INX5INX8FT = 17.16
let WHITE_POST_ECONO_5INX5INX9FT = 19.31
let WHITE_POST_ECONO_4INX4INX6FT = 13.17
let WHITE_POST_ECONO_4INX4INX8FT = 17.56
let WHITE_POST_PREMIUM_5INX5INX7FT = 17.64
let WHITE_POST_PREMIUM_5INX5INX8FT = 20.16
let WHITE_POST_PREMIUM_5INX5INX9FT = 22.68
let WHITE_POST_PREMIUM_5INX5INX10FT = 25.21
let WHITE_POST_PREMIUM_5INX5INX12FT = 30.25
let WHITE_POST_PREMIUM_5INX5INX16FT = 40.33
let WHITE_POST_PREMIUM_4INX4INX6FT = 16.61
let WHITE_POST_PREMIUM_4INX4INX8FT = 22.15
let WHITE_POST_PREMIUM_4INX4INX16FT = 44.30
let WHITE_POST_CAP_4INX4IN = 0.89
let WHITE_POST_CAP_5INX5IN = 0.89
/////////////////////////////////////
//TAN MATERIAL
let TAN_PRIVACY_PANEL_4X6  = 56.84
let TAN_PRIVACY_PANEL_4X8 = 82.05
let TAN_PRIVACY_PANEL_5X6 = 56.84
let TAN_PRIVACY_PANEL_5X8 = 82.05
let TAN_PRIVACY_PANEL_6X6 = 66.30
let TAN_PRIVACY_PANEL_6X8 = 94.43
let TAN_PRIVACY_RAIL_GRN_1X5X6 = 8.56
let TAN_PRIVACY_RAIL_GRN_1X5X8 = 11.41
let TAN_PRIVACY_RAIL_STD_1X5X6 = 9.64
let TAN_PRIVACY_RAIL_STD_1X5X8 = 12.85
let TAN_PRIVACY_RAIL_STD_1X5X12 = 19.28
let TAN_PRIVACY_T_G_11INX50IN = 6.09
let TAN_PRIVACY_T_G_11INX61IN = 7.55
let TAN_PRIVACY_T_G_11INX62IN = 7.55
let TAN_PRIVACY_T_G_11INX16FT = 23.28
let TAN_PRIVACY_T_G_6INX16FT = 12.11
let TAN_PRIVACY_U_CHANNEL_6 = 2.1
let TAN_PRIVACY_U_CHANNEL_16 = 5.6
let TAN_VINYL_GATE_T_G_4X6 = 265
let TAN_VINYL_GATE_T_G_5X6 = 310
let TAN_METAL_GATE_T_G_4X6 = 345
let TAN_METAL_GATE_T_G_6X6 = 385
let TAN_METAL_GATE_T_G_5X6 = 385
let TAN_POST_GREEN_5INX5INX7FT = 12.89
let TAN_POST_GREEN_5INX5INX8FT = 14.73
let TAN_POST_GREEN_LINE_5INX5INX8FT = 14.73
let TAN_POST_ECONO_5INX5INX6FT = 13.6
let TAN_POST_ECONO_5INX5INX6_5FT = 14.73
let TAN_POST_ECONO_5INX5INX7FT = 15.87
let TAN_POST_ECONO_5INX5INX8FT = 18.13
let TAN_POST_PREMIUM_5INX5INX7FT = 18.57
let TAN_POST_PREMIUM_5INX5INX8FT = 21.23
let TAN_POST_PREMIUM_5INX5INX9FT = 23.88
let TAN_POST_PREMIUM_5INX5INX12FT = 31.84
let TAN_POST_PREMIUM_5INX5INX16FT = 42.45
let TAN_POST_PREMIUM_4INX4INX6FT = 17.52
let TAN_POST_PREMIUM_4INX4INX16FT = 46.72
let TAN_POST_PREMIUM_4INX4INX24FT = 70.08
let TAN_POST_CAP_4INX4IN = 0.99
let TAN_POST_CAP_5INX5IN = 0.99
///////////////////////////////////////////////////////
//CLAY AND STONE PRICES
let CLAY_OR_STONE_PRIVACY_PANEL_4X6  = 66.4
let CLAY_OR_STONE_PRIVACY_PANEL_4X8 = 94.57
let CLAY_OR_STONE_PRIVACY_PANEL_5X6 = 66.40
let CLAY_OR_STONE_PRIVACY_PANEL_5X8 = 94.57
let CLAY_OR_STONE_PRIVACY_PANEL_6X6 = 81.06
let CLAY_OR_STONE_PRIVACY_PANEL_6X8 = 105.69
let CLAY_OR_STONE_PRIVACY_RAIL_STD_1X5X6 = 9.34
let CLAY_OR_STONE_PRIVACY_RAIL_STD_1X5X8 = 12.46
let CLAY_OR_STONE_PRIVACY_RAIL_STD_1X5X12 = 18.69
let CLAY_OR_STONE_PRIVACY_T_G_11INX50IN = 6.9
let CLAY_OR_STONE_PRIVACY_T_G_11INX61IN = 8.55
let CLAY_OR_STONE_PRIVACY_T_G_11INX62IN = 8.55
let CLAY_OR_STONE_PRIVACY_T_G_11INX16FT = 26.38
let CLAY_OR_STONE_PRIVACY_T_G_6INX16FT = 14.72
let CLAY_OR_STONE_PRIVACY_U_CHANNEL_6FT = 2.56
let CLAY_OR_STONE_PRIVACY_U_CHANNEL_16FT = 6.83
let CLAY_OR_STONE_VINYL_GATE_T_G_4X6 = 275
let CLAY_OR_STONE_VINYL_GATE_T_G_5X6 = 330
let CLAY_OR_STONE_METAL_GATE_T_G_4X6 = 350
let CLAY_OR_STONE_METAL_GATE_T_G_6X6 = 400
let CLAY_OR_STONE_METAL_GATE_T_G_5X6 = 400
let CLAY_OR_STONE_POST_ECONO_5INX5INX6_5FT = 16.47
let CLAY_OR_STONE_POST_ECONO_5INX5INX8FT = 20.27
let CLAY_OR_STONE_POST_PREMIUM_5INX5INX8FT = 23.79
let CLAY_OR_STONE_POST_PREMIUM_5INX5INX9FT = 26.76
let CLAY_OR_STONE_POST_PREMIUM_5INX5INX24FT = 71.36
let CLAY_OR_STONE_POST_PREMIUM_4INX4INX6FT = 19.6
let CLAY_OR_STONE_POST_PREMIUM_4INX4INX16FT = 52.27
let CLAY_OR_STONE_POST_PREMIUM_4INX4INX24FT = 78.4
let CLAY_OR_STONE_POST_CAP_4INX4IN = 1.1
let CLAY_OR_STONE_POST_CAP_5INX5IN = 1.1
////////////////////////////////////////////////////////////
//RANCH RAIL
let RANCHRAIL_GREEN_1INX5INX16FT = 11.54
let RANCHRAIL_ECONO_1INX5INX16FT = 16.57
let RANCHRAIL_PREMIUM_1INX5INX16FT = 21.12
let RANCHRAIL_GATE_VINYL_4FT = 160
let RANCHRAIL_GATE_VINYL_6FT = 175
let RANCHRAIL_GATE_METAL_4FT = 250
let RANCHRAIL_GATE_METAL_8FT = 275
let RANCHRAIL_POST_GREEN_WHITE_5INX5INX5FT = 8.73
let RANCHRAIL_POST_GREEN_WHITE_5INX5INX6_5FT = 9.48
let RANCHRAIL_POST_GREEN_WHITE_LINE_5INX5INX6_5FT = 9.48
let RANCHRAIL_POST_GREEN_WHITE_5INX5INX7FT = 12.22
let RANCHRAIL_POST_ECONO_WHITE_5INX5INX5FT = 10.73
let RANCHRAIL_POST_ECONO_WHITE_5INX5INX6_5FT = 13.94
let RANCHRAIL_POST_ECONO_WHITE_5INX5INX7FT = 15.02
let RANCHRAIL_POST_PREMIUM_WHITE_5INX5INX6_5FT = 16.38
let RANCHRAIL_POST_PREMIUM_WHITE_5INX5INX7FT = 17.74
let RANCHRAIL_POST_PREMIUM_WHITE_5INX5INX10FT = 25.21
let RANCHRAIL_POST_PREMIUM_WHITE_4INX4INX6FT = 16.61
let RANCHRAIL_POST_PREMIUM_WHITE_4INX4INX16FT = 44.30
let RANCHRAIL_POST_PREMIUM_WHITE_4INX4INX24FT = 66.44
let RANCHRAIL_POST_CAP_5INX5IN = 0.89
let RANCHRAIL_POST_CAP_4INX4IN = 0.89


class Gate : SaleItemLineDetail{
    var Id: String?
    var type,Location: String
    var length, heighth:Double
    init(loc:String, len:Double, hei:Double, t:String, q:Double){
        length = len
        heighth = hei
        type = t
        Location = loc
        super.init(q: 1, up: 0.0)
        calcCost()
    }
    required init(dict: [String : Any]) {
        type = ""
        length = 0.0
        heighth = 0.0
        Location = ""
        super.init(dict: dict)
    }
    required init(from decoder: Decoder) throws {
        fatalError("init(from:) has not been implemented")
    }
    func calcCost(){
        //calc cost of gate here
    }
}


class FenceLine : SaleItemLineDetail {
    var Id: String?
    var numPosts, secLength, numCaps, numSections, numUChannel, numScrews, numRails, numPanels, length, postWidth, heighth:Double
    var type,Location:String
    var bti,eti:Bool
    let sec_length = 8.0
    let panel_width = 18.0
    init(l: Double, t:String, pw:Double, h:Double,bti:Bool,eti:Bool, loc:String) {
        type = t
        length = l
        numPosts = 0.0
        numSections = 0.0
        numUChannel = 0.0
        numScrews = 0.0
        numRails = 0.0
        numPanels = 0.0
        postWidth = pw
        heighth = h    
        numCaps = 0.0 
        secLength = 0.0
        self.bti = bti
        self.eti = eti
        Location = loc
        super.init(q: l, up: 0.0)
        calcNPo()
        calcNS()
        calcSL()
        calcNR()
        calcNPa()
        calcNUC()
        calcNSCR()
        calcCost()
    }
    required init(dict: [String : Any]) {
        type =  ""
        length = 0.0
        numPosts = 0.0
        numSections = 0.0
        numUChannel = 0.0
        numScrews = 0.0
        numRails = 0.0
        numPanels = 0.0
        postWidth = 0.0
        heighth = 0.0
        numCaps = 0.0
        secLength = 0.0
        self.bti = false
        self.eti = false
        Location = ""
        super.init(dict: dict)
    }
    
    required init(from decoder: Decoder) throws {
        fatalError("init(from:) has not been implemented")
    }
    func calcNPo(){
        numPosts = ceil((length/sec_length)+1)
        if(bti){
            numPosts -= 1.0
        }
        if(eti){
            numPosts -= 1.0
        }
        numCaps = numPosts
    }
    func calcSL(){
        secLength = length / numSections
    }
    func calcNS(){
        numSections = ceil(length/sec_length)
    }
    func calcNSCR(){
        numScrews = numUChannel * 2
    }
    func calcNR(){
        numRails = numSections * 2
    }
    func calcNPa(){
        var inches = length * 12
        inches = inches - (postWidth * numPosts)
        numPanels = ceil(inches/panel_width)
    }
    func calcNUC(){
        numUChannel = numSections * 2
    }
    func calcCost(){
        //calc the unit price right here for the line
    }
}

class FenceCompany {
    var be:Backend!
    init(b:Backend){
        be = b
    }
}

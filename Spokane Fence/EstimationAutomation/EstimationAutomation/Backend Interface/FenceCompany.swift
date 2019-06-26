//
//  FenceCompany.swift
//  EstimateAutomation
//
//  Created by codeslinger on 5/16/19.
//  Copyright © 2019 SpokaneAutomationCompany. All rights reserved.
//

import Foundation

let taxationRate = 0.086

protocol FenceComponent {
    var cost:Double { get set }
    var qty:Double {get set }
    func calcCost() -> Double
}

protocol FenceDecorator : FenceComponent {
    var component:FenceComponent { get set }
}

protocol Fence : SaleItemLineDetail {
    var comp:FenceComponent { get set }
    var cost:Double { get set}
    var numConc:Double { get set}
    var numPosts:Double { get set}
    var secLength:Double { get set}
    var numCaps:Double { get set}
    var numSections:Double { get set}
    var numUChannel:Double { get set}
    var numScrews:Double { get set}
    var numRails:Double { get set}
    var numPanels:Double { get set}
    var length:Double { get set }
    var Location:String {get set}
    var eti:Bool { get set }
    var bti:Bool { get set }
    func calcNPo()
    func calcSL()
    func calcNS()
    func calcNSCR()
    func calcNR()
    func calcNPa()
    func calcNUC()
    func calcNConc()
}
class FenceLine : SaleItemLineDetail, Fence {
    var Location: String
    var comp: FenceComponent
    var cost: Double
    var numConc: Double
    var numPosts: Double
    var secLength: Double
    var numCaps: Double
    var numSections: Double
    var numUChannel: Double
    var numScrews: Double
    var numRails: Double
    var numPanels: Double
    var length: Double
    var sec_length = 8.0
    var panel_width = 11.0
    var postWidth = 5.0 //inches
    var heighth = 6.0
    var eti: Bool
    var bti: Bool
    init(l: Double, bti:Bool,eti:Bool, loc:String) {
        length = l
        self.bti = bti
        self.eti = eti
        numPosts = 0.0
        numSections = 0.0
        numUChannel = 0.0
        numScrews = 0.0
        numRails = 0.0
        numPanels = 0.0
        numCaps = 0.0
        secLength = 0.0
        cost = 0.0
        comp = Base.init()
        numConc = 0.0
        Location = loc
        super.init(q: l, up: 0.0)
        calcNPo()
        calcNS()
        calcSL()
        calcNR()
        calcNPa()
        calcNUC()
        calcNSCR()
        calcNConc()
        calcCost()
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
        numPanels = ceil(numPanels * 1.1) //account for 10% loss
    }
    func calcNUC(){
        numUChannel = ceil((numSections * 2) * 1.1) //account for 10% loss while on the job
    }
    func calcNConc(){
        numConc = ceil(numPosts * 1.5)
    }
    func postWrapper( c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = WHITE_POST_ECONO_4INX4INX8FT(comp: fc, qty: numPosts)
        return fc
    }
    func panelWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = WHITE_PRIVACY_T_G_11INX62IN(comp: fc, qty: numPanels)
        return fc
    }
    func railWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        if secLength < 6 {
            fc = WHITE_PRIVACY_RAIL_STD_1X5X6(comp: fc, qty: numRails)
        }
        else {
            fc = WHITE_PRIVACY_RAIL_STD_1X5X8(comp: fc, qty: numRails)
        }
        return fc
    }
    func uchannelWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = WHITE_PRIVACY_U_CHANNEL_6(comp: fc, qty: numUChannel)
        return fc
    }
    func screwWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = EVERBILT_HEX_1_5(comp: fc, qty: numScrews)
        return fc
    }
    func concWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = CONCRETE_PRE_MIX_80LBS(comp: fc, qty: numConc)
        return fc
    }
    func capWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = WHITE_POST_CAP_5INX5IN(comp: fc, qty: numCaps)
        return fc
    }
    func calcCost() {
        //concrete
        comp = concWrapper(c: comp)
        //screws
        comp = screwWrapper(c: comp)
        //u channel
        comp = uchannelWrapper(c: comp)
        //rails
        comp = railWrapper(c: comp)
        //panels
        comp = panelWrapper(c: comp)
        //posts
        comp = postWrapper(c: comp)
        comp = capWrapper(c: comp)
        UnitPrice = (comp.calcCost() / length)
    }
}

class Base: FenceComponent {
    var qty: Double = 1
    var cost: Double = 0.0 // this changes the base price before material
    func calcCost() -> Double {
        return cost
    }
}

class Gate : SaleItemLineDetail{
    var comp:FenceComponent
    var cost: Double
    var Id: String?
    var Location: String
    var length:Double
    init(loc:String, len:Double, q:Double){
        length = len
        Location = loc
        cost = 0.0
        self.comp = Base.init()
        super.init(q: 1, up: 0.0)
        calcCost()
    }
    required init(from decoder: Decoder) throws {
        fatalError("init(from:) has not been implemented")
    }
    func calcCost(){
        //calc cost of gate here
        comp = WHITE_VINYL_GATE_T_G_4X6(comp: comp,qty: 1)
        comp = INSERT_TWO_SIDED_4INX8FT(comp: comp,qty: 1)
        UnitPrice = comp.calcCost()
    }
}

class GATE_WHITE_4_6 : Gate {
    override init(loc: String, len: Double, q: Double) {
        super.init(loc: loc, len: len, q: q)
    }
    required init(from decoder: Decoder) throws {
        fatalError("init(from:) has not been implemented")
    }

}
class GATE_WHITE_5_6 : Gate {
    override init(loc: String, len: Double, q: Double) {
        super.init(loc: loc, len: len, q: q)
    }
    required init(from decoder: Decoder) throws {
        fatalError("init(from:) has not been implemented")
    }
    override func calcCost() {
        comp = WHITE_VINYL_GATE_T_G_5X6(comp: comp,qty: 1)
        comp = INSERT_TWO_SIDED_4INX8FT(comp: comp,qty: 1)
        UnitPrice = comp.calcCost()
    }
}

class WHITE_GREENPOST_6_FenceLine : FenceLine {
    override init(l: Double, bti:Bool,eti:Bool, loc:String) {
        super.init(l: l, bti: bti, eti: eti, loc: loc)
    }
    required init(from decoder: Decoder) throws {
        fatalError("init(from:) has not been implemented")
    }
    override func postWrapper( c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = WHITE_POST_GREEN_5INX5INX8FT(comp: fc, qty: numPosts)
        return fc
    }
}

class WHITE_ECONOPOST_6_FenceLine : FenceLine {
    override init(l: Double, bti:Bool,eti:Bool, loc:String) {
        super.init(l: l, bti: bti, eti: eti, loc: loc)
    }
    required init(from decoder: Decoder) throws {
        fatalError("init(from:) has not been implemented")
    }
    override func postWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = WHITE_POST_ECONO_5INX5INX8FT(comp: fc, qty: numPosts)
        return fc
    }
}

class WHITE_PREMPOST_6_FenceLine : FenceLine {
    override init(l: Double, bti:Bool,eti:Bool, loc:String) {
        super.init(l: l, bti: bti, eti: eti, loc: loc)
    }
    required init(from decoder: Decoder) throws {
        fatalError("init(from:) has not been implemented")
    }
    override func postWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = WHITE_POST_PREMIUM_5INX5INX8FT(comp: fc, qty: numPosts)
        return fc
    }
}

class TAN_GREENPOST_6_Fenceline : FenceLine {
    override init(l: Double, bti:Bool,eti:Bool, loc:String) {
        super.init(l: l, bti: bti, eti: eti, loc: loc)
    }
    required init(from decoder: Decoder) throws {
        fatalError("init(from:) has not been implemented")
    }
    override func postWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_POST_GREEN_5INX5INX8FT(comp: fc, qty: numPosts)
        return fc
    }
    override func capWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_POST_CAP_5INX5IN(comp: fc, qty: numCaps)
        return fc
    }
    override func panelWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_PRIVACY_T_G_11INX62IN(comp: fc, qty: numPanels)
        return fc
    }
    override func railWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_PRIVACY_RAIL_STD_1X5X8(comp: fc, qty: numRails)
        return fc
    }
    override func uchannelWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_PRIVACY_U_CHANNEL_6(comp: fc, qty: numUChannel)
        return fc
    }
}
class TAN_ECONOPOST_6_Fenceline : FenceLine {
    override init(l: Double, bti:Bool,eti:Bool, loc:String) {
        super.init(l: l, bti: bti, eti: eti, loc: loc)
    }
    required init(from decoder: Decoder) throws {
        fatalError("init(from:) has not been implemented")
    }
    override func postWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_POST_ECONO_5INX5INX8FT(comp: fc, qty: numPosts)
        return fc
    }
    override func capWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_POST_CAP_5INX5IN(comp: fc, qty: numCaps)
        return fc
    }
    override func panelWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_PRIVACY_T_G_11INX62IN(comp: fc, qty: numPanels)
        return fc
    }
    override func railWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_PRIVACY_RAIL_STD_1X5X8(comp: fc, qty: numRails)
        return fc
    }
    override func uchannelWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_PRIVACY_U_CHANNEL_6(comp: fc, qty: numUChannel)
        return fc
    }
}
class TAN_PREMPOST_6_Fenceline : FenceLine {
    override init(l: Double, bti:Bool,eti:Bool, loc:String) {
        super.init(l: l, bti: bti, eti: eti, loc: loc)
    }
    required init(from decoder: Decoder) throws {
        fatalError("init(from:) has not been implemented")
    }
    override func postWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_POST_PREMIUM_5INX5INX8FT(comp: fc, qty: numPosts)
        return fc
    }
    override func capWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_POST_CAP_5INX5IN(comp: fc, qty: numCaps)
        return fc
    }
    override func panelWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_PRIVACY_T_G_11INX62IN(comp: fc, qty: numPanels)
        return fc
    }
    override func railWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_PRIVACY_RAIL_STD_1X5X8(comp: fc, qty: numRails)
        return fc
    }
    override func uchannelWrapper(c: FenceComponent) -> FenceComponent {
        var fc = c
        fc = TAN_PRIVACY_U_CHANNEL_6(comp: fc, qty: numUChannel)
        return fc
    }
}









///FENCE COMPONENTS ********************************************************************************************************************

class EVERBILT_HEX_1_5 : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 0.1588
    var qty: Double
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class U_CHANNEL_STEEL_1X5X8 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 7.25
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class INSERT_TWO_SIDED_4INX8FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 28.5
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class INSERT_Z_LINE_5INX8FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 25
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class INSERT_TWO_SIDED_5INX8F : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 39.04
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class INSERT_GATE_ALUM_5INX8FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 75
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class CONCRETE_PRE_MIX_80LBS : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 4.25
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class PORTLAND_CEMENT_94LBS : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 11.95
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class QUICK_ROCK_50LBS : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 34.25
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
//WHITE PRIVACY PRICES
class WHITE_PRIVACY_PANEL_4X6 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 51.48
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_PANEL_4X8 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 74.95
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_PANEL_5X6 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 51.48
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_PANEL_5X8 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 74.95
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_PANEL_6X6 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 60.48
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_PANEL_6X8 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 86.73
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_RAIL_GRN_1X5X6 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 6.89
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_RAIL_GRN_1X5X8 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 9.19
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_RAIL_STD_1X5X6 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 8.1
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_RAIL_STD_1X5X8 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 10.8
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_RAIL_STD_1X5X12 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 16.2
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_T_G_11INX50IN : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 5.83
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_T_G_11INX61IN : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 7.23
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_T_G_11INX62IN : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 7.23
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_T_G_11INX16FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 22.29
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_T_G_6INX16FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 11.48
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_U_CHANNEL_6 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 1.96
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_PRIVACY_U_CHANNEL_16 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 5.22
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_VINYL_GATE_T_G_4X6  : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 245
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_VINYL_GATE_T_G_5X6 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 290
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_METAL_GATE_T_G_4X6 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 300
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_METAL_GATE_T_G_6X6 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 340
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_METAL_GATE_T_G_5X6  : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 340
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_GREEN_5INX5INX5FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 8.73
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_GREEN_5INX5INX6FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 10.48
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_GREEN_5INX5INX7FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 12.23
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_GREEN_5INX5INX8FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 13.97
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_GREEN_5INX5INX9FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 15.72
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_GREEN_5INX5INX10FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 17.47
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_GREEN_LINE_5INX5INX8FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 13.97
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_ECONO_5INX5INX5FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 10.73
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_ECONO_5INX5INX6FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 12.87
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_ECONO_5INX5INX6_5FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 13.94
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_ECONO_5INX5INX7FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 15.02
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_ECONO_5INX5INX8FT: FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 17.16
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_ECONO_5INX5INX9FT  : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 19.31
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_ECONO_4INX4INX6FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 13.17
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_ECONO_4INX4INX8FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 17.56
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_PREMIUM_5INX5INX7FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 17.64
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_PREMIUM_5INX5INX8FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 20.16
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_PREMIUM_5INX5INX9FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 22.68
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_PREMIUM_5INX5INX10FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 25.21
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_PREMIUM_5INX5INX12FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 30.25
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_PREMIUM_5INX5INX16FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 40.33
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_PREMIUM_4INX4INX6FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 16.61
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_PREMIUM_4INX4INX8FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 22.15
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_PREMIUM_4INX4INX16FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 44.3
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_CAP_4INX4IN : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 0.89
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
class WHITE_POST_CAP_5INX5IN : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 0.89
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
/*
/////////////////////////////////////
//TAN MATERIAL
let TAN_PRIVACY_PANEL_4X6  = 56.84
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_PRIVACY_PANEL_4X8 = 82.05
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_PRIVACY_PANEL_5X6 = 56.84
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_PRIVACY_PANEL_5X8 = 82.05
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_PRIVACY_PANEL_6X6 = 66.30
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_PRIVACY_PANEL_6X8 = 94.43
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_PRIVACY_RAIL_GRN_1X5X6 = 8.56
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_PRIVACY_RAIL_GRN_1X5X8 = 11.41
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_PRIVACY_RAIL_STD_1X5X6 = 9.64
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
 */
class TAN_PRIVACY_RAIL_STD_1X5X8 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 12.85
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
/*
let TAN_PRIVACY_RAIL_STD_1X5X12 = 19.28
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_PRIVACY_T_G_11INX50IN = 6.09
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_PRIVACY_T_G_11INX61IN = 7.55
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
 */
class TAN_PRIVACY_T_G_11INX62IN : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 7.55
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
/*
let TAN_PRIVACY_T_G_11INX16FT = 23.28
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_PRIVACY_T_G_6INX16FT = 12.11
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
 */
class TAN_PRIVACY_U_CHANNEL_6 : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 2.1
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
/*
let TAN_PRIVACY_U_CHANNEL_16 = 5.6
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_VINYL_GATE_T_G_4X6 = 265
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_VINYL_GATE_T_G_5X6 = 310
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_METAL_GATE_T_G_4X6 = 345
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_METAL_GATE_T_G_6X6 = 385
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_METAL_GATE_T_G_5X6 = 385
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_POST_GREEN_5INX5INX7FT = 12.89
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
*/

class TAN_POST_GREEN_5INX5INX8FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 14.73
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}

/*
let TAN_POST_GREEN_LINE_5INX5INX8FT = 14.73
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_POST_ECONO_5INX5INX6FT = 13.6
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_POST_ECONO_5INX5INX6_5FT = 14.73
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_POST_ECONO_5INX5INX7FT = 15.87
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
*/
class TAN_POST_ECONO_5INX5INX8FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 18.13
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
/*
let TAN_POST_PREMIUM_5INX5INX7FT = 18.57
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
*/
class TAN_POST_PREMIUM_5INX5INX8FT : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 21.23
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
/*
let TAN_POST_PREMIUM_5INX5INX9FT = 23.88
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_POST_PREMIUM_5INX5INX12FT = 31.84
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_POST_PREMIUM_5INX5INX16FT = 42.45
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_POST_PREMIUM_4INX4INX6FT = 17.52
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_POST_PREMIUM_4INX4INX16FT = 46.72
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_POST_PREMIUM_4INX4INX24FT = 70.08
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let TAN_POST_CAP_4INX4IN = 0.99
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
*/
class TAN_POST_CAP_5INX5IN : FenceDecorator {
    var qty: Double
    var component: FenceComponent
    var cost: Double = 0.99
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
/*
///////////////////////////////////////////////////////
//CLAY AND STONE PRICES
let CLAY_OR_STONE_PRIVACY_PANEL_4X6  = 66.4
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_PANEL_4X8 = 94.57
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_PANEL_5X6 = 66.40
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_PANEL_5X8 = 94.57
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_PANEL_6X6 = 81.06
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_PANEL_6X8 = 105.69
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_RAIL_STD_1X5X6 = 9.34
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_RAIL_STD_1X5X8 = 12.46
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_RAIL_STD_1X5X12 = 18.69
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_T_G_11INX50IN = 6.9
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_T_G_11INX61IN = 8.55
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_T_G_11INX62IN = 8.55
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_T_G_11INX16FT = 26.38
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_T_G_6INX16FT = 14.72
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_U_CHANNEL_6FT = 2.56
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_PRIVACY_U_CHANNEL_16FT = 6.83
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_VINYL_GATE_T_G_4X6 = 275
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_VINYL_GATE_T_G_5X6 = 330
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_METAL_GATE_T_G_4X6 = 350
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_METAL_GATE_T_G_6X6 = 400
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_METAL_GATE_T_G_5X6 = 400
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_POST_ECONO_5INX5INX6_5FT = 16.47
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_POST_ECONO_5INX5INX8FT = 20.27
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_POST_PREMIUM_5INX5INX8FT = 23.79
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_POST_PREMIUM_5INX5INX9FT = 26.76
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_POST_PREMIUM_5INX5INX24FT = 71.36
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_POST_PREMIUM_4INX4INX6FT = 19.6
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_POST_PREMIUM_4INX4INX16FT = 52.27
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_POST_PREMIUM_4INX4INX24FT = 78.4
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_POST_CAP_4INX4IN = 1.1
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let CLAY_OR_STONE_POST_CAP_5INX5IN = 1.1
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
////////////////////////////////////////////////////////////
//RANCH RAIL
let RANCHRAIL_GREEN_1INX5INX16FT = 11.54
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_ECONO_1INX5INX16FT = 16.57
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_PREMIUM_1INX5INX16FT = 21.12
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_GATE_VINYL_4FT = 160
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_GATE_VINYL_6FT = 175
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_GATE_METAL_4FT = 250
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_GATE_METAL_8FT = 275
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_GREEN_WHITE_5INX5INX5FT = 8.73
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_GREEN_WHITE_5INX5INX6_5FT = 9.48
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_GREEN_WHITE_LINE_5INX5INX6_5FT = 9.48
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_GREEN_WHITE_5INX5INX7FT = 12.22
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_ECONO_WHITE_5INX5INX5FT = 10.73
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_ECONO_WHITE_5INX5INX6_5FT = 13.94
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_ECONO_WHITE_5INX5INX7FT = 15.02
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_PREMIUM_WHITE_5INX5INX6_5FT = 16.38
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_PREMIUM_WHITE_5INX5INX7FT = 17.74
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_PREMIUM_WHITE_5INX5INX10FT = 25.21
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_PREMIUM_WHITE_4INX4INX6FT = 16.61
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_PREMIUM_WHITE_4INX4INX16FT = 44.30
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_PREMIUM_WHITE_4INX4INX24FT = 66.44
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_CAP_5INX5IN = 0.89
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}
let RANCHRAIL_POST_CAP_4INX4IN = 0.89
class INSERT_THREE_SIDED_5INX8FT : FenceDecorator {
    var component: FenceComponent
    var cost: Double = 50
    init(comp: FenceComponent, qty: Double) {
        self.component = comp
        self.qty = qty
    }
    func calcCost() -> Double {
        return component.calcCost() + (cost * qty)
    }
}*/
class FenceCompany {
    var be:Backend!
    init(b:Backend){
        be = b
    }
}

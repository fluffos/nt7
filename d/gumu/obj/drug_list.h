// drug_list.h
// by Blacko /2001/8
// update april 2001.11.09

mapping *drug_list = ({
        ([
                "name": "金蜜散",  //木香,山菊,蝉蜕,牛黄
                "level": 60,
                "file": "jinmisan",
                "time": 10,
                "s": 5,
                "d": 35,
                "n": 2,
        ]),
        ([
                "name": "玉蜂针毒",  //柴胡,葵花粉,玉蜂毒
                "level": 90,
                "file": "yufeng-zhen",
                "time": 20,
                "s": 2,
                "d": -39,
                "n": -39,
        ]),
        ([
                "name": "古墓玉浆",  //升麻,土茯苓,何首乌,雪莲子,玉蜂王浆
                "level": 120,
                "file": "yujiang",
                "time": 30,
                "s": 201,
                "d": 121,
                "n": 72,
        ]),
        ([
                "name": "古墓圣浆", //木香,土茯苓,人参,鲨胆,黄连,古墓玉浆
                "level": 150,
                "file": "shengyao",
                "time": 40,
                "s": 221,
                "d": 184,
                "n": 21,
        ])
});
/*
古墓圣药列表
60         金蜜散        =        山菊 + 木香 + 蝉蜕 + 牛黄
90        玉蜂针        =        柴胡 + 葵花粉 + 玉蜂毒 + 金针
120        古墓玉浆=        升麻 + 土茯苓 + 何首乌 + 雪莲子 + 玉蜂王浆
150        古墓圣药=        木香 + 土茯苓 + 人参 + 鲨胆 + 黄连 + 古墓玉浆

古墓药材列表
*木香，*柴胡，*升麻，*山菊，*土茯苓
*蝉蜕，*何首乌，*黄连/雄黄，*牛黄，*鲨胆，*人参，*雪莲子，*葵花粉

土茯苓        30        20        40        tufuling
升麻        1        1        2        shengma
山菊        1        3        1        shanju
柴胡        2        1        1        chaihu
木香        1        2        1        muxiang
name        cure_s        cure_d        cure_n        herb
巴豆        -1        2        0        badou
葵花粉        0        -40        40        kuihua
防风        0        0        5        fangfeng
生地        0        0        15        shengdi
穿山甲        0        0        30        chuanshanjia
金银花        0        1        0        jy-hua
荷叶        0        3        0        heye
菊梗        0        5        0        jugeng
黄连        0        20        0        huanglian
雄黄        0        20        0        xionghuang
牛黄        0        30        0        niuhuang
鲨胆        0        52        10        shadan
蝉蜕        3        0        0        chantui
枸枳子        5        0        0        gouzhizi
田七        5        30        0        tianqi
川贝        10        0        0        chuanbei
雪莲子        20        30        40        xuelianzi
藏红花        30        0        0        zanghonghua
熊胆        30        0        45        xiongdan
豹胎        30        0        72        baotai
茯苓        40        0        53        fuling
何首乌        80        0        10        heshouwu
人参        100        0        0        renshen
*/
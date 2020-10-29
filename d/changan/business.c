// Room: /d/changan/business.c

inherit WAREHOUSE;

void create()
{
        set("short", "长安城商栈");
        set("long", @LONG
这里就是著名的京城商栈，京城买卖商品的集散地，也是富商大
贾云集之所，由京城商会控制。在京城大宗商品的买卖都要通过这里
进行。门口挂着一块木牌(sign)。
LONG );

        set("item_desc",([
        "sign" : "
list                    查看当地各种商品的价格。
shou <数量> 商品        收购一定数量的商品。
pao <数量> 商品         在本地抛售一定数量的商品。
fasong                  将你在本地的货物发往其它的地点。
\n",
]));

        set("exits",([
        "south" : __DIR__"majiu",
]));


        // 初始货物数量
        set("all_wares",([
        "rice" :   187500,     //1
        "wheat" :  187500,    //2
        "corn" :   187500,     //3
        "ganzhe" : 187500,   //4
        "goober" : 187500,   //5
        "silk" :    37500,     //6
        "cloth" :  187500,    //7
        "zxiu" :    37500,     //8
        "iron" :   187500,     //9
        "tong" :   187500,     //10
        "diamand" : 37500,  //11
        "suis" :   187500,     //12
        "gold" :    18750,      //13
        "silver" :  37500,   //14
        "picture" : 0,      //15  需要
        "jxiu" :    18750,      //16
        "book" :    18750,      //17
        "vase" :    18750,      //18
        "harm" :   187500,     //19
        "guiy" :    37500,     //20
        "meat" :   187500,     //21
        "fish" :   187500,     //22
        "orange" : 187500,   //23
        "tea" :    187500,      //24
        "yye" :    187500,      //25
        "shen" :    18750,      //26
        "deer" :    18750,      //27
        "sdan" :    18750,      //28
        "bamboo" : 300000,   //29
        "pei" :     18750,       //30
        "hairpin" : 18750,   //31
        "qilin" :  187500,    //32  本地
        "guan" :   187500,     //33  本地
        "ddai" :    18750,      //34
        "mxia" :    18750,      //35
        "jade" :    18750,      //36
        "pearl" :   18750,     //37
        "bonsai" :  18750,    //38
        "spear" :  187500,    //39
        "sword" :  187500,    //40
        "blade" :  187500,    //41
        "shield" : 300000,   //42
        "jian" :   300000,     //43
        "armor" :  187500,    //44
        "wood" :   187500,     //45
        "stone" :  300000,    //46
        "cansi" :       0,        //47  需要
        "cotton" : 300000,   //48
        "salt" :   300000,     //49 
        "paper" :   37500,    //50
]));

        // 各类商品的价格指数
        set("kind_rate",([
        "picture" : 122, //15  需要
        "qilin" : 77,    //32  本地
        "guan" : 78,     //33  本地
        "cansi" : 125,   //47  需要
]));
 
        set("coor/x", -10750);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
}
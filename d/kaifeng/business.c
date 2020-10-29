// Room: /d/kaifeng/business.c

inherit WAREHOUSE;

void create()
{
        set("short", "开封府商栈");
        set("long", @LONG
这里就是著名的开封商栈，开封买卖商品的集散地，也是富商大
贾云集之所，由开封商会控制。在开封大宗商品的买卖都要通过这里
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
        "rice" :   200000,     //1
        "wheat" :  200000,    //2
        "corn" :   369000,     //3   本地
        "ganzhe" : 200000,   //4
        "goober" : 200000,   //5
        "silk" :    41000,     //6
        "cloth" :  200000,    //7
        "zxiu" :    41000,     //8
        "iron" :   200000,     //9
        "tong" :   200000,     //10
        "diamand" : 41000,  //11
        "suis" :   200000,     //12
        "gold" :    20000,      //13
        "silver" :  41000,   //14
        "picture" : 20000,   //15  
        "jxiu" :    20000,      //16
        "book" :    20000,      //17
        "vase" :   200000,      //18  本地
        "harm" :   200000,     //19
        "guiy" :    41000,     //20
        "meat" :   200000,     //21
        "fish" :   200000,     //22
        "orange" : 200000,   //23
        "tea" :    200000,      //24
        "yye" :    200000,      //25
        "shen" :    20000,      //26
        "deer" :    20000,      //27
        "sdan" :    20000,      //28
        "bamboo" : 325000,   //29
        "pei" :     20000,       //30
        "hairpin" : 20000,   //31
        "qilin" :   20000,     //32  
        "guan" :    20000,      //33  
        "ddai" :    20000,      //34
        "mxia" :    20000,      //35
        "jade" :    20000,      //36
        "pearl" :   20000,     //37
        "bonsai" :   4100,    //38  需要
        "spear" :  200000,    //39
        "sword" :  200000,    //40
        "blade" :  200000,    //41
        "shield" : 320000,   //42
        "jian" :   320000,     //43
        "armor" :  200000,    //44
        "wood" :   200000,     //45
        "stone" :  330000,    //46
        "cansi" :   41000,    //47  
        "cotton" : 320000,   //48
        "salt" :        0,         //49  需要 
        "paper" :   41000,    //50
]));

        // 各类商品的价格指数
        set("kind_rate",([
        "corn" : 74,      // 3  本地
        "vase" : 76,      //18  本地
        "bonsai" : 125,   //38  需要
        "salt" : 125,     //49  需要
]));
 
	set("coor/x", -5030);
	set("coor/y", 2260);
	set("coor/z", 0);
	setup();
}
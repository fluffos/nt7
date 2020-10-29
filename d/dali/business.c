// Room: /d/tianshui/business.c

inherit WAREHOUSE;

void create()
{
        set("short", "大理城商栈");
        set("long", @LONG
这里就是著名的大理商栈，大理买卖商品的集散地，也是富商大
贾云集之所，由大理商会控制。在大理大宗商品的买卖都要通过这里
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
        "rice" :         0,     //1   需要
        "wheat" :   200000,    //2
        "corn" :    200000,     //3
        "ganzhe" :  200000,   //4
        "goober" :  200000,   //5
        "silk" :     40000,     //6
        "cloth" :        0,    //7   需要
        "zxiu" :     40000,     //8
        "iron" :    200000,     //9
        "tong" :    200000,     //10
        "diamand" :  40000,  //11
        "suis" :    200000,     //12
        "gold" :     20000,      //13
        "silver" :   40000,   //14
        "picture" :  20000,   //15  
        "jxiu" :     20000,     //16  本地
        "book" :     20000,      //17
        "vase" :     20000,      //18
        "harm" :    200000,     //19
        "guiy" :     40000,     //20
        "meat" :         0,         //21  需要
        "fish" :    200000,     //22
        "orange" :     400,     //23  需要
        "tea" :     200000,      //24
        "yye" :     200000,      //25
        "shen" :     20000,      //26
        "deer" :     20000,      //27
        "sdan" :     20000,      //28
        "bamboo" :  320000,   //29
        "pei" :      20000,       //30
        "hairpin" :  20000,   //31
        "qilin" :    20000,     //32  
        "guan" :     20000,      //33  
        "ddai" :     20000,      //34
        "mxia" :     20000,      //35
        "jade" :     20000,      //36
        "pearl" :    20000,     //37
        "bonsai" :       0,       //38  需要
        "spear" :   200000,    //39
        "sword" :   200000,    //40
        "blade" :   200000,    //41
        "shield" :  320000,   //42
        "jian" :    320000,     //43
        "armor" :   200000,    //44
        "wood" :    200000,     //45
        "stone" :   360000,    //46  本地
        "cansi" :    40000,    //47 
        "cotton" :       0,       //48  需要
        "salt" :    320000,     //49 
        "paper" :    40000,    //50
]));

        // 各类商品的价格指数
        set("kind_rate",([
        "rice" :  124,     //1   需要
        "cloth" : 124,     //7   需要
        "jxiu" :  90,      //16  本地
        "meat" : 126,      //21  需要
        "orange" : 125,    //23  需要
        "bonsai" : 125,    //38  需要
        "stone" : 76,      //46  本地
        "cotton" : 126,    //48  需要

]));
 
	set("coor/x", -19150);
	set("coor/y", -6900);
	set("coor/z", 0);
	setup();
}
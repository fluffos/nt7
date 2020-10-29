#include <room.h>
inherit TRANS_ROOM;

void create()
{
mapping map_short = ([
         "nanyang"     : "南阳",
         "wugong"      : "武功镇",
         "yangzhou"    : "扬州",
         "kaifeng"     : "开封",
         "changan"     : "长安",
         "beijing"     : "北京",
         "zhongzhou"   : "中州",
         "xiangyang"   : "襄阳",
]);

mapping trans_pay = ([
         "nanyang"     : 120,
         "wugong"      : 80,
         "yangzhou"    : 160,
         "kaifeng"     : 140,
         "changan"     : 100,
         "beijing"     : 160,
         "zhongzhou"   : 120,
         "xiangyang"   : 100,
]);

        set("short","马厩");
        set("long",@LONG
这是客店后的马厩，常年供应新鲜草料。洛阳乃天下古城
历史悠久、民风淳朴，马夫们会把马牵到马厩好生照看，将它
们喂饱饮足，再洗刷得干乾净净。马厩雨檐下的烂木柱上钉着
块破木牌 (paizi)。马厩中堆放著几堆草料。
LONG);
        set("outdoors", "luoyang");
        set("no_fight", 1);
        set("objects", ([
              "/clone/horse/zaohongma": 1,
              "/clone/horse/huangbiaoma": 1,
              "/clone/horse/ziliuma": 1,
              "/clone/npc/mafu": 1,
        ]));
        set("exits",([
                "west" : __DIR__"kezhan",
                "up"   : "/clone/shop/luoyang_shop",
        ]));
        set("trans", map_short);
        set("trans_money", trans_pay);

	set("coor/x", -6970);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(TRANS_ROOM);
}
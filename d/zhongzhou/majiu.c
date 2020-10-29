#include <room.h>
inherit TRANS_ROOM;

void create()
{
mapping map_short = ([
         "nanyang"       : "南阳",
         "suzhou"        : "苏州",
         "luoyang"       : "洛阳",
         "beijing"       : "北京",
         "xiangyang"     : "襄阳",
         "kaifeng"       : "开封",
         "changan"       : "长安",
         "yangzhou"      : "扬州",
]);

mapping trans_pay = ([
         "nanyang"       : 120,
         "suzhou"        : 80,
         "luoyang"       : 120,
         "beijing"       : 150,
         "xiangyang"     : 80,
         "kaifeng"       : 100,
         "changan"       : 100,
         "yangzhou"      : 80,
]);

      set("short", "马厩");
      set("long", @LONG
这里是中州城英豪酒楼后的马厩，常年供应新鲜草料。中
州城自古乃军事要地，民风淳朴，马夫们会把马牵到马厩好生
照看，将它们喂饱饮足，再洗刷得干乾净净，一直伺候到客人
上路。马厩雨檐下的烂木柱上钉着一块破木牌 (paizi)。马厩
中堆放著几堆草料，正中有一口泔槽。
LONG);
      set("outdoors", "zhongzhou");
      set("no_fight", 1);
      set("objects", ([
              "/clone/horse/zaohongma": 1,
              "/clone/horse/huangbiaoma": 1,
              "/clone/horse/ziliuma": 1,
              "/clone/npc/mafu": 1,
      ]));
      set("exits",([
              "west" : __DIR__"yinghao",
              "up"   : "/clone/shop/zhongzhou_shop",
      ]));
        set("trans", map_short);
        set("trans_money", trans_pay);
        set("coor/x", -9020);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
      replace_program(TRANS_ROOM);
}
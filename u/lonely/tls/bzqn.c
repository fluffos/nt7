#include <ansi.h>
inherit ROOM;

void create()
{
  set("short","百丈桥");
  set("long",@LONG
一条深沟横在面前，挡住了你的去路，沟上有一座长长的索桥，
桥身是用树藤和木板连起来的，一阵风吹来，桥摇摇欲坠，几块木板
还掉了下去。你不由的忧豫起来，止步不前了。一块石碑(shibei)立
在桥旁。
LONG);
     set("outdoors", "天龙寺");
     set("exits",([
           "north" : __DIR__"fqg",
           "south" : __DIR__"bzq",
           "east" : __DIR__"wxj",
     ]));
     set("item_desc", ([
                "shibei" :HIW"


    ※※※※※※※※
    ※※※　　※※※
    ※※※　  ※※※
    ※※※ 百 ※※※
    ※※※    ※※※
    ※※※ 丈 ※※※
    ※※※　  ※※※
    ※※※ 桥 ※※※
    ※※※　  ※※※
    ※※※　　※※※
    ※※※※※※※※\n"NOR,
        ]));

     set("coor/x",-390);
  set("coor/y",-270);
   set("coor/z",30);
   setup();
}
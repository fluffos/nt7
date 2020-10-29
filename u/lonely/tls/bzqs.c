#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
  set("short","百丈桥边");
  set("long",@LONG
你走出了松林，一条深沟横在面前，挡住了你的去路，沟上有一
座长长的索桥，桥身是用树藤和木板连起来的，一阵风吹来，桥摇摇
欲坠，几块木板还掉了下去。你不由的忧豫起来，止步不前了。一块
石碑(shibei)立在桥旁。
LONG);
     set("outdoors", "天龙寺");
     set("exits",([
           "north" : __DIR__"bzq",
           "south" : __DIR__"road5",
     ]));

set("objects",([
		__DIR__"npc/liao-kuan" : 1,
		]));


     set("item_desc", ([
                "shibei" :
HIW"


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
  set("coor/y",-290);
   set("coor/z",30);
   setup();
}
int valid_leave(object me, string dir)
{
       string name, new_name;
      //  me = this_player();
        name = me->query("name");
        new_name = name[0..0];

    if (me->query("family/family_name") != "天龙寺" &&
            present("liaokuan chanshi", environment(me)) &&
	    dir =="north")
            return notify_fail("了宽禅师大师把手一伸，拦住了你的去路，\n"+
           "说道：阿弥陀佛，施主不是天龙弟子，不得过百丈桥到后山。\n");
/*
     if ((new_name != "本" || && present("liaokuan chanshi", environment(me)) && dir =="north")
            return notify_fail("了宽禅师把手一伸，拦住了你的去路，\n"+
           "说道：阿弥陀佛，你的辈分不够，不能去后山。\n");
*/
        return ::valid_leave(me, dir);
}

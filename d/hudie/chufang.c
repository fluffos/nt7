// 厨房 chufang.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "厨房");
        set("long", @LONG
这是一间宽敞的厨房，一个小童正在忙碌着作饭，整个房间弥漫
着令人垂涎欲滴的菜香，看来这个小童的手艺还不错。你走了半天本
来就饿的肚子不由地咕咕交了起来。
LONG );

        set("no_fight", 1);

        set("exits", ([ 
            "north" : __DIR__"huapu4",
            "south" : __DIR__"xfang2",
            "east" : __DIR__"caotang",
        ]));

        set("objects",([
            __DIR__"npc/xtong3" : 1,
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object *ob = deep_inventory(me);
        int i = sizeof(ob);
        if((dir != "west")){
          while (i--)
          if(ob[i]->id("rice") || ob[i]->id("miantang") || ob[i]->id("qingcai"))
             return notify_fail(CYN"小僮哼了一声：吃饱喝足了还要带走呀！\n"NOR);                
        }
        return ::valid_leave(me, dir);
}
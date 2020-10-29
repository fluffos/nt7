// 山壁 shanbi.c
 
#include <ansi.h>
inherit ROOM;

void create() 
{ 
        set("short", "山壁");
        set("long", @LONG
这里嫣红姹紫，遍山遍野都是鲜花，春光浪漫已极，转了几个弯，
却见迎面一块山壁，路途已尽。旁边是一排花丛(huacong)。
LONG );

        set("item_desc", ([
                "huacong" : "这是一排漂亮的花丛，几只蝴蝶从花从里钻了进去。\n",
        ]));

        set("outdoors", "蝴蝶谷");

        set("exits", ([ 
                "east" : "/d/wudang/wdroad2",
        ]));

        set("coor/x",80);
  set("coor/y",-170);
   set("coor/z",0);
   setup();
}

void init()
{
        add_action("do_bo", "bo");
}

int do_bo(string arg)
{
        object room, me;
        mapping fam;

        me = this_player();
        fam=query("family", me);

        if(!living(me) ) return 0;

        if ( me->is_busy() || me->is_fighting())
              return notify_fail("你正忙着哪！\n");

        if( !arg || arg != "huacong" ) return 0;

        if( arg == "huacong" ){
            if( (!fam || fam["family_name"] != "明教") && (!query_temp("hdq", me)) )
                return notify_fail("你拨了拨花丛，并没有什么发现，不禁有些怅然。\n");
            message_vision(HIC"$N拨了拨周围的花丛，突然发现右边"HIY"(Right)"HIC"好象有一条小路。\n"NOR, me);
            if(!(room = find_object(__DIR__"shanbi")))
              room = load_object(__DIR__"shanbi");
              set("exits/right", __DIR__"huacong1");
              call_out("delete_exit", 5, room);
              return 1; 
        }
}

void delete_exit(object room)
{       
        message("vision",HIW"一阵微风吹来，花丛动了起来，挡住了小路。\n"NOR, room);
        delete("exits/right");
}

int valid_leave(object me, string dir)
{
	return ::valid_leave(me, dir);
}
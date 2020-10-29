// Modify By River 98/12
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "黑森林");
	set("long", @LONG
你信步而行，举步踏到的尽是矮树长草，这里没有路,每走一步，荆棘都
钩刺到小腿,划破你的身体。
LONG
	);
        set("outdoors", "大理");

	set("exits", ([
           "south" : __DIR__"xiaoxi",
           "north" : __DIR__"senlin-2",
           "west" : __DIR__"senlin-3",
           "east" : __DIR__"senlin-4",
	]));

	setup();
}

void init()
{
        add_action("do_look", "look");
}

int do_look(string arg)
{
        object me = this_player();        
        mixed *local;
        local = localtime(time() * 60);
        if (!arg){
        if(local[2] < 3 || local[2] >= 21) {
          message("vision",BLU"这里黑黝黝一片，\n"
          "越来越多，转眼便布满山谷，有的如流萤飘飞，有的如繁星闪烁。\n"NOR, me);
          }
         return 0;
      }
}
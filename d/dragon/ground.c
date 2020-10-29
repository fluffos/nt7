#include <room.h>
inherit ROOM;

void init();
int do_climb(string arg);

void create()
{
      set("short","芳草地");
      set("long",
"芬芳的草地，到处是奇花异草。有一个参天大树(tree)在草坪中央，\n"
"看起来似乎有一种神力。\n"
);
      set("exits",([ /* sizeof() == 1 */
          "southdown"  : __DIR__"bamboo1",
          "east"  : __DIR__"hole",
      ]));
      set("item_desc",([
                 "tree" :"紫色的树身，坚硬无比，正是传说中的人参果树。\n"
      ]));
      set("objects", ([
  //       "/d/shenlong/obj/hua4" : 2,
      ]));
      set("no_magic", 1);
        setup();
      create_door("east", "石门", "west", DOOR_CLOSED);
}

void init()
{
        add_action("do_climb","climb");
}

int do_climb(string arg)
{
      object me;
      me = this_player();
      if (!arg || arg != "tree")
   {
            return notify_fail("你要爬什么？\n");
    }
        if( query("qi", me)<70 )
                return notify_fail("你的气不足，恐怕爬不上去。\n");
        if ((int)me->query_skill("dodge", 1) < 130)
{
          message_vision("$N想爬上树去，可是爬到一半就一头栽了下来。\n\n",me);
            me->receive_damage("qi",60);
         return 1;
}
else
          message_vision("$N脱掉鞋子，三下两下就爬上了树去。\n\n",me);
            me->receive_damage("qi",60);
                  me->move(__DIR__"tree");
       return 1;
}

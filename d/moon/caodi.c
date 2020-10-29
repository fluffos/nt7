// ken 1999.12.9

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "幽香湖旁");
	set("long", @LONG
地势到此豁然开朗，眼前是各式各样的奇花异草。左边是一个小湖，
幽风袭面，清香暗涌。北面则是陡峭的山崖，你这才发现，刚才的
灯光就来自这座山上。
LONG
	);
	set("exits", ([ 
  "east" : __DIR__"caodi2",
  "west" : __DIR__"caodi1",
  "northup" : __DIR__"road1",
]));
	set("coor/x",-30);
	set("coor/y",1050);
	set("coor/z",0);
	setup();
}
void init()
{
   add_action("do_jump", "jump");
}
int do_jump(string arg)
{
   object me, room;
   int mlvl;
   me = this_player();
   if(!arg || arg != "对面") 
    {
     write("你要向哪边跳？？");
     return 0; 
    }
   mlvl = (int)me->query_skill("move",1);
   if(mlvl < 50)
    {
      message_vision("$N纵身向对面跳了过去，呼呼....\n不好！！！没跳到！！！\n", me);
    me->unconcious();
      me->set("kee",(int)me->query("kee")/2);
      me->set("eff_kee",(int)me->query("eff_kee")/2);
      me->start_busy(4);
    }
   else{
      message_vision("$N纵身向对面跳了过去，你只觉得耳边风声忽忽作响。。。。\n\n", me);
      room = load_object(__DIR__"zz7");
      message_vision("你跳到对面，好累哪。。。\n", me);
      me->move(room);
   }
   return 1;
}

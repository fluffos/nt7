#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","城西客栈");
  set ("long", @LONG
这里是家小客店。这几天来住店的人很多，不知道还没有空房子。
店小二正在门前热情地招呼着客人。客店的门前挂着个大牌子，上面写
着「住宿五两纹银」。门口挂着两个大红灯笼，上面写着「平安」二字。
LONG);

  set("exits", ([ 
  
          "north":__DIR__"xijie2",
          "enter":__DIR__"shuifang",
         ]));
  set("objects",([
          __DIR__"npc/xiaoer2":1,
          ]));

  
  set("valid_startroom", 1);
  setup();
 
}

int valid_leave(object me,string dir)
{
        if( !query_temp("gived_money", me) && dir == "enter" )
                if(objectp(present("xiao",environment(me))))
                        return notify_fail("店小二拦住了你：客官，您还没给钱呢!\n");
                else return notify_fail("掌柜从里面喊道：客官，给钱再住店啊!\n");
                return ::valid_leave(me,dir);
                return 1;
}
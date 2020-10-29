#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","睡房");
  set ("long", @LONG
这里就是客栈的卧室了。只件这里已经横七竖八的躺了几个人。你
来到这里，不禁感到困了，打了一个呵欠。
LONG);

  set("exits", ([ 
  
        
          "out":__DIR__"kezhan",
         ]));
  set("sleep_room",1);
  set("valid_startroom", 1);
  setup();
 
}

int valid_leave(object me,string dir)
{
        if(dir=="out")
                delete_temp("gived_money", me);
        return ::valid_leave(me,dir);
}

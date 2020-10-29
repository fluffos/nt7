//room: /d/tangmen/qiushi.c

inherit ROOM;
#include <ansi.h>
void create()
{
  set("short","囚室");
  set("long",
      "这里四面一片漆黑，你借着刚刚打开的出口一点点亮光，发现里面竟然有一个\n"
"人。这个人被精钢镣铐锁着，不能动弹，蓬头垢面，但仍然看得出气度不凡。\n"
     );
   set("objects", ([
           __DIR__"npc/xiaoqiushui" : 1,
                 ]));        
  set("exits",([
      
          ]));

 setup();

}
void init()
{
        add_action("do_break", "break");
}
int do_break(string arg)
{
    int n;
        object me = this_player();

    if( !arg || arg!="bagua" )
        {
        write("唐门的财物岂是你随便能破坏的！\n");
        return 1;
    }

    message_vision(
    "$N走到八卦前，腾身而起，运起全身内力，双掌斜斜击向八卦。\n", this_player());


    n=query("neili", me);
    if (n >= 1500)
        {
        message_vision(
        HIR"$N只听一声巨响！！！！！！！！！\n"NOR, this_player());
        set("exits/up", "/d/tangmen/dating");
        set("neili", n-1500, this_player());
        remove_call_out("close");
        call_out("close", 10, this_object());
    }
    else
        {
                message_vision(
                HIW"结果只听一声闷哼，$N被八卦阵的反弹力震得眼前一黑....\n"NOR, this_player());
set("neili", 0,                 this_player());
                this_player()->unconcious();
    }
return 1;
} 



void close(object room)
{
    message("vision","只听见一阵嘎嘎的响声，八卦又翻了转来，恢复了原样。\n", room);
    delete("exits/up", room);
}



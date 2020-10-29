// Room: /d/tangmen/dating.c
//by hem
inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "议事大厅");
        set("long", @LONG
        这里是唐门的议事大厅。平时一般不使用，只有在唐门发生重大事情的时
候，唐门的长辈才在这儿聚集商量。整个大厅建筑得很奇怪，四周有八根朱红大柱
地面黝黑发亮，是唐门平时冶炼暗器所剩的铁屑溶制成的整块。正中是一个很大的
八卦图(bagua)。
LONG
        );
        
        set("valid_startroom", 1);

        set("exits", ([
                
           "north" : __DIR__"houzhai",
        ]));
     set("objects", ([
 __DIR__"npc/dizi" : 1,
                        ]));

        set("item_desc", ([
                "bagua" : HIY "很奇怪的八卦图，不知道唐门为什么要在这儿刻上它。\n",  
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
if( query_temp("marks/闹", this_player())){
    message_vision(
    "$N走到八卦前，腾身而起，运起全身内力，双掌自上而下重重击向八卦。\n", this_player());


    n=query("neili", me);
    if (n >= 1500)
        {
        message_vision(
        HIR"$N只听轰得一声巨响！！！八卦竟然翻转，面前出现一个洞。\n"NOR, this_player());
        set("exits/down", "/d/tangmen/qiushi");
        set("neili", n-1500, this_player());
        remove_call_out("close");
        call_out("close", 10, this_object());
    }
    else
        {
                message_vision(
                HIW"结果只听一声闷哼，$N被八卦的反弹力震得眼前一黑....\n"NOR, this_player());
set("neili", 0,                 this_player());
                this_player()->unconcious();
    }
delete_temp("marks/闹", me);
return 1;    
}
else 
        {write(HIY"你娃脑壳有包啊？看到是铁砣砣都要去打！\n"NOR);
        return 1;}
}

void close(object room)
{
    message("vision","只听见一阵嘎嘎的响声，八卦又翻了转来，恢复了原样。\n", room);
    delete("exits/down", room);
}
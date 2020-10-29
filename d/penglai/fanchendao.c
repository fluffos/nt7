inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "凡尘道");
        set("long",@LONG
由于仙界有规定，岛中仙人均不可随意离岛，需要进行外出游
历时即入了凡尘，凡是需要出岛进入凡尘的仙者均需要由此处出岛，
经过彩石沙滩洗尽身上仙气才能进入尘世间，而洗掉仙气同时，出
岛仙者的法力也大大减弱。
LONG);

        set("exits", ([
                "southeast"   : __DIR__"pantaoyuan2",
                "southwest"   : __DIR__"pantaoyuan3",
                "north"       : __DIR__"caishishatan",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛

        set("no_clean_up", 1); 

        set("region", "penglai");
        setup();
}

void init ()
{
        if( !query_temp("apply/xianshu-lingwei", this_player()) )
        {
                if( !query("penglai/go_quest/ok", this_player()) )
                {
                        this_player()->start_busy(3);
                        tell_object(this_player(), NOR + WHT "你到了此处，四周仙气缭绕令你一时间难以辨别方向。\n" NOR);
                }
                else
                {
                        if (random(2))
                        {
                                this_player()->start_busy(1);
                                tell_object(this_player(), NOR + WHT "你到了此处，四周仙气缭绕令你一时间难以辨别方向。\n" NOR);                
                        }
                }
        }
}

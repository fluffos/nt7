inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "长生村");
        set("long",@LONG
这里是长生村东村，周围三三两两的茅草房，鸡犬相闻，
炊烟了了，不时有几只黄毛狗摇着尾巴对着你叫几声，看来
在对你表示欢迎。不远处几位村民正在耕田，耕牛传来卖力
的吼叫声。一群幼鸡跟着一名农妇，正在争抢着农妇洒下的
米食。偶有三五成群的小毛孩相互追逐，嬉戏。此情此景，
令人好生羡慕。
LONG);

        set("exits", ([
                "west"         : __DIR__"changshengcuneast1",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        set("no_fight", 1);
        set("no_fight", 1);
        set("sleep_room", 1);

        set("objects", ([
                __DIR__"npc/wantong" : random(4),
                __DIR__"npc/nongfu1" : random(2),
                __DIR__"npc/nongfu2" : random(2),
        ]));
        
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

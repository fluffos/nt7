inherit ROOM;

#include <ansi.h>

void create()
{
        set("short", "长生村");
        set("long",@LONG
这里便是传说中长生村了，想来奇怪，这村与人间普通
村庄竟无任何区别，村中房舍与居民也与凡间所见相同。不
远处几个村民正在辛勤地劳作，鸡犬相闻，好不快活。回头
一想自己四海漂泊，浪迹天涯，不禁黯然感慨。不远处炊烟
了了，偶有三两个村民赶着牛车经过，看似非常忙碌，不时
地，从前方房屋中传出机杼之声，想必是村中妇女正忙着纺
织棉布，你心中黯然，归家感觉油然而生。
LONG);

        set("exits", ([
                "west"          : __DIR__"changshengcunwest1",
                "east"          : __DIR__"changshengcuneast1",
                "north"         : __DIR__"changshengcunnorth1",
                "south"         : __DIR__"changshengcunsouth1",
                "out"           : __DIR__"changshengdao1",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        set("no_fight", 1);
        
        set("objects", ([
                __DIR__"npc/shuzhongxian" : 1,
                __DIR__"npc/wantong" : random(4),
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

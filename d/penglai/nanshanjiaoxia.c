inherit ROOM;

#include <ansi.h>

#define MEMBER_D "/adm/daemons/memberd"

void create()
{
        set("short", "南山脚下");
        set("long",@LONG
这是通往蓬莱岛南山的必经之路，传说南山乃仙人修炼仙法的
地方，属于禁地。虽无人看守，但若没有仙人的指引外人是无论如
何也无法进入的。四周植物葱郁，仙气围绕，景致甚是迷人。抬头
仰望南山，山峰高耸，仙气缭绕，再一细看又若隐若现，令人难以
琢磨。
LONG);

        set("exits", ([
                "north"    : __DIR__"xianrenzhilu",
        ]));
        set("no_rideto", 1);         // 设置不能骑马到其他地方
        set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
        set("no_die", 1);            // 死亡后移动到扁鹊居
        set("penglai", 1);           // 表示在蓬莱岛
        set("no_fight", 1);
        
        set("region", "penglai");
        setup();
}

void init ()
{
        add_action("do_closeeye", "closeeye");
        
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
        
        if( !query("penglai/nanshan_quest/ok", this_player()) )
        {
                tell_object(this_player(), HIG "\n你正欲进入南山，却发现这里根本没有上山之路，奇哉！。\n" NOR);
        }
        else
        {
                tell_object(this_player(), HIG "\n要进入南山，闭上你的眼睛(closeeye)，默念守路仙人教给你的咒语。\n" NOR);
        }
}

int do_closeeye(string arg)
{
        object me;
        int i;
        object *inv;
        object horse, person;
        
        
        me = this_player();
        
        if (me->is_busy())
                return notify_fail("你正忙。\n");
                
        // 所有骑马的人必须下马
        if( objectp(horse=query_temp("is_riding", me)) )
        {
                if( objectp(person=query_temp("is_rided_follow", horse)) )
                        delete_temp("is_riding_follow", person);

                delete_temp("is_rided_follow", horse);
                delete_temp("is_rided_by", horse);
                delete_temp("is_riding_follow", me);
                delete_temp("is_riding", me);

                message_vision(HIR "\n$N的" + horse->name() + HIR " 似乎受到了惊吓，前蹄一扬，所有人"
                               "被迫跳下马。\n\n" NOR, me);

                return 1;
        }
                        
        // 把背起的用户放下来
        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! playerp(inv[i])) continue;

                // 被人背起的用户
                inv[i]->move(__FILE__);                
        }

        if( query("penglai/nanshan_quest/ok", this_player()) )
        {
                i = 20;
                tell_object(this_player(), HIG "\n你闭上你的眼睛，默念守路仙人教给你的咒语...\n" NOR);
                if( !MEMBER_D->is_valid_member(query("id", this_player())) )
                        return notify_fail("对不起，南山地图只对有效会员开放。\n");
                        
                me->move(__DIR__"nanshanzhong" + random(i));
        }
        else
        {
                return 0;
        }

        return 1;
}

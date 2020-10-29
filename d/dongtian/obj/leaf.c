// This program is a part of NITAN MudLIB 
// redl 2015/3
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR HIC"仙隐"HIG"符叶"NOR,({"xianyin fuye", "fuye"}));
        set("long", HIG "这是一片仙界流传出来的神奇树叶，上面刻画有隐身符意。\n" NOR HIK "(use fuye)\n" NOR); 
        set("unit", "片");
        set("base_unit", "片");
        set("value", 10000);
        set("base_value", 10000);
        set_weight(100);
        set("base_weight",100);
        set("material", "jade");
        setup();
}

int do_open(string arg)
{
        object ob, me = this_player();
        int ra, lv = query("level", me);
                
                if (environment()!=me) return 0;
        if (!arg || (arg!="fuye" && arg!="xianyin fuye")) return 0;
        if( me->is_busy() ||
                me->is_fighting()
                ) {
                write(NOR BUSY_MESSAGE NOR);
                return 1;
        }
        if (lv<50) {
                write(NOR "你的等级小于５０级，不能使用这种符叶。\n" NOR);
                return 1;
        }
        if (query_temp("flag_hslj", me)) {
                write(NOR "现在是在华山擂台，不能使用这种符叶。\n" NOR);
                return 1;
        }
        if( query_temp("apply/shade_vision", me) ) {
                        write(NOR "你现在正在隐身之中。\n" NOR);
                return 1;
                }
                if( me->is_fighting()) {
                        write(NOR "你还是专心解决了敌人再说吧。\n" NOR);
                return 1;
                }
        set_temp("apply/shade_vision", 1, me);
        me->start_busy(3);
        message_vision(NOR + CYN + "$N" + NOR + CYN + "拿出一个树叶，抬手望自己额头上一帖，身形快速地消失了。\n" + NOR, me);
                __DIR__"leaf_c.c"->do_remove_yinxian(me);
        destruct(this_object());
        return 1;
}

void init()
{
        add_action("do_open","use"); 
}


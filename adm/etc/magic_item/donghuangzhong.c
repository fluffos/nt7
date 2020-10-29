// 上古十大神器之 东皇钟
// Create by Rcwiz for Hero.cn 2003/09
// 在 /d/songshan/fengchangtai.c可以打开天界之门

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIC "东皇钟" NOR, ({ "donghuang zhong", "donghuang", "zhong" }) );
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "口");
                set("long", HIC "这是一口看似普通的古钟，却有一种令人神往的气魄。\n"                                
                                "可用之来打开(qiao)天界之门，进入通天门。\n" NOR);

        }
        setup();
}

void init()
{
        add_action("do_qiao", "qiao");
}

int do_qiao(string arg)
{
        object me;
        
        me = this_player();
        
        if(! objectp(present("donghuang zhong", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");

        if (environment(me)->query("short") != "封禅台")
                 return notify_fail("你得到封禅台才能打开天界之门。\n");

        message_sort(HIC "\n$N" HIC "将东皇钟放在地上，然后用力一敲，只"
                         "听得一声巨响，刹那间，天际出现一道彩色之门，伴"
                         "随着千万道玄目的光华，东皇钟将$N" HIC "卷了进"
                         "去 ……\n" NOR, me);

        me->move("/kungfu/class/sky/tianmen0");
        destruct(this_object());

        return 1;
}

// 扫把 回春堂做任务的道具。

#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name("扫把", ({ "saoba" }));
        set_weight(5000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "根");
                set("long", "这是一根竹制的扫把。\n");
                set("value", 1);
                set("material", "iron");
                set("wield_msg", "$N拿出一把$n，拿在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        init_hammer(5);
        setup();
}

void init()
{
           add_action("do_job","dasao");
}

int do_job(string arg)
{
        object me;
        object weapon;
         int i, j;
        me = this_player();
        j=(random(query("str", me))/3);
        if (j <= 0)
                j = 5;

        if( query("jing", me) <= j){
                message_vision ("$N太累了，得先休息一下，才能继续完成任务！\n", me );
                return 1;
        }

        if( !query_temp("renwu_name", me)){
                message_vision ("$N拿起扫把，狂舞了一阵便觉无趣！\n", me);
                return 1;
        }

        if( query_temp("renwu_wancheng", me) >= 100 )
        {
                set_temp("renwu_wancheng", 100, me);//表示完成任务
                return notify_fail ("你完成了任务，回去复命吧！\n");
        }

              if (me->is_busy()) 
                      return notify_fail("你现在正忙着呢！\n"); 
        if( query("short", environment(me)) != query_temp("renwu_name", me) )
                return notify_fail ("不是让你在这里打扫啊！\n");

        //判断是否wield了工具
        if( !objectp(weapon=query_temp("weapon", me) )
            || query("id", weapon) != "saoba" )
        {
                return notify_fail ("你空手怎么扫地？拿手抓吗！\n");
        }
        else 
        {               
                addn_temp("renwu_wancheng", j, me);
                addn("jing", -j, me);
                me->improve_skill("medical", (j/3));
                message_vision ("$N拿起扫把，一边扫着地板，一边留意医师在给人把脉！\n", me);
                   me->start_busy(1+random(3));
        }
        return 1;
}
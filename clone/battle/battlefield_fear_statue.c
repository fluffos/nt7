#include <ansi.h>

#define BATTLEFIELD2_D     "/adm/daemons/battlefieldd2.c"
inherit ITEM;

void delay_destruct()
{
        destruct(this_object());
}

void init(object me)
{
        object target;
        string* players;

        if( !me ) me = this_player();
        if( !userp(me) ) 
                return;

        if( !BATTLEFIELD2_D->in_battle(me) )
                return;

        if( query_temp("used") )
                return tell_object(me, name(1)+"的强大能力已经被使用。\n");

        players = BATTLEFIELD2_D->get_sorted_players();

        for(int i=0;i<sizeof(players);++i)
        {
                if( players[i] == me->query_id(1) )
                        continue;

                target = find_player(players[i]);
                if( !objectp(target) || !BATTLEFIELD2_D->inside_battlefield(target) )
                        continue;

                if( objectp(target) && BATTLEFIELD2_D->in_battle(target) )
                        break;
        }

        BATTLEFIELD2_D->add_bonus_score(me, 100);
        tell_object(me, "你因为碰触"+name(1)+"而获得 "HIY"100"NOR" 点战绩红利。\n");
        if( target )
        tell_object(me, "你触动了战争恐惧石碑的力量让"+target->query_idname()+NOR"变得虚弱起来。\n");

        tell_object(target, HIR+me->query_idname()+HIR"使用了战争恐惧石碑的力量让你变得虚弱起来。\n" NOR);
        target->set_weak(10);

        call_out((: delay_destruct :), 1);

        set_temp("used", 1);
}

void create()
{
        set_name(RED"战争恐惧石碑"NOR, ({ "battlefield fear statue", "statue" }) );
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "使用这个石碑的人可以大幅降低另一位战场中玩家的能力。");
                set("value", 1000000);
                set("unit", "个");
                set("no_get", 1);
        }
}


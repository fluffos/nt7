// head.c 脑袋

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;
inherit F_CUTABLE;
inherit F_SILENTDEST;

void eat_effect();
int is_head() { return 1; }

void create()
{
        set_name(NOR + RED "头颅" NOR, ({ "head" }));
        set_weight(1500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 1);
                set("no_store", 1);
                set("no_sell", "我的天…这…这你也拿来卖…官…官府呢？");
                set("food_supply", 10);
                set("food_remaining", 4);
                set("long", RED "这是一颗鲜血淋淋的首级，鲜血正缓缓渗出。\n" NOR);
        }
}

int set_from(object owner)
{
        apply_effect((: eat_effect :));
        set("owner_id",query("owner_id", owner));
        set("victim_name",query("victim_name", owner));
        set("is_player",query("is_player", owner));
        set("killed_by",query("killed_by", owner));
        set("defeated_by",query("defeated_by", owner));
        set("defeated_by_who",query("defeated_by_who", owner));
        set("assist",query("assist", owner));
        set("gender",query("gender", owner));

        if( !stringp(query("victim_name", owner)) )
        {
                set("name", "腐烂的人头");
                set("name", "腐烂的无头尸体", owner);
        } else
        {
                set("name",query("victim_name", owner)+"的人头");
                set("name", "无头尸体", owner);
        }

        if( query_temp("clawed_by_jiuyin", owner) )
        {
                set_temp("clawed_by_jiuyin", 1);
                set("long", query("long") +
                            "上面赫然有五个小洞，伸手一探，刚好可以插入。\n");
        }

        set_name(NOR + RED + query("name") + NOR, ({ "head" }));
        return 1;
}

int do_cut(object me, string part)
{
        if (! query("food_remaining"))
                return 0;

        return ::do_cut(me, part);
}

int finish_eat()
{
        set_name(NOR + WHT "骷髅头" NOR, ({ "bone" }));
        set_weight(150);
        set("long", WHT "这是一个白森森的骷髅头。\n" NOR);
        return 1;
}

void eat_effect()
{
        object me;

        me = this_player();
        addn("combat/eatman", 1, me);
        if( query("shen", me)>-1000 )
                set("shen", -1000, me);
}
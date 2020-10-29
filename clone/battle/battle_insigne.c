#include <ansi.h>
#define BATTLEFIELD2_D     "/adm/daemons/battlefieldd2.c"
inherit COMBINED_ITEM;

void create()
{
        set_name(HIC"战"NOR CYN"争"HIC"勋"NOR CYN"章"NOR, ({ "battle insigne"}) );
        set_temp("status", HIG"传"NOR GRN"奇");

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", "从战争中获得的战争勋章，可以用来兑换稀有的物品，也可以\n"
                            "使用(use)它重新进入战场。\n");
                set("unit", "堆");
                set("base_unit", "枚");
                set("base_value", 100);
                set("no_sell", 1);
                set("no_drop", 1);
                set("no_give", 1);
        }
        setup();
        set_amount(1);
}

void init()
{
        add_action("do_use", "use");
}

int do_use(string arg)
{
        object me;
        object env;

        me = this_player();

        if( !BATTLEFIELD_D->is_battle_open() && !BATTLEFIELD2_D->is_battle_start() )
                return notify_fail("战斗还没有开始报名。\n");

        if( !BATTLEFIELD_D->is_battle_start() && !BATTLEFIELD2_D->is_battle_start() )
                return notify_fail("战斗还没有开始。\n");
        
        if( !BATTLEFIELD_D->in_battle(me) && !BATTLEFIELD2_D->in_battle(me) )
                return notify_fail("你可以使用battle join来参加战斗。\n");        
                
        if( BATTLEFIELD_D->inside_battlefield(me) || BATTLEFIELD2_D->inside_battlefield(me) )
                return notify_fail("你已经在战场中了，为荣誉而战吧。\n");

        if( BATTLEFIELD_D->in_battle(me) ) BATTLEFIELD_D->init_player(me);
        else BATTLEFIELD2_D->init_player(me);
        add_amount(-1);
        return 1;
}


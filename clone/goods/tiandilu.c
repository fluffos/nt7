// This program is a part of NITAN MudLIB 
// redl 2015/4

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC"天"HIK"地"HIR"洪炉" NOR, ({ "tiandi lu", "lu" }));
        set_weight(2000);
        set_max_encumbrance(100000000000000);
                set("unit", "个");
                set("long", "且夫天地为炉兮，造化为工。阴阳为炭兮，万物为铜。\n");
                set("value", 20000);
                set("auto_load", 1);
                set("item_prop/medical", 6000);
                set("item_prop/liandan-shu", 4000);
        setup();
}

int msg_drink(object me)
{
        message_vision(NOR CYN "$N"NOR CYN"吧嗒吧嗒地咂嘴，似乎意犹未尽的样子。\n" NOR, me);
}

int do_drink(string arg)
{
        object ob, *obs;
        object me = this_player();
        object qm = this_object();
        int i = 25;
        
        if (!arg || (arg!="lu" && arg!="tiandi lu"))
                return 0;
        if (me->is_busy()) 
                return notify_fail(BUSY_MESSAGE);
        if (me->is_fighting()) 
                return notify_fail(NOR "你还在战斗里，不能喝天地洪炉。\n" NOR);
        if (environment(qm)!=me)
                return notify_fail(NOR "你先拿起来再喝吧。\n" NOR);
                
        //obs = filter_array(all_inventory(qm), (: sscanf(base_name($1),"/clone/%*s") :));
        obs = all_inventory(qm);
        if (!obs || !sizeof(obs)) {
                return notify_fail(NOR "天地洪炉里什么也没有。\n" NOR);
        }
        
        message_vision(NOR CYN "$N"NOR CYN"抱起$n" NOR CYN "往嘴巴里一倒...\n" NOR, me, qm);
        while (i--) {
                if (!obs || !sizeof(obs)) break;
                ob = obs[random(sizeof(obs))];
                if (!ob) break;
                me->command("eat " + query("id", ob) + " in tiandi lu");
                me->stop_busy();
                obs = all_inventory(qm);
        }
        remove_call_out("msg_drink");
        call_out("msg_drink", 1, me);         
        me->start_busy(3+random(2));
        return 1;
}

int is_container() { return 1; }
int can_make_medicine() { return 1; }

void init() {
        if (!interactive(this_player())) return;
        add_action("do_drink", "drink");
}

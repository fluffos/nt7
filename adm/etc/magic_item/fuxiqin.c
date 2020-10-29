// 上古十大神器之 伏羲琴
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + MAG "伏羲琴" NOR, ({ "fuxi qin", "fuxi", "qin" }) );
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "把");
                set("long", NOR + MAG "这是一把看似普通的古琴，传说乃上古伏羲氏\n"
                                      "所用。\n"
                                      "弹奏(tan)后可恢复所有精、气、内力和异常状态。\n" 
                                      "需要弹琴技法一百级，tan ? 查看使用次数。\n" NOR);

        }
        setup();
}

void init()
{
        add_action("do_tan", "tan"); 
}

int do_tan(string arg)
{
        object me;
        mapping my;
        
        me = this_player();
        
        if(! objectp(present("fuxi qin", me)))return 0;

        if (arg == "?")
        {
                 write(HIG "使用次数 " + this_object()->query("count") + "/3\n" NOR);
                 return 1;
        }
                
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");

        message_sort(NOR + MAG + "\n$N" NOR + MAG "盘膝而坐，轻轻地拨弄着伏羲琴，"
                                 "伴随着令人心醉的琴声，$N" NOR + MAG "只觉得周身"
                                 "舒泰之极。\n" NOR, me);

        my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"];
        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
        my["qi"]     = my["eff_qi"]     = my["max_qi"];
        my["neili"]  = my["max_neili"];
        my["food"]   = me->max_food_capacity();
        my["water"]  = me->max_water_capacity();
        me->clear_condition();
        me->save();
        
        me->start_busy(2);
        this_object()->add("count", 1);
        if (this_object()->query("count") >= 3)
        {
                write(HIW "只听得一阵脆响，伏羲琴已损坏了。\n" NOR);
                destruct(this_object());        
        }

        return 1;
}

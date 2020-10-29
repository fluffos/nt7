#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "干将精元" NOR, ({ "ganjiang jingyuan" }) );
        set_weight(1);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "这是一颗晶莹无瑕的宝石，据说拥有着奇幻的力量。\n"
                                "输入指令 use <你的九级兵器ID> 可将九级兵器提升到待镶嵌状态。\n"
                                "只要进行最后一步镶嵌即可将你的九级兵器提升为十级神器。        十级神\n"
                                "器拥有着超凡的力量。\n"
                                "有关最后一步镶嵌及十级神器介绍请参见帮助文件 help weapon | help enchase\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "块");
        }

        setup();
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_use", "use");
        }
}

int do_use(string arg)
{
                object me;
                object weapon;
                
                string result;

                me = this_player();

                if (! arg)return notify_fail("指令格式: use <你九级兵器的ID>\n");

                if (! objectp(weapon = present(arg, me)))
                        return notify_fail("你身上没有这样道具。\n");

            if (! weapon->is_item_make())
                        return notify_fail("无法在此道具上完成。\n");

            if (weapon->weapon_level() < 12000)
                        return notify_fail("只能九级兵器才能进行该项操作。\n");

                weapon->set("magic/imbue_ok", 1);
                weapon->set("owner/" + weapon->item_owner(), 5000000);
                
                weapon->save();
            
        tell_object(me, HIC "你感受" + weapon->name() + HIC "发生了"
                    "不可言喻的变化。\n" NOR);


                destruct(this_object());

                return 1;
}

int query_autoload()
{
         return 1;
}
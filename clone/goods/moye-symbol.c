#include <ansi.h>
inherit ITEM;

int query_autoload() { return 1; }
void create()
{
        set_name(HIM "莫邪圣符" NOR, ({ "moye symbol", "symbol" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIM "莫邪圣符可以将普通道具升级(into)为下线不掉物品。\n" NOR);
                set("unit", "张");
                set("value", 500000);
        }
        setup();
}

void init()
{
        add_action("do_integrate", "into");
}

int do_integrate(string arg)
{
        object me;
        object ob;

        if (! arg)
                return notify_fail("你要往什么道具上使用该圣符？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)) &&
            ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你身上和附近没有这样道具啊。\n");
        
        if (ob == this_object() || ob->is_character())
                return notify_fail("你想要干什么?\n");
                
        if (ob->query_autoload())
                return notify_fail(ob->name() + "已经是下线不掉物品了，没有这个必要吧！\n");

        set("set_data", 1, ob);
        set("auto_load", 1, ob);

        tell_object(me, "你把" + name() + "盖在" + ob->name() + "上，然后口中念念有词，"
                        "只见圣符化作一道红光飞入" + ob->name() + "体内！\n");

        tell_object(me, HIC "你感受" + ob->name() + HIC"发生了不可言喻的变化。\n" NOR);

        destruct(this_object());
        return 1;
}
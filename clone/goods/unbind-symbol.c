#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "解除绑定符" NOR, ({ "unbind symbol", "unbind", "symbol" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", YEL "该符文可以解除(unbind)物品的绑定属性。\n" NOR);
                set("unit", "块");
                set("value", 500000);
        }
        setup();
}

void init()
{
        add_action("do_unbind", "unbind");
}

int do_unbind(string arg)
{
        object me;
        object ob;

        if (! arg || arg == "")
                return notify_fail("你要往什么道具上使用该神符？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)) &&
            ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你身上和附近没有这样道具啊。\n");

        if (ob == this_object() || ob->is_character())
                return notify_fail("你想要干什么?\n");

        if (!query("bindable", ob))
                return notify_fail("这个物品没有绑定过，无需解除绑定！\n");

        delete("bindable", ob);
        delete("bind_owner", ob);
        set("set_data", 1, ob);
        set("auto_load", 1, ob);

        tell_object(me, "你把" + name() + "盖在" + ob->name() + "上，然后口中念念有词，"
                        "只见圣符化作一道红光飞入" + ob->name() + "体内！\n");

        tell_object(me, HIC "你感受" + ob->name() + HIC"已经解除了绑定。\n" NOR);

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}



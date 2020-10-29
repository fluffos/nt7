#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "解除干将绑定符" NOR, ({ "remove symbol", "remove", "symbol" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", YEL "该符文可以解除(unbind)物品的被干将圣符绑定。\n" NOR);
                set("unit", "块");
                set("value", 5000);
        }
        setup();
}

void init()
{
        add_action("do_unbind", "unbind");
}

int do_unbind(string arg)
{
        string id, file;
        object obj;
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

        if( query("item_owner", ob) != query("id", me) )
                return notify_fail("你只能解除你自己的物品！\n");

        if( !sscanf(base_name(ob), "/data/template/%*s") )
                return notify_fail("这个物品没有用干将圣符绑定过！\n");

        if( !ob->is_xunzhang() )
                return notify_fail("目前只开放解除勋章类的绑定！\n");

        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的装备再说！\n"); 

        id = replace_string(query("id", ob), " ", "-");
        file = "/clone/medal/"+id+".c";
        if( !objectp(obj = new(file)) )
                return notify_fail("解除勋章失败，请联系巫师解决！\n");

        obj->move(me);
        rm(base_name(ob)+".c");

        tell_object(me, "你把" + name() + "盖在" + ob->name() + "上，然后口中念念有词，"
                        "只见圣符化作一道红光飞入" + ob->name() + "体内！\n");

        tell_object(me, HIC "你感受" + ob->name() + HIC"已经解除了绑定。\n" NOR);

        destruct(ob);
        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}


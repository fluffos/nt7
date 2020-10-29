#include <ansi.h>
inherit ITEM;

int query_autoload() { return 1; }
void create()
{
        set_name(HIM "欧冶子圣符" NOR, ({ "ouyezi symbol", "symbol" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIM "欧冶子圣符可以将普通自造兵器升级(upd)为准10LVL兵器。\n" NOR);
                set("unit", "张");
                set("value", 500000);
        }
        setup();
}

void init()
{
        add_action("do_integrate", "upd");
}

int do_integrate(string arg)
{
        object me;
        object ob;
        string ownerid;

        if (! arg)
                return notify_fail("你要往什么道具上使用该圣符？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)) &&
            ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你身上和附近没有这样道具啊。\n");

        if( !ob->is_item_make() )
                return notify_fail("只有自造装备才可以升级为准10LV。\n");

        if( query("magic/imbue_ok", ob) )
                return notify_fail(name() + "已经是准10LVL以上兵器，没有这个必要吧。\n");

        if (!ob->is_weapon() && !ob->is_unarmed_weapon())
        {
                set("forge", 100, ob);
                set("magic/imbue_ok", 1, ob);
        }
        else
        {
        ownerid = ob->item_owner();
        
        addn("combat/MKS", 2100, ob);
        addn("owner/"+ownerid, 21000000, ob);
        set("magic/imbue_ok", 1, ob);
        addn("magic/blood", 21000, ob);
        }
        ob->save();
  
        tell_object(me, "你把" + name() + "盖在" + ob->name() + "上，然后口中念念有词，\n"
                        "只见圣符化作一道红光飞入" + ob->name() + "体内！\n");

        tell_object(me, HIC "你感受" + ob->name() + HIC"发生了不可言喻的变化。\n" NOR);

        destruct(this_object());
        return 1;
}

#include <ansi.h>
inherit ITEM;

int query_autoload() { return 1; }
void create()
{
        set_name(HIM "欧冶子木符" NOR, ({ "ouyezi wood", "symbol" }));
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIM "欧冶子木符可以将普通自造防具升级(upd)为准开孔状态，拥有木属性。\n" NOR);
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

        if( query("magic/imbue_ok", ob) )
                return notify_fail(name() + "已经是准10LVL以上兵器，没有这个必要吧。\n");

        if (ob->is_weapon() || ob->is_unarmed_weapon())
                return notify_fail("你只能在防具上使用该圣符。\n");
                
        ownerid = ob->item_owner();
        
        set("magic/imbue_ok", 1, ob);
        set("magic/type", "wood", ob);
        ob->save();
  
        tell_object(me, "你把" + name() + "盖在" + ob->name() + "上，然后口中念念有词，\n"
                        "只见圣符化作一道红光飞入" + ob->name() + "体内！\n");

        tell_object(me, HIC "你感受" + ob->name() + HIC"发生了不可言喻的变化。\n" NOR);

        destruct(this_object());
        return 1;
}
// 玄兵圣水用于开孔兵器

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "无极圣水" NOR, ({ "wuji water", "water" }) );
        set_weight(30);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("long", HIW "一瓶莹剔透圣水，散射出绚目的光彩。\n"
                            "他可以用来直接扩展(kuokong)兵器或防具最大孔数。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "瓶");
        }

        setup();
}

void init()
{
        add_action("do_kuokong", "kuokong");
}

int do_kuokong(string arg)
{
        object me;
        object ob;

        if (! arg)
                return notify_fail("你要往什么道具上使用无极圣水？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)) &&
            ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你身上和附近没有这样道具啊。\n");
        
        if (ob == this_object() || ob->is_character())
                return notify_fail("你想要干什么?\n");
        
        if (! ob->is_item_make())
                return notify_fail(ob->name() + "无法用无极圣水来扩展凹槽。\n");
        
        if( !query("enchase/flute", ob) )
                return notify_fail("你还是先去开孔后再考虑扩展凹槽吧。\n");
                
        set("ultimate/37", 1, ob);
        set("ultimate/39", 1, ob);
        
        if( query("skill_type", ob )
        ||  ob->is_unarmed_weapon())
                set("enchase/flute", 9, ob);
        else
                set("enchase/flute", 7, ob);
        
        ob->save();
        tell_object(me, "你把一瓶" + name() + "洒在" + ob->name() + "上，"
                        "只见" + ob->name() + "通体红光一闪即灭，豁然已经多出几个凹槽！\n");

        destruct(this_object());
        return 1;
}

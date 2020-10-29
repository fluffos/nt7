#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "神圣血清" NOR, ({ "god blood", "god", "blood" }));
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIR "這是一瓶神圣血清，似乎可以飲用。\n" NOR);
                set("unit", "瓶");
                set("value", 300000);
        }
        setup();
}

void init()
{
        add_action("do_drink", "drink");
}

int do_drink(string arg)
{
        object me = this_player();

        string mapsk;
        string na, un;
        mapping my = me->query_entire_dbase();
        int time = 1800;

        na = query("name");
        un = query("unit");

        if (! arg || ! id(arg))
                return notify_fail("你要喝什么东西？\n");

        if (me->is_busy())
                return notify_fail("急什么，小心别噎着了。\n");

        my = me->query_entire_dbase();

        // vip的效果
        switch( me->query_viplevel() )
        {
        case 1:
                time = time - time / 10;
                break;
        case 2:
                time = time - time * 2 / 10;
                break;
        case 3:
                time = time - time * 3 / 10;
                break;
        case 4:
                time = time - time * 4 / 10;
                break;
        case 5:
                time = time - time * 5 / 10;
                break;
        case 6:
                time = time - time * 6 / 10;
                break;  
        case 7:
                time = time - time * 7 / 10;
                break;                  
        }
        if( time < 10 ) time = 10;

        if( time()-query_temp("last_eat/blood", me) < time )
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        set_temp("last_eat/blood", time(), me);


        message_vision(HIY "$N" HIY "一仰脖，将一整" + un + na +
                       HIY "饮下，再也感觉不到任何疲惫。\n" NOR, me);

        my["jing"]     = my["max_jing"];
        my["qi"]       = my["max_qi"];
        my["eff_jing"] += my["max_jing"]/2;
        if( my["eff_jing"] > my["max_jing"] ) my["eff_jing"] = my["max_jing"];
        my["eff_qi"] += my["max_qi"]/2;
        if( my["eff_qi"] > my["max_qi"] ) my["eff_qi"] = my["max_qi"];
        my["neili"]    = my["max_neili"];
        my["jingli"]   = my["max_jingli"];

        me->start_busy(3);
        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}

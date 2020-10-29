//Cracked by Roath
inherit ITEM;
#include <ansi.h>
void setup()
{}

void init()
{
        add_action("do_make", "make");
}

void create()
{
        set_name("硫磺" NOR, ({"liu huang", "sulphur", "huang"}));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("long", "一块硫磺，通常用来制作火药。\n");
                set("value", 200);
        }
}

int do_make(string arg)
{
        object  ob, *obj, me = this_player();
        int i;
        if( !arg || arg!="lianxin dan" )
                return notify_fail("你要做什么？\n");
        if( me->query_skill("poison", 1) < 120)
                return notify_fail("你的毒技火侯不够，不能制作炼心弹。\n");
        if(! present("wugong ke", me) && !present("xiezi ke", me)
        && !present("shedan", me) && !present("du zhusi", me)
        && !present("shachong ke", me))
                return notify_fail("你没有足够的原料！\n");
        message_vision(CYN"$N小心翼翼地把一块毒药和硫磺放在一起，注进内力，捏成了一颗炼心弹。\n"NOR, me );
                ob = new("/d/xingxiu/obj/lianxin.c");
                ob->move(me);
        obj = all_inventory(me);
        for(i=sizeof(obj)-1; i>=0; i--) {
                if( userp(obj[i]) ) continue;
                if( query("name", obj[i]) == "蜈蚣壳" || query("id", obj[i]) == "xiezi ke"
                || query("id", obj[i]) == "shedan" || query("id", obj[i]) == "du zhusi"
                || query("id", obj[i]) == "shachong ke" )
                        destruct(obj[i]);
        }
        destruct(this_object());
        return 1;
}
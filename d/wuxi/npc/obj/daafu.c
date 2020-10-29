// This program is a part of NITAN MudLIB 
// redl 2013/9
inherit ITEM;
#include <ansi.h>

void create()
{
        set_name("大阿福", ({"da afu", "afu"}));
        set("long",
                "这是个憨态可掬的大阿福。这尊大阿福塑成男像。\n使用(use)它可以让宝宝变大一岁。\n");
        set("unit", "尊");
        set("weight", 10);
        set("value", 999990000);
}

int do_use()
{
        int age;
        object ob, me = this_player();

        if (!query("couple/child_id", me))
        {
                tell_object(me, NOR + "你还没有孩子。\n" + NOR); 
                return 1;
        }

      ob = present(query("couple/child_id", me), environment(me));
        if( !ob || !objectp(ob) || base_name(ob)!="/clone/user/baby" )
        {
                        tell_object(me, NOR + "你的孩子没有站在你跟前。\n" + NOR); 
                        return 1;
        }
        
    age = query("age", ob);
    if (age > 59) 
    {
                tell_object(me, NOR + "你的孩子已经够老的了。\n" + NOR); 
                return 1;
    }
    
    age ++;
    set("mud_age", age * 86400, ob);
    set("age", age, ob);
        
        message_vision(append_color(NOR + "$N拿起一尊" + name() + "往$n的头上一拍...\$n吓得一个激灵，容貌似乎苍老了一点。\n" + NOR, YEL), me, ob);
        destruct(this_object());
        return 1; 
        
}

void init()
{
        object me = this_player();
        if (playerp(me)) {
                add_action("do_use", "use");
        }
}


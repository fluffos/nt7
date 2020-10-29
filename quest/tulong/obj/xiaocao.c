#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
    set_name(HIM "精灵之花" NOR, ({ "flower" }) );
        set_weight(10);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", "一朵娇艳美丽，不沾半点世间烟火的精灵之花。\n");
                set("unit", "朵");
                set("value", 6); 
                set("no_get", 1);
                set("material", "plant");
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N轻轻地把一朵$n戴在头上。\n");
                set("unwield_msg", "$N轻轻地把$n从头上除了下来。\n");
                set("female_only", 1);

        }
        setup();
}

void init()
{
        add_action("do_get","zhai");
}

int do_get(string arg)
{
        object me,ob;
        me=this_player();
        ob=this_object(); 

    if( !arg ) return notify_fail("你要捡起什麽东西？\n");
        if (arg=="flower" ) 
         {
        write(HIM"精灵之花"NOR+HIG"中出现了一只小精灵，\n
小精灵振动着翅膀说：谢谢你解开了第三个封印，请过关吧！\n"NOR);
        ob->move(me);   
 message_vision(HIG"$N被一阵清风送到了另一个房间。\n"NOR, me); 
        me->move("/d/dragon/spirit5");
                set_temp("m_success/初级", 1, me);
        destruct(ob);        return 1;
         }
}
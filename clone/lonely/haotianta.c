#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIM + "昊天塔" NOR, ({ "haotian ta", "haotian", "ta" }) );
        set_weight(300);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "个");
                set("long", HIM "这是一个拥有吸星换月之力的宝塔，不时地从中投射出\n"
                                "奇异的光芒。\n"                                
                                "当你打通十二重天达到天外天后，能借用该塔之力进入来世。\n" 
                                "*可用之神力进入轮回司中（use haotian ta）。\n"NOR);

        }
        setup();
}

void init()
{
        add_action("do_use", "use");       
}

int do_use(string arg)
{
        object me;
        
        me = this_player();
        
        if(! objectp(present("haotian ta", me)))return 0;
        
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");
        
        if( !query("outdoors", environment(me)) )
                 return notify_fail("你得先到户外去。\n");
                 
        message_sort(HIM + "\n$N" HIM "祭起手中的昊天塔，猛然间，七色光芒自昊天塔中射"
                     "出，将$N卷了进去。\n" NOR, me);
                
        me->move("/kungfu/class/sky/lunhuisi");
        set("startroom", "/kungfu/class/sky/lunhuisi", me);
        destruct(this_object());

        return 1;
}
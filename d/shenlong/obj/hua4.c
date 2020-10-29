// hua4.c

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIC "翡翠兰" NOR, ({"feicui lan", "feicui", "lan"}));
   /*if (clonep())
		set_default_object(__FILE__);
   else*/ {
        	set("unit", "朵");
		set("long", "这是一朵千年难得一见的翡翠兰，据说能解百毒。\n");
        	set("value", 1000000);
		set("only_do_effect", 1);
	}
        setup();
}

int do_effect(object me)
{
        int time = 300;

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

        if( time()-query_temp("last_eat/feicui", me) < time ) 
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n"); 
                return 1; 
        }

        set_temp("last_eat/feicui", time(), me); 
        me->clear_condition();
set("eff_jing",query("max_jing",  me), 	me);
set("jing",query("max_jing",  me), 	me);
set("eff_qi",query("max_qi",  me), 	me);
set("qi",query("max_qi",  me), 	me);
        message_vision("$N把" + name() + "扔进嘴里，几下就吞了下去。\n", me);
	tell_object(me, HIG "\n你只觉一股清香沁入心肺，顿时灵台一片"
		        "空明，神意清爽！\n" NOR);
	destruct(this_object());
	return 1;
}

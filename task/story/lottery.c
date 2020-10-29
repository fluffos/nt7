
// 彩票

inherit TASK;

#include <ansi.h>
void create()
{

        set_name(HIM "彩票" NOR, ({ "lottery" }));
        set_weight(1);
        set("owner","冼老板");
        set("task",1); 
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
	        set("unit", "张");
    	        set("long", "一张彩票。好象是扬州城冼老板的。");
        	set("value", 100);
	        set("no_put_in",1); 
        }
        setup();
}

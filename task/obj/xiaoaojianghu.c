#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIC "笑傲江湖曲" NOR,({ "xiaoao jianghu" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "本");
                set("material", "paper");
                set("long", "这是一本笑傲江湖曲。\n");
        }
        set("owner", "令狐冲");
        setup();
}  

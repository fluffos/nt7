#include <ansi.h>
inherit TASK;
void create()
{
        set_name(HIC "辟邪剑谱" NOR,({ "pixie jianpu" }) );
        set_weight(100);
        if( clonep() )
                destruct(this_object());
        else {
                set("unit", "本");
                set("material", "paper");
                set("long", "这是一本辟邪剑普秘籍。\n");
        }
        set("owner", "林平之");
        setup();
}  

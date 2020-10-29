// 上古十大神器之 昊天塔
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(HIM + "昊天塔" NOR, ({ "haotian ta", "haotian", "ta" }) );
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "个");
                set("long", HIM "这是一个拥有吸星换月之力的宝塔，不时地从中投射出\n"
                                "奇异的光芒。\n"                                
                                "当你打通十二重天达到天外天后，能借用该塔之力进入来世。\n" NOR);

        }
        setup();
}

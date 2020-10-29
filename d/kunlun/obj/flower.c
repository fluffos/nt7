// Room: flower.c
// Last Modified by Lonely on Nov. 15 2000

#include <ansi.h>                     
#include <armor.h>
inherit HEAD;

void create()
{
        set_name(HIG"青陀罗花"NOR,({ "flower", "hua" }) );
        set_weight(500);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "朵");
                set("value", 0);
                set("material", "plant");
                set("long", "这是一朵青陀罗花。\n"
                        "这花汁原有腥臭之气，本身并无毒性, \n"
                        "但一经和鲜血混和，却生剧毒，同时腥臭转为清香。\n");
                set("wear_msg", "");
                set("unequip_msg", "$N摘下胸前的$n。\n");
                set("armor_prop/armor", 0);
        }
        setup();
}

int wear()
{
        object me = environment();
        int ret;

        message_vision("$N拿出一朵"+query("name", this_object())+"，戴在胸前。",me);
        if (ret=::wear())
        {
                if( query("gender", me) == "男性" )
                        message_vision("好一个风流少年郎！\n", me);
                else if( query("gender", me) == "女性" )
                        message_vision("好一个美丽俏佳娃！\n", me);
                else
                        message_vision("好一个不三不四的家伙！\n", me);
        }
        return ret;
}
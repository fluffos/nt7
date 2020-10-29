#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        string *names=({HIW"百合"NOR,HIR"玫瑰"NOR,HIB"芙蓉"NOR,HIY"海棠"NOR,HIM"蔷薇"NOR,HIG"玉兰"NOR,HIC"丁香"NOR,
                       HIY"腊梅"NOR,HIR"月季"NOR,HIW"雪莲"NOR});
        set_name(names[random(sizeof(names))], ({"flower", "hua"}));
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "朵");
                set("long","一朵美丽的"+query("name", this_object())+NOR"。\n");
                set("value", 0);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", random(2)+1);
                set("wear_msg", "$N轻轻地把一朵$n戴在头上。\n");
                set("unequip_msg", "$N轻轻地把$n从头上摘了下来。\n");
        }
        setup();
}
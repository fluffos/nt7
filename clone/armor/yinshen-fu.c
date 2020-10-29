#include <armor.h>
#include <ansi.h>

inherit MYHEART;

void create()
{
        set_name(NOR + WHT "隐身符" NOR, ({ "yinshen fu", "yinshen", "fu" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "paper");
                set("unit", "张");
                set("long", HIY "这是一张道符，据说装备后可以隐藏行踪。\n" NOR);
                set("value", 10000);
                set("armor_prop/invisible", 1);
                set("special/desc", "装备后可隐藏行踪，他人无法查看到你的存在。");
        }
        setup();
}

int query_autoload()
{
        return 1;
}
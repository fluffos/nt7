#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIM "浅草观音" NOR, ({ "qiancao guanyin", "qiancao", "guanyin" }) );
        set_weight(1);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("material", "paper");
                set("unit", "个");
                set("long", HIM "这是一个产自扶桑浅草寺的护身人偶，上面绣有「浅草观音」的字样。\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/qy", 4);

        }
        setup();
}

int query_autoload()
{
        return 1;
}
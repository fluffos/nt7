#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(HIR "朱雀羽毛" NOR, ({ "zhuque yumao", "zhuque", "yumao" }));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {               
                    set("long", HIR "一根朱雀身上的羽毛，呈火红色。\n" NOR);
            set("unit", "根");
            set("value", 100000);

        }
        setup();
}

int query_autoload()
{
        return 1;
}
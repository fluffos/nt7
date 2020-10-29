#include <weapon.h>
#include <ansi.h>
inherit STAFF;

void create()
{
        set_name(NOR + YEL "青铜杖" NOR, ({ "qingtong zhang","qingtong","zhang" }));
        set_weight(800);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "根");
                set("long", NOR + YEL "这是一根青铜锻造的杖，入手沉甸甸的，似乎相当结实。\n" NOR);
                set("material", "qingtong");
                set("value", 100000);
        }
        init_staff(300);
        setup();
}

int query_autoload()
{
        return 1;
}
#include <ansi.h>
#include <weapon.h>
inherit F_UNIQUE;

inherit STAFF; 

void create()
{
        set_name(HIG "玉竹杖" NOR, ({"yuzhu zhang", "zhang", "staff"}));
        set_weight(5000);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "根");
                set("long", HIG"一根碧绿犹如翡翠般的竹杖。\n"NOR);
                set("value", 8000000);
                set("material", "bamboo");
                set("rigidity", 3000);
                set("replica_ob","/clone/weapon/zhubang");
                set("wield_msg", "$N抽出一根青光闪闪的绿玉竹杖抓在手中。\n");
                set("unwield_msg", "$N把手中的绿竹杖插回腰中。\n");
        }
        init_staff(200); 
        setup();
}       
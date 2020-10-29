// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玉麒麟[2;37;0m[2;37;0m", ({"qiling"}));        
        set("gender", "男性");                
        set("long", "苍茫的天涯是我的爱，好大一只麒麟跑过来。[2;37;0m
它是三问鱼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nulx");
        set("owner_name", "三问鱼");
        set_temp("owner", "nulx");
        set_temp("owner_name", "三问鱼");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("勇气[2;37;0m[2;37;0m", ({"fannysoamm"}));        
        set("gender", "男性");                
        set("long", "美丽于一身的强大生物[2;37;0m
它是北风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fannysoa");
        set("owner_name", "北风");
        set_temp("owner", "fannysoa");
        set_temp("owner_name", "北风");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m獬豸[2;37;0m[2;37;0m", ({"judgement"}));        
        set("gender", "男性");                
        set("long", "体形或而大如牛，或而小如羊，双目炯炯有神，额上朝天耸立一角！[2;37;0m
它是北斗的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "delta");
        set("owner_name", "北斗");
        set_temp("owner", "delta");
        set_temp("owner_name", "北斗");
        ::setup();
}

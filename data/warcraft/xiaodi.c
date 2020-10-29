// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("可口可乐[2;37;0m[2;37;0m", ({"cokee"}));        
        set("gender", "男性");                
        set("long", "可口可乐[2;37;0m
它是逍地的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaodi");
        set("owner_name", "逍地");
        set_temp("owner", "xiaodi");
        set_temp("owner_name", "逍地");
        ::setup();
}

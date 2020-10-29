// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"omo"}));        
        set("gender", "女性");                
        set("long", "白虎[2;37;0m
它是周仓拾的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xpd");
        set("owner_name", "周仓拾");
        set_temp("owner", "xpd");
        set_temp("owner_name", "周仓拾");
        ::setup();
}

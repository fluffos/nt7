// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"mes"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是钱庄五的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mee");
        set("owner_name", "钱庄五");
        set_temp("owner", "mee");
        set_temp("owner_name", "钱庄五");
        ::setup();
}

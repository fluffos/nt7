// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"mds"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是钱庄三的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mcc");
        set("owner_name", "钱庄三");
        set_temp("owner", "mcc");
        set_temp("owner_name", "钱庄三");
        ::setup();
}

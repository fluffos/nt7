// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"mas"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是钱庄一的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "maa");
        set("owner_name", "钱庄一");
        set_temp("owner", "maa");
        set_temp("owner_name", "钱庄一");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("最爱白虎[2;37;0m[2;37;0m", ({"hlclabh"}));        
        set("gender", "女性");                
        set("long", "最爱白虎[2;37;0m
它是白虎一号的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hlcla");
        set("owner_name", "白虎一号");
        set_temp("owner", "hlcla");
        set_temp("owner_name", "白虎一号");
        ::setup();
}

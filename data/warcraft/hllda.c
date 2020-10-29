// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎一号[2;37;0m[2;37;0m", ({"hlldabh"}));        
        set("gender", "女性");                
        set("long", "最爱白虎[2;37;0m
它是文东一号的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "hllda");
        set("owner_name", "文东一号");
        set_temp("owner", "hllda");
        set_temp("owner_name", "文东一号");
        ::setup();
}

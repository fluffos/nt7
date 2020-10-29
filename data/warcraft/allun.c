// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("沙沙[2;37;0m[2;37;0m", ({"shasha"}));        
        set("gender", "男性");                
        set("long", "沙沙的最爱[2;37;0m
它是萧寒的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "allun");
        set("owner_name", "萧寒");
        set_temp("owner", "allun");
        set_temp("owner_name", "萧寒");
        ::setup();
}

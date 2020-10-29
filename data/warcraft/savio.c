// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("寒江雪[2;37;0m[2;37;0m", ({"vivian"}));        
        set("gender", "女性");                
        set("long", "看上去十分的威严、瞩目，充满无穷的神气。[2;37;0m
它是舟子恒的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "savio");
        set("owner_name", "舟子恒");
        set_temp("owner", "savio");
        set_temp("owner_name", "舟子恒");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m奈[5m[1;37m落[2;37;0m[2;37;0m", ({"xox"}));        
        set("gender", "女性");                
        set("long", "其视乃明，不食不寝不息，风雨是谒。是烛九阴，是烛龙。[2;37;0m
它是奢比尸的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "hmm");
        set("owner_name", "奢比尸");
        set_temp("owner", "hmm");
        set_temp("owner_name", "奢比尸");
        ::setup();
}

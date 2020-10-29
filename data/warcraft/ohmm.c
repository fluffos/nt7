// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m应[1;37m龙[2;37;0m[2;37;0m", ({"ioi"}));        
        set("gender", "男性");                
        set("long", "旱而为应龙之状，乃得大雨。目开而日出，目闭而日落[2;37;0m
它是马玛的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ohmm");
        set("owner_name", "马玛");
        set_temp("owner", "ohmm");
        set_temp("owner_name", "马玛");
        ::setup();
}

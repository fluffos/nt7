// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m辛巴[2;37;0m[2;37;0m", ({"simba"}));        
        set("gender", "男性");                
        set("long", "万兽之王[2;37;0m
它是木法沙的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mufasa");
        set("owner_name", "木法沙");
        set_temp("owner", "mufasa");
        set_temp("owner_name", "木法沙");
        ::setup();
}

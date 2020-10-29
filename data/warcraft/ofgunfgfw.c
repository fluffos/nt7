// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"zxcc"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是逯冲风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ofgunfgfw");
        set("owner_name", "逯冲风");
        set_temp("owner", "ofgunfgfw");
        set_temp("owner_name", "逯冲风");
        ::setup();
}

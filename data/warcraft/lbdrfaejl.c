// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"west"}));        
        set("gender", "女性");                
        set("long", "do 自行车,自行车[2;37;0m
它是卓灏玉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lbdrfaejl");
        set("owner_name", "卓灏玉");
        set_temp("owner", "lbdrfaejl");
        set_temp("owner_name", "卓灏玉");
        ::setup();
}

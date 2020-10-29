// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("泡泡龙[2;37;0m[2;37;0m", ({"goto"}));        
        set("gender", "女性");                
        set("long", "泡泡...[2;37;0m
它是灭莉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "loli");
        set("owner_name", "灭莉");
        set_temp("owner", "loli");
        set_temp("owner_name", "灭莉");
        ::setup();
}

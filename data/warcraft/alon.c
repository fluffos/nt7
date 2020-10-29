// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m阎罗王[2;37;0m[2;37;0m", ({"alcn"}));        
        set("gender", "女性");                
        set("long", "阎罗王[2;37;0m
它是猪四的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "alon");
        set("owner_name", "猪四");
        set_temp("owner", "alon");
        set_temp("owner_name", "猪四");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("美人儿[2;37;0m[2;37;0m", ({"piao"}));        
        set("gender", "女性");                
        set("long", "母的[2;37;0m
它是牛的很的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lgumu");
        set("owner_name", "牛的很");
        set_temp("owner", "lgumu");
        set_temp("owner_name", "牛的很");
        ::setup();
}

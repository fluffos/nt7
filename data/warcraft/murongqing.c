// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("孤羽[2;37;0m[2;37;0m", ({"guyu"}));        
        set("gender", "男性");                
        set("long", "无心亦心，自在观真，薄情非情，醉饮太平。[2;37;0m
它是慕容情的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "murongqing");
        set("owner_name", "慕容情");
        set_temp("owner", "murongqing");
        set_temp("owner_name", "慕容情");
        ::setup();
}

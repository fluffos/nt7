// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("风骚美人[2;37;0m[2;37;0m", ({"meiren"}));        
        set("gender", "女性");                
        set("long", "水蜜桃[2;37;0m
它是在喇在的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lhuashan");
        set("owner_name", "在喇在");
        set_temp("owner", "lhuashan");
        set_temp("owner_name", "在喇在");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("山猪[2;37;0m[2;37;0m", ({"yaobb"}));        
        set("gender", "女性");                
        set("long", "山猪[2;37;0m
它是山药的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yao");
        set("owner_name", "山药");
        set_temp("owner", "yao");
        set_temp("owner_name", "山药");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是摩诃的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wake");
        set("owner_name", "摩诃");
        set_temp("owner", "wake");
        set_temp("owner_name", "摩诃");
        ::setup();
}

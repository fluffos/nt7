// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白狐[2;37;0m[2;37;0m", ({"bbookpet"}));        
        set("gender", "男性");                
        set("long", "白狐[2;37;0m
它是墨二的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "bbook");
        set("owner_name", "墨二");
        set_temp("owner", "bbook");
        set_temp("owner_name", "墨二");
        ::setup();
}

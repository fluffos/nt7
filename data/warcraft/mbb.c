// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m", ({"cat"}));        
        set("gender", "女性");                
        set("long", "其实是一只猫[2;37;0m
它是墨不白的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mbb");
        set("owner_name", "墨不白");
        set_temp("owner", "mbb");
        set_temp("owner_name", "墨不白");
        ::setup();
}

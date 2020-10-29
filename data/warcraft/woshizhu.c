// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "女性");                
        set("long", "白[2;37;0m
它是猪头的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "woshizhu");
        set("owner_name", "猪头");
        set_temp("owner", "woshizhu");
        set_temp("owner_name", "猪头");
        ::setup();
}

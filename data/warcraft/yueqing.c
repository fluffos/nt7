// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("就会很快就[2;37;0m[2;37;0m", ({"yueqinga"}));        
        set("gender", "女性");                
        set("long", "就会很快就[2;37;0m
它是令狐玉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yueqing");
        set("owner_name", "令狐玉");
        set_temp("owner", "yueqing");
        set_temp("owner_name", "令狐玉");
        ::setup();
}

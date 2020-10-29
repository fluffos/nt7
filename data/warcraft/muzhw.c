// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白狐[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "白[2;37;0m
它是啊梦的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "muzhw");
        set("owner_name", "啊梦");
        set_temp("owner", "muzhw");
        set_temp("owner_name", "啊梦");
        ::setup();
}

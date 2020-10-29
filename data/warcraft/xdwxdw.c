// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神花波一多[2;37;0m[2;37;0m", ({"bin"}));        
        set("gender", "男性");                
        set("long", "1987年12月26日在小日本出生，2012年3月出道。[2;37;0m
它是蛇仔明的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xdwxdw");
        set("owner_name", "蛇仔明");
        set_temp("owner", "xdwxdw");
        set_temp("owner_name", "蛇仔明");
        ::setup();
}

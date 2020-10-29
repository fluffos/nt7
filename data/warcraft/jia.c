// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m制[33m钱[33m[2;37;0m[2;37;0m", ({"money"}));        
        set("gender", "男性");                
        set("long", "长得跟制钱一样喜人的老虎[2;37;0m
它是贾有钱的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jia");
        set("owner_name", "贾有钱");
        set_temp("owner", "jia");
        set_temp("owner_name", "贾有钱");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m红颜知己[2;37;0m[2;37;0m", ({"ilovelong"}));        
        set("gender", "男性");                
        set("long", "我爱我的龙龙[2;37;0m
它是周慧敏的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zhouhuimin");
        set("owner_name", "周慧敏");
        set_temp("owner", "zhouhuimin");
        set_temp("owner_name", "周慧敏");
        ::setup();
}

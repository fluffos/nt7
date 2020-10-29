// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m真爱三龙[2;37;0m[2;37;0m", ({"ilovelong"}));        
        set("gender", "女性");                
        set("long", "我爱我的龙龙[2;37;0m
它是李三争的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lizhengc");
        set("owner_name", "李三争");
        set_temp("owner", "lizhengc");
        set_temp("owner_name", "李三争");
        ::setup();
}

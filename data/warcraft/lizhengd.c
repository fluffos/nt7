// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;37m真爱四龙[2;37;0m[2;37;0m", ({"ilovelong"}));        
        set("gender", "女性");                
        set("long", "我爱我的龙龙[2;37;0m
它是李四争的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lizhengd");
        set("owner_name", "李四争");
        set_temp("owner", "lizhengd");
        set_temp("owner_name", "李四争");
        ::setup();
}

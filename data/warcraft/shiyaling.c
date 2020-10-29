// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("爱骑[2;37;0m[2;37;0m", ({"ilovelong"}));        
        set("gender", "女性");                
        set("long", "我爱我的龙龙[2;37;0m
它是史亚玲的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "shiyaling");
        set("owner_name", "史亚玲");
        set_temp("owner", "shiyaling");
        set_temp("owner_name", "史亚玲");
        ::setup();
}

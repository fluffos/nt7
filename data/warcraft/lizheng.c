// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;35m真爱永恒[2;37;0m[2;37;0m", ({"ilovelong"}));        
        set("gender", "女性");                
        set("long", "我爱我的龙龙[2;37;0m
它是李争的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lizheng");
        set("owner_name", "李争");
        set_temp("owner", "lizheng");
        set_temp("owner_name", "李争");
        ::setup();
}

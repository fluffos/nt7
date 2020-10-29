// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m夏娃[2;37;0m[2;37;0m", ({"eva"}));        
        set("gender", "女性");                
        set("long", "无[2;37;0m
它是老江湖的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "oldmen");
        set("owner_name", "老江湖");
        set_temp("owner", "oldmen");
        set_temp("owner_name", "老江湖");
        ::setup();
}

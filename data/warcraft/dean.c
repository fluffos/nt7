// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("超牛小鸟[2;37;0m[2;37;0m", ({"deanxiaoniao"}));        
        set("gender", "女性");                
        set("long", "这是迪恩的小鸟[2;37;0m
它是迪恩的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dean");
        set("owner_name", "迪恩");
        set_temp("owner", "dean");
        set_temp("owner_name", "迪恩");
        ::setup();
}

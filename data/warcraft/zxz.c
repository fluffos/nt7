// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麻布袋[2;37;0m[2;37;0m", ({"bag"}));        
        set("gender", "女性");                
        set("long", "麻布袋[2;37;0m
它是墨毒的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zxz");
        set("owner_name", "墨毒");
        set_temp("owner", "zxz");
        set_temp("owner_name", "墨毒");
        ::setup();
}

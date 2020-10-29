// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("美丽强大幻兽[2;37;0m[2;37;0m", ({"zhuquezhuque"}));        
        set("gender", "女性");                
        set("long", "美丽强大幻兽[2;37;0m
它是静五的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jinge");
        set("owner_name", "静五");
        set_temp("owner", "jinge");
        set_temp("owner_name", "静五");
        ::setup();
}

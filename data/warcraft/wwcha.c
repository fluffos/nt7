// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("荒兽[2;37;0m[2;37;0m", ({"ppp"}));        
        set("gender", "女性");                
        set("long", "荒兽[2;37;0m
它是大波龙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wwcha");
        set("owner_name", "大波龙");
        set_temp("owner", "wwcha");
        set_temp("owner_name", "大波龙");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m无敌[2;37;0m[2;37;0m", ({"wu_di"}));        
        set("gender", "女性");                
        set("long", "攻不破，自然无敌。[2;37;0m
它是恶恶恶的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "eee");
        set("owner_name", "恶恶恶");
        set_temp("owner", "eee");
        set_temp("owner_name", "恶恶恶");
        ::setup();
}

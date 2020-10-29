// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m火凤凰[2;37;0m[2;37;0m", ({"liyr"}));        
        set("gender", "女性");                
        set("long", "生活在神兽森林的仙宠[2;37;0m
它是林月如的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "shen");
        set("owner_name", "林月如");
        set_temp("owner", "shen");
        set_temp("owner_name", "林月如");
        ::setup();
}

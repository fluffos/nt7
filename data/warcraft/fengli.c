// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔毯[2;37;0m[2;37;0m", ({"maotian"}));        
        set("gender", "女性");                
        set("long", "舒福的毯子[2;37;0m
它是凤梨的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fengli");
        set("owner_name", "凤梨");
        set_temp("owner", "fengli");
        set_temp("owner_name", "凤梨");
        ::setup();
}

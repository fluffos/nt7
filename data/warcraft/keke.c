// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("暗杀未[2;37;0m[2;37;0m", ({"asdf"}));        
        set("gender", "男性");                
        set("long", "暗杀未[2;37;0m
它是额是的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "keke");
        set("owner_name", "额是");
        set_temp("owner", "keke");
        set_temp("owner_name", "额是");
        ::setup();
}

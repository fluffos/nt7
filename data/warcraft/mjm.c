// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱竹雀[2;37;0m[2;37;0m", ({"que"}));        
        set("gender", "女性");                
        set("long", "朱[2;37;0m
它是名角米的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mjm");
        set("owner_name", "名角米");
        set_temp("owner", "mjm");
        set_temp("owner_name", "名角米");
        ::setup();
}

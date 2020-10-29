// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("九凤[2;37;0m[2;37;0m", ({"jiuf"}));        
        set("gender", "女性");                
        set("long", "九凤[2;37;0m
它是灵儿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ler");
        set("owner_name", "灵儿");
        set_temp("owner", "ler");
        set_temp("owner_name", "灵儿");
        ::setup();
}

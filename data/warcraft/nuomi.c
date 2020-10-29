// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火[2;37;0m[2;37;0m", ({"huo"}));        
        set("gender", "男性");                
        set("long", "$HIR$火[2;37;0m
它是糯米的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "nuomi");
        set("owner_name", "糯米");
        set_temp("owner", "nuomi");
        set_temp("owner_name", "糯米");
        ::setup();
}

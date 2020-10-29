// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"niao"}));        
        set("gender", "女性");                
        set("long", "你死了.[2;37;0m
它是米书的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mid");
        set("owner_name", "米书");
        set_temp("owner", "mid");
        set_temp("owner_name", "米书");
        ::setup();
}

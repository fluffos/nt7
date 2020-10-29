// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m凤[1;33m凰[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "上古神兽不死鸟[2;37;0m
它是毒姑的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dugu");
        set("owner_name", "毒姑");
        set_temp("owner", "dugu");
        set_temp("owner_name", "毒姑");
        ::setup();
}

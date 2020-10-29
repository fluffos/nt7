// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"que"}));        
        set("gender", "女性");                
        set("long", "不死鸟[2;37;0m
它是卿卿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qing");
        set("owner_name", "卿卿");
        set_temp("owner", "qing");
        set_temp("owner_name", "卿卿");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火鸟[2;37;0m[2;37;0m", ({"feifeng"}));        
        set("gender", "女性");                
        set("long", "火鸟[2;37;0m
它是安可的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "shuifei");
        set("owner_name", "安可");
        set_temp("owner", "shuifei");
        set_temp("owner_name", "安可");
        ::setup();
}

// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m不死朱雀[2;37;0m[2;37;0m", ({"jianers"}));        
        set("gender", "女性");                
        set("long", "不死朱雀[2;37;0m
它是剑二的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jianer");
        set("owner_name", "剑二");
        set_temp("owner", "jianer");
        set_temp("owner_name", "剑二");
        ::setup();
}

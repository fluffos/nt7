// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m菲尼克斯[2;37;0m[2;37;0m", ({"asd"}));        
        set("gender", "男性");                
        set("long", "菲尼克斯[2;37;0m
它是段正玄的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zhengxuan");
        set("owner_name", "段正玄");
        set_temp("owner", "zhengxuan");
        set_temp("owner_name", "段正玄");
        ::setup();
}

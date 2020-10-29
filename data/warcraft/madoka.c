// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m月野兔[2;37;0m[2;37;0m", ({"yyt"}));        
        set("gender", "女性");                
        set("long", "可爱的美少女[2;37;0m
它是鹿目圆香的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "madoka");
        set("owner_name", "鹿目圆香");
        set_temp("owner", "madoka");
        set_temp("owner_name", "鹿目圆香");
        ::setup();
}

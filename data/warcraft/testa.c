// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[31m飞天神兽[35m麒麟[2;37;0m[2;37;0m", ({"qilun"}));        
        set("gender", "男性");                
        set("long", "天空中突然一道闪电，一瞬间，一只神物出现在你的面前...[2;37;0m
它是乱来的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "testa");
        set("owner_name", "乱来");
        set_temp("owner", "testa");
        set_temp("owner_name", "乱来");
        ::setup();
}

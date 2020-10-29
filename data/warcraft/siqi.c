// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m奇虎[2;37;0m[2;37;0m", ({"qihu"}));        
        set("gender", "女性");                
        set("long", "奇虎[2;37;0m
它是思奇的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "siqi");
        set("owner_name", "思奇");
        set_temp("owner", "siqi");
        set_temp("owner_name", "思奇");
        ::setup();
}

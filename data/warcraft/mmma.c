// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m噬天虎[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "女性");                
        set("long", "可爱小老虎[2;37;0m
它是月武者的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mmma");
        set("owner_name", "月武者");
        set_temp("owner", "mmma");
        set_temp("owner_name", "月武者");
        ::setup();
}

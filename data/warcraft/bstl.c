// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("霸天虎[2;37;0m[2;37;0m", ({"bth"}));        
        set("gender", "男性");                
        set("long", "来自赛博斯坦星球[2;37;0m
它是老头子的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "bstl");
        set("owner_name", "老头子");
        set_temp("owner", "bstl");
        set_temp("owner_name", "老头子");
        ::setup();
}
